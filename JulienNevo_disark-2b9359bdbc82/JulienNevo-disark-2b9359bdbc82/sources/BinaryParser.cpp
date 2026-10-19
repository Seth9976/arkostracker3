#include "BinaryParser.h"

#include "base/ExportConfiguration.h"

namespace disark
{

BinaryParser::BinaryParser(const ExportConfiguration& pExportConfiguration, BinaryParser::BytesProvider& pBytesProvider) noexcept :
    bytesProvider(pBytesProvider),
    opcodes(pExportConfiguration)
{
}

std::pair<Opcode, BinaryParser::ReadResult> BinaryParser::readOpcode() noexcept
{
    // Reads a first byte.
    const auto firstByte = bytesProvider.fetchByte();
    if (firstByte < 0) {
        return { Opcode::buildError(), ReadResult::buildError({ }) };      // Couldn't get one byte!
    }

    // Searches for an opcode that has this byte. There may be none, because we have to search for prefixes instructions!
    const auto* opcode = opcodes.search(firstByte);
    if (opcode != nullptr) {
        // We have found a valid opcode with one byte.
        return { *opcode, ReadResult::buildSuccess() };
    }

    // --------------------------------------------------------------
    // No valid 1-byte opcode was found. Maybe a two-byte?
    const auto secondByte = bytesProvider.fetchByte();
    if (secondByte < 0) {
        return { Opcode::buildError(), ReadResult::buildError({ firstByte }) };      // Only one byte could be read.
    }
    bool errorIllegalCombination;       // NOLINT(*-init-variables)
    opcode = opcodes.search(firstByte, secondByte, errorIllegalCombination);

    if (opcode != nullptr) {
        // We have found a valid opcode with two bytes.
        return { *opcode, ReadResult::buildSuccess() };
    }
    // We may have encountered an illegal combination.
    if (errorIllegalCombination) {
        return { Opcode::buildError(), ReadResult::buildError({ firstByte, secondByte }) };
    }

    // --------------------------------------------------------------
    // Two bytes are not enough to choose. We need TWO more bytes. The next will be a relative index ("d"), and the next an opcode.
    const auto relativeIndex = bytesProvider.fetchByte();
    if (relativeIndex < 0) {
        return { Opcode::buildError(), ReadResult::buildError({ firstByte, secondByte }) };      // Only two bytes could be read.
    }
    // Reads the fourth byte, which is the opcode third byte.
    const auto thirdByte = bytesProvider.fetchByte();
    if (thirdByte < 0) {
        return { Opcode::buildError(), ReadResult::buildError({ firstByte, secondByte, relativeIndex }) };      // Only three bytes could be read.
    }

    opcode = opcodes.search(firstByte, secondByte, thirdByte, errorIllegalCombination);

    if (opcode != nullptr) {
        // Stores the signed index now. Must simpler, we won't ask the bytes provider to rewind!
        auto returnedOpcode = *opcode;                // Must make a copy, the original one was const.
        returnedOpcode.setSignedIndexForThreeBytesOpcode(relativeIndex);
        // We have found a valid opcode with three bytes + relative (special case!!).
        return { std::move(returnedOpcode), ReadResult::buildSuccess() };
    }

    // We have encountered an illegal combination.
    return { Opcode::buildError(), ReadResult::buildError({ firstByte, secondByte, relativeIndex, thirdByte }) };
}

std::pair<std::unique_ptr<Instruction>, BinaryParser::ReadResult> BinaryParser::readInstruction(const Opcode& opcode) noexcept
{
    // Any parameter in the opcode? If no, we can stop here, everything is fine.
    auto parameter1Type = opcode.getParameterType1();
    auto parameter2Type = opcode.getParameterType2();
    if ((parameter1Type == SourceParameterType::absent) && (parameter2Type == SourceParameterType::absent)) {
        return std::make_pair(std::make_unique<Instruction>(opcode), ReadResult::buildSuccess());
    }

    // Starts with the specific case. If the opcode is a three-bytes opcode, then it means:
    // opcode - opcode - signedIndex - opcode! Damn Z80.
    // The trick found is to store this relativeIndex in the opcode while the opcode was being read.
    int parameter1;       // NOLINT(*-init-variables)
    int parameter2;       // NOLINT(*-init-variables)
    if (opcode.isThreeBytesOpcode()) {
        jassert(parameter1Type == SourceParameterType::signed8bitsIndex);
        parameter1 = opcode.getSignedIndexForThreeBytesOpcode();
        parameter2 = -1;
        jassert(parameter1 >= 0);
    } else {
        // A normal opcode (1 or 2 bytes).
        // Reads the first parameter.
        bool success;       // NOLINT(*-init-variables)
        auto firstParameterBytes = readBytesFromParameterType(parameter1Type, success);
        if (!success) {
            // Not all bytes could be read.
            return std::make_pair(nullptr, ReadResult::buildError(firstParameterBytes));
        }

        // Reads the second parameter.
        auto secondParameterBytes = readBytesFromParameterType(parameter2Type, success);
        if (!success) {
            // Not all bytes could be read. Important: the first parameter bytes are also returned, they are added at the beginning.
            secondParameterBytes.insert(secondParameterBytes.begin(), firstParameterBytes.begin(), firstParameterBytes.end());
            return std::make_pair(nullptr, ReadResult::buildError(secondParameterBytes));
        }

        // The Instruction can be built.
        parameter1 = buildParameter(firstParameterBytes);
        parameter2 = buildParameter(secondParameterBytes);
    }

    Instruction instruction(opcode, parameter1, parameter2);

    return std::make_pair(std::make_unique<Instruction>(std::move(instruction)), ReadResult::buildSuccess());
}

std::vector<int> BinaryParser::readBytesFromParameterType(const SourceParameterType type, bool& success) noexcept
{
    success = true;

    std::vector<int> readBytes;

    // Determines how many bytes there are to read, from the Parameter type.
    int byteCountToRead;       // NOLINT(*-init-variables)
    switch (type) {
        case SourceParameterType::absent:
            byteCountToRead = 0;
            break;
        case SourceParameterType::number8bits: [[fallthrough]];
        case SourceParameterType::relativeJump8bits: [[fallthrough]];
        case SourceParameterType::signed8bitsIndex:
            byteCountToRead = 1;
            break;
        case SourceParameterType::number16bits:
            byteCountToRead = 2;
            break;
        default:
            jassertfalse;           // Abnormal!
            byteCountToRead = 0;
            break;
    }

    // Reads every byte, if possible.
    for (; byteCountToRead > 0; --byteCountToRead) {
        auto readByte = bytesProvider.fetchByte();
        if (readByte < 0) {
            // Error!
            success = false;
            break;
        }

        readBytes.emplace_back(readByte);
    }

    return readBytes;
}

int BinaryParser::buildParameter(const std::vector<int>& bytes) noexcept
{
    switch (bytes.size()) {
        case 0U:
            return -1;      // No value.
        case 1U:
            return bytes.front();
        case 2U:
            return bytes.at(0U) + (bytes.at(1U) * 256);     // Little endian.
        default:
            jassertfalse;
            return -1;      // Should never happen!
    }
}

std::pair<std::vector<Instruction>, std::vector<int>> BinaryParser::buildAllInstructions() noexcept
{
    std::vector<Instruction> instructions;
    std::vector<int> leftOverBytes;

    while (bytesProvider.hasNext()) {
        auto opcodeAndResult = readOpcode();
        const auto& opcodeResult = opcodeAndResult.second;
        if (!opcodeResult.isSuccess()) {
            // Couldn't read the opcode fully, or illegal combination. Stops, and stores the left-over bytes.
            leftOverBytes.insert(leftOverBytes.end(), opcodeResult.getReadBytesIfError().begin(), opcodeResult.getReadBytesIfError().end());
            break;
        }

        // Builds the Instruction from the Opcode.
        const auto& opcode = opcodeAndResult.first;
        auto instructionAndResult = readInstruction(opcode);
        if (instructionAndResult.first == nullptr) {
            // Not a success. Same as above, stores the left-over bytes.
            const auto& instructionResult = instructionAndResult.second;
            jassert(!instructionResult.isSuccess());

            // Stores the opcode bytes. This is needed, because neither the opcode nor the parameters must be encoded as-is, so we needed to track the bytes into the left-over.
            const auto& opcodeBytes = opcode.getOpcodeBytes();
            leftOverBytes.insert(leftOverBytes.end(), opcodeBytes.begin(), opcodeBytes.end());
            // Stores the parameters bytes.
            leftOverBytes.insert(leftOverBytes.end(), instructionResult.getReadBytesIfError().begin(), instructionResult.getReadBytesIfError().end());
            break;
        }

        // The Instruction was successfully retrieved. Stores it.
        instructions.push_back(*std::move(instructionAndResult.first));
    }

    return std::make_pair(std::move(instructions), std::move(leftOverBytes));
}

std::vector<int> BinaryParser::buildByteRegion() noexcept
{
    std::vector<int> readBytes;

    // Reads and stores the bytes, as much as we can.
    while (bytesProvider.hasNext()) {
        readBytes.emplace_back(bytesProvider.fetchByte());
    }

    return readBytes;
}

std::pair<std::vector<int>, int> BinaryParser::buildWordRegion() noexcept
{
    std::vector<int> words;
    auto leftOver = -1;

    // First, gets the bytes.
    const auto bytes = buildByteRegion();
    // Gather them in a word.
    size_t index = 0U;
    const auto size = bytes.size();
    while (index + 1U < size) {          // Security because we will get a word.
        auto word = bytes.at(index) + (bytes.at(index + 1U) * 256);     // Little endian.
        words.emplace_back(word);

        index = index + 2U;
    }

    // Any left over?
    if ((size % 2U) != 0U) {
        leftOver = bytes.back();
    }

    return std::make_pair(std::move(words), leftOver);
}

}    // namespace disark
