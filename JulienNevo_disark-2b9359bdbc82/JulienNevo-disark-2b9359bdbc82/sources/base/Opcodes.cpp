#include "Opcodes.h"

#include "../utils/MapUtil.h"
#include "ExportConfiguration.h"
#include "OpcodesFiller.h"
#include "SourceItem.h"

namespace disark
{

Opcodes::Opcodes(const ExportConfiguration& pExportConfiguration) noexcept:
        exportConfiguration(pExportConfiguration),
        firstByteToOpcodes()
{
    // Delegates the declaration of opcodes to another object.
    OpcodesFiller opcodesFiller(exportConfiguration, *this);
    opcodesFiller.fillOpcodes();

    jassert(firstByteToOpcodes.size() == 256U);
}

void Opcodes::addOpcode(const Opcode& opcode) noexcept
{
    // The main opcode is the key in the map.
    const auto opcodeValue = opcode.getFirstByte();
    jassert((opcodeValue >= 0) && (opcodeValue <= 255));
    MapUtil::addValueToMapOfListOfValues(firstByteToOpcodes, opcodeValue, opcode);
}

const Opcode* Opcodes::search(const int byte) const noexcept
{
    const auto& opcodes = findOpcodesFromFirstByte(byte);
    // Several opcodes: don't choose in this method.
    if (opcodes.size() > 1U) {
        return nullptr;
    }

    // Only one: selects it.
    return &opcodes.front();
}

const Opcode* Opcodes::search(const int firstByte, const int secondByte, bool& errorIllegalCombination) const noexcept
{
    errorIllegalCombination = false;

    const auto& opcodes = findOpcodesFromFirstByte(firstByte);

    // This is the second pass, so there must have been at least two opcodes to choose from!
    jassert(opcodes.size() > 1U);
    // Which one matches? If more than one, we can't decide now.
    auto matchFoundCount = 0;
    const Opcode* lastMatchingOpcode = nullptr;
    for (const auto& opcode: opcodes) {
        if (opcode.match(firstByte, secondByte)) {
            // This opcode matches. Keeps its reference, in case it is the only one, we can directly return it.
            ++matchFoundCount;
            lastMatchingOpcode = &opcode;
        }
    }

    // Any match?
    if (lastMatchingOpcode != nullptr) {
        jassert(matchFoundCount > 0);
        // If one match, choose it. If too many, we will need a third opcode.
        return (matchFoundCount == 1) ? lastMatchingOpcode : nullptr;
    }

    // None matches! It means this is a illegal combination.
    errorIllegalCombination = true;
    return nullptr;
}

const Opcode* Opcodes::search(const int firstByte, const int secondByte, const int thirdByte, bool& errorIllegalCombination) const noexcept
{
    errorIllegalCombination = false;

    const auto& opcodes = findOpcodesFromFirstByte(firstByte);

    // This is the third pass, so there must have been at least two opcodes to choose from!
    jassert(opcodes.size() > 1U);
    // Which one matches? If more than one, we can't decide now.
    for (const auto& opcode: opcodes) {
        if (opcode.match(firstByte, secondByte, thirdByte)) {
            // This opcode matches. We can stop.
            return &opcode;
        }
    }

    // None matches! It means this is a illegal combination.
    errorIllegalCombination = true;
    return nullptr;
}

const std::vector<Opcode>& Opcodes::findOpcodesFromFirstByte(const int firstByte) const noexcept
{
    // Gets the opcode(s) starting with the first byte.
    // None should be impossible, unless I forgot to encode one!
    // If several, it means there are several opcodes, so a second byte is needed.
    auto iterator = firstByteToOpcodes.find(firstByte);
    if (iterator == firstByteToOpcodes.cend()) {
        jassertfalse;               // Must not happen! You forgot to encode an opcode, you daft git!
    }

    const auto& opcodes = iterator->second;
    jassert(!opcodes.empty());

    return opcodes;
}

void Opcodes::parseAndAddOpcode(int firstByte, const juce::String& expression) noexcept
{
    jassert(firstByteToOpcodes.find(firstByte) == firstByteToOpcodes.cend());       // One-byte opcodes are unique!
    bool undocumented;      // NOLINT(*-init-variables)
    const auto& sourceItems = parse(expression, undocumented);
    addOpcode({ firstByte, sourceItems, undocumented });
}

void Opcodes::parseAndAddOpcode(int firstByte, int secondByte, const juce::String& expression) noexcept
{
    bool undocumented;      // NOLINT(*-init-variables)
    const auto& sourceItems = parse(expression, undocumented);
    addOpcode({ firstByte, secondByte, sourceItems, undocumented });
}

void Opcodes::parseAndAddOpcode(int firstByte, int secondByte, int thirdByte, const juce::String& expression) noexcept
{
    bool undocumented;      // NOLINT(*-init-variables)
    const auto& sourceItems = parse(expression, undocumented);
    addOpcode({ firstByte, secondByte, thirdByte, sourceItems, undocumented });
}

std::vector<SourceItem> Opcodes::parse(const juce::String& inputExpression, bool& undocumented) const noexcept
{
    // Removed unwanted chars, just in case.
    auto expression = inputExpression.trim().toLowerCase();

    // Starts with a "*"? If yes, it means "undocumented".
    undocumented = expression.startsWith("*");
    auto charIndex = undocumented ? 1 : 0;       // Skips the "*".

    std::vector<SourceItem> sourceItems;

    // Maps linking every "word" found to SourceItem.
    // Handy, but the limitation is that every word must be different, so expressing different meaning from one word is not possible (see FlagC for example).
    static const std::map<juce::String, SourceItem> stringToSourceItem = {
            { "n",    SourceItem::value8Bits },
            { "nn",   SourceItem::value16Bits },
            { "+d",   SourceItem::signedIndex8Bits },
            { "+e",   SourceItem::relativeJump8Bits },

            { "(",    SourceItem::openParenthesis },
            { ")",    SourceItem::closeParenthesis },
            { ",",    SourceItem::comma },

            { "0",    SourceItem::decorative0 },
            { "1",    SourceItem::decorative1 },
            { "2",    SourceItem::decorative2 },
            { "3",    SourceItem::decorative3 },
            { "4",    SourceItem::decorative4 },
            { "5",    SourceItem::decorative5 },
            { "6",    SourceItem::decorative6 },
            { "7",    SourceItem::decorative7 },
            { "8",    SourceItem::decorative8 },
            { "16",   SourceItem::decorative16 },
            { "24",   SourceItem::decorative24 },
            { "32",   SourceItem::decorative32 },
            { "40",   SourceItem::decorative40 },
            { "48",   SourceItem::decorative48 },
            { "56",   SourceItem::decorative56 },

            { "z",    SourceItem::flagZ },
            { "nz",   SourceItem::flagNZ },
            { "cc",   SourceItem::flagC },           // No choice... Must be different from the register C.
            { "nc",   SourceItem::flagNC },
            { "p",    SourceItem::flagP },
            { "pe",   SourceItem::flagPE },
            { "po",   SourceItem::flagPO },
            { "m",    SourceItem::flagM },

            { "a",    SourceItem::registerA },
            { "b",    SourceItem::registerB },
            { "c",    SourceItem::registerC },
            { "d",    SourceItem::registerD },
            { "e",    SourceItem::registerE },
            { "h",    SourceItem::registerH },
            { "l",    SourceItem::registerL },
            { "f",    SourceItem::registerF },
            { "af",   SourceItem::registerAF },
            { "af'",  SourceItem::registerAFs },
            { "hl",   SourceItem::registerHL },
            { "hl'",  SourceItem::registerHLs },
            { "de",   SourceItem::registerDE },
            { "de'",  SourceItem::registerDEs },
            { "bc",   SourceItem::registerBC },
            { "bc'",  SourceItem::registerBCs },
            { "ix",   SourceItem::registerIX },
            { "ixl",  SourceItem::registerIXL },
            { "ixh",  SourceItem::registerIXH },
            { "iy",   SourceItem::registerIY },
            { "iyl",  SourceItem::registerIYL },
            { "iyh",  SourceItem::registerIYH },
            { "sp",   SourceItem::registerSP },
            { "i",    SourceItem::registerI },
            { "r",    SourceItem::registerR },

            { "adc",  SourceItem::opcodeAdc },
            { "add",  SourceItem::opcodeAdd },
            { "and",  SourceItem::opcodeAnd },
            { "bit",  SourceItem::opcodeBit },
            { "call", SourceItem::opcodeCall },
            { "ccf",  SourceItem::opcodeCcf },
            { "cp",   SourceItem::opcodeCp },
            { "cpd",  SourceItem::opcodeCpd },
            { "cpdr", SourceItem::opcodeCpdr },
            { "cpi",  SourceItem::opcodeCpi },
            { "cpir", SourceItem::opcodeCpir },
            { "cpl",  SourceItem::opcodeCpl },
            { "daa",  SourceItem::opcodeDaa },
            { "dec",  SourceItem::opcodeDec },
            { "di",   SourceItem::opcodeDi },
            { "djnz", SourceItem::opcodeDjnz },
            { "ei",   SourceItem::opcodeEi },
            { "ex",   SourceItem::opcodeEx },
            { "exx",  SourceItem::opcodeExx },
            { "halt", SourceItem::opcodeHalt },
            { "im",   SourceItem::opcodeIm },
            { "in",   SourceItem::opcodeIn },
            { "ind",  SourceItem::opcodeInd },
            { "inc",  SourceItem::opcodeInc },
            { "indr", SourceItem::opcodeIndr },
            { "ini",  SourceItem::opcodeIni },
            { "inir", SourceItem::opcodeInir },
            { "jr",   SourceItem::opcodeJr },
            { "jp",   SourceItem::opcodeJp },
            { "ld",   SourceItem::opcodeLd },
            { "ldd",  SourceItem::opcodeLdd },
            { "lddr", SourceItem::opcodeLddr },
            { "ldi",  SourceItem::opcodeLdi },
            { "ldir", SourceItem::opcodeLdir },
            { "neg",  SourceItem::opcodeNeg },
            { "nop",  SourceItem::opcodeNop },
            { "or",   SourceItem::opcodeOr },
            { "out",  SourceItem::opcodeOut },
            { "outi", SourceItem::opcodeOuti },
            { "outd", SourceItem::opcodeOutd },
            { "otdr", SourceItem::opcodeOtdr },
            { "otir", SourceItem::opcodeOtir },
            { "pop",  SourceItem::opcodePop },
            { "push", SourceItem::opcodePush },
            { "res",  SourceItem::opcodeRes },
            { "ret",  SourceItem::opcodeRet },
            { "reti", SourceItem::opcodeReti },
            { "retn", SourceItem::opcodeRetn },
            { "rl",   SourceItem::opcodeRl },
            { "rla",  SourceItem::opcodeRla },
            { "rlc",  SourceItem::opcodeRlc },
            { "rlca", SourceItem::opcodeRlca },
            { "rld",  SourceItem::opcodeRld },
            { "rr",   SourceItem::opcodeRr },
            { "rra",  SourceItem::opcodeRra },
            { "rrc",  SourceItem::opcodeRrc },
            { "rrca", SourceItem::opcodeRrca },
            { "rrd",  SourceItem::opcodeRrd },
            { "rst",  SourceItem::opcodeRst },
            { "sbc",  SourceItem::opcodeSbc },
            { "scf",  SourceItem::opcodeScf },
            { "set",  SourceItem::opcodeSet },
            { "sla",  SourceItem::opcodeSla },
            { "sll",  SourceItem::opcodeSll },
            { "sra",  SourceItem::opcodeSra },
            { "srl",  SourceItem::opcodeSrl },
            { "sub",  SourceItem::opcodeSub },
            { "xor",  SourceItem::opcodeXor },
    };

    // Looks for all the next words.
    auto nextWord = readNextWord(expression, charIndex);
    while (nextWord.isNotEmpty()) {
        jassert(stringToSourceItem.find(nextWord) != stringToSourceItem.cend());        // You forgot to declare this above! Ooops!
        auto opcodeSourceItem = stringToSourceItem.find(nextWord)->second;              // Don't even test the presence: it is crash, so be it, shouldn't happen!
        sourceItems.emplace_back(opcodeSourceItem);

        nextWord = readNextWord(expression, charIndex);
    }

    // SDCC does not like (IY +d) -> +d (IY).
    // Have a pass to change them, if relevant.
    if (exportConfiguration.isSdccRelativeRegisterSyntaxUsed()) {
        manageSdccRelativeRegister(sourceItems);
    }


    // Manages some SDCC boring special cases.
    // If ",n" or ",nn", then add an immediate symbol ("#") in between, but only for some specific opcodes (NOT for JP, CALL, etc.).
    if (exportConfiguration.getImmediateDataDeclarationSymbol().isNotEmpty()) {
        manageImmediateDataDeclaration(sourceItems);
    }

    return sourceItems;
}

void Opcodes::manageImmediateDataDeclaration(std::vector<SourceItem>& sourceItems) noexcept
{
    const auto size = sourceItems.size();
    jassert(size > 0U);

    // Filters the opcode. Only a few accept Immediates on the second member.
    const auto& opcode = sourceItems.front();
    static const std::vector<SourceItem> acceptedSourceItems = {
            SourceItem::opcodeAdc,
            SourceItem::opcodeAdd,
            SourceItem::opcodeAnd,
            SourceItem::opcodeCp,
            SourceItem::opcodeDec,
            SourceItem::opcodeInc,
            SourceItem::opcodeLd,
            SourceItem::opcodeOr,
            SourceItem::opcodeSub,
            SourceItem::opcodeSbc,
            SourceItem::opcodeXor,
    };
    if (std::find(acceptedSourceItems.begin(), acceptedSourceItems.end(), opcode) == acceptedSourceItems.cend()) {
        // Nothing to do!
        return;
    }

    // Is there a comma and a "n" or "nn" after?
    auto foundComma = false;
    for (size_t index = 1U; index < size; ++index) {
        foundComma = (sourceItems.at(index) == SourceItem::comma);
        if (foundComma) {
            const auto indexAfterComma = index + 1U;
            jassert(size > indexAfterComma);       // After a comma, there must be at least another item!

            const auto& itemAfterComma = sourceItems.at(indexAfterComma);

            if ((itemAfterComma == SourceItem::value8Bits)
                || (itemAfterComma == SourceItem::value16Bits)
                || (itemAfterComma == SourceItem::valueRaw16Bits)) {
                // Inserts a "#" symbol here.
                sourceItems.insert(sourceItems.begin() + static_cast<int64_t>(indexAfterComma), SourceItem::decorativeImmediate);
            }
            break;      // Whatever happens, we can stop this loop.
        }
    }

    if (foundComma) {
        return;
    }

    // There is no comma. Simple case of "sub n" for example
    if (size == 2U) {        // Opcode plus value.
        constexpr auto secondIndexIndex = 1;
        const auto secondItem = sourceItems.at(static_cast<size_t>(secondIndexIndex));
        if ((secondItem == SourceItem::value8Bits)
            || (secondItem == SourceItem::value16Bits)
            || (secondItem == SourceItem::valueRaw16Bits)) {
            // Inserts a "#" symbol here.
            sourceItems.insert(sourceItems.begin() + secondIndexIndex, SourceItem::decorativeImmediate);
        }
    }
}

void Opcodes::manageSdccRelativeRegister(std::vector<SourceItem>& sourceItems) noexcept
{
    static const std::vector<SourceItem> sourceItemsIXToFind = { SourceItem::openParenthesis, SourceItem::registerIX, SourceItem::signedIndex8Bits, SourceItem::closeParenthesis };
    static const std::vector<SourceItem> sourceItemsIYToFind = { SourceItem::openParenthesis, SourceItem::registerIY, SourceItem::signedIndex8Bits, SourceItem::closeParenthesis };

    static const std::vector<SourceItem> sourceItemsIXReplacement = { SourceItem::signedIndex8Bits, SourceItem::openParenthesis, SourceItem::registerIX,
                                                                      SourceItem::closeParenthesis };
    static const std::vector<SourceItem> sourceItemsIYReplacement = { SourceItem::signedIndex8Bits, SourceItem::openParenthesis, SourceItem::registerIY,
                                                                      SourceItem::closeParenthesis };

    auto found = findAndReplaceIfFoundRelativeRegister(sourceItems, sourceItemsIXToFind, sourceItemsIXReplacement);
    if (!found) {
        findAndReplaceIfFoundRelativeRegister(sourceItems, sourceItemsIYToFind, sourceItemsIYReplacement);
    }
}

bool Opcodes::findAndReplaceIfFoundRelativeRegister(std::vector<SourceItem>& sourceItems, const std::vector<SourceItem>& sequenceToFind,
                                                    const std::vector<SourceItem>& replacementSequence) noexcept
{
    auto found = false;

    // Is the sequence to find present in the SourceItems?
    auto iterator = std::search(sourceItems.begin(), sourceItems.end(), sequenceToFind.begin(), sequenceToFind.end());
    if (iterator != sourceItems.cend()) {
        // Yes: replaces it with the replacement sequence.
        std::copy_n(replacementSequence.begin(), replacementSequence.size(), iterator);
        found = true;
    }

    return found;
}

juce::String Opcodes::readNextWord(const juce::String& expression, int& charIndex) noexcept
{
    const auto length = expression.length();

    // Skips the spaces.
    while ((charIndex < length) && (expression[charIndex] == ' ')) {
        ++charIndex;
    }

    // Any simple char following?
    if (charIndex < length) {
        const auto foundChar = expression[charIndex];
        switch (foundChar) {
            case '(': {
                ++charIndex;
                return "(";
            }
            case ')': {
                ++charIndex;
                return ")";
            }
            case ',': {
                ++charIndex;
                return ",";
            }
            default:
                break;
        }
    } else {
        // End of expression.
        return "";
    }

    // Parses the next chars till a separator is found.
    // We know we haven't reached the end yet.
    juce::String result = "";
    auto foundChar = expression[charIndex];
    do {
        result += foundChar;

        foundChar = expression[++charIndex];
    } while ((charIndex < length) && (foundChar != '(') && (foundChar != ')') && (foundChar != ',') && (foundChar != ' '));

    return result;
}

}    // namespace disark
