#include "Opcode.h"

namespace disark
{

Opcode::Opcode(const int pSingleOpcode, std::vector<SourceItem> pSourceItems, const bool pUndocumented) noexcept:
        firstByte(pSingleOpcode),
        secondByte(-1),
        thirdByte(-1),
        signedIndexForThreeBytesOpcodes(-1),
        sourceItems(std::move(pSourceItems)),
        parameterType1(SourceParameterType::absent),      // Set just below.
        parameterType2(SourceParameterType::absent),
        undocumented(pUndocumented)
{
    determineParameterTypes();
}

Opcode::Opcode(const int pFirstByte, const int pSecondByte, std::vector<SourceItem> pSourceItems, const bool pUndocumented) noexcept:
        firstByte(pFirstByte),
        secondByte(pSecondByte),
        thirdByte(-1),
        signedIndexForThreeBytesOpcodes(-1),
        sourceItems(std::move(pSourceItems)),
        parameterType1(SourceParameterType::absent),      // Set just below.
        parameterType2(SourceParameterType::absent),
        undocumented(pUndocumented)
{
    determineParameterTypes();
}

Opcode::Opcode(const int pFirstByte, const int pSecondByte, const int pThirdByte, std::vector<SourceItem> pSourceItems, const bool pUndocumented) noexcept:
        firstByte(pFirstByte),
        secondByte(pSecondByte),
        thirdByte(pThirdByte),
        signedIndexForThreeBytesOpcodes(-1),                  // For now. Set via a setter.
        sourceItems(std::move(pSourceItems)),
        parameterType1(SourceParameterType::signed8bitsIndex),      // Always the same.
        parameterType2(SourceParameterType::absent),
        undocumented(pUndocumented)
{
}

Opcode Opcode::buildError() noexcept
{
    return { -1, -1, -1, { }, false };
}

int Opcode::getFirstByte() const noexcept
{
    return firstByte;
}

int Opcode::getSecondByte() const noexcept
{
    return secondByte;
}

int Opcode::getThirdByte() const noexcept
{
    return thirdByte;
}

bool Opcode::match(const int firstByteParam, const int secondByteParam) const noexcept
{
    jassert((firstByteParam >= 0) && (firstByteParam <= 255));
    jassert((secondByteParam >= 0) && (secondByteParam <= 255));

    return ((firstByte == firstByteParam) && (secondByte == secondByteParam));
}

bool Opcode::match(const int firstByteParam, const int secondByteParam, const int thirdByteParam) const noexcept
{
    jassert((thirdByteParam >= 0) && (thirdByteParam <= 255));

    return ((thirdByte == thirdByteParam) && match(firstByteParam, secondByteParam));
}

SourceParameterType Opcode::getParameterType1() const noexcept
{
    return parameterType1;
}

SourceParameterType Opcode::getParameterType2() const noexcept
{
    return parameterType2;
}

void Opcode::determineParameterTypes() noexcept
{
    auto currentParameterIndex = 0;

    // Parses all the SourceItems.
    for (const auto& sourceItem: sourceItems) {
        if (sourceItem == SourceItem::value16Bits) {
            jassert(currentParameterIndex < 2);
            setParameterType(currentParameterIndex++, SourceParameterType::number16bits);
        } else if (sourceItem == SourceItem::value8Bits) {
            jassert(currentParameterIndex < 2);
            setParameterType(currentParameterIndex++, SourceParameterType::number8bits);
        } else if (sourceItem == SourceItem::relativeJump8Bits) {
            jassert(currentParameterIndex < 2);
            setParameterType(currentParameterIndex++, SourceParameterType::relativeJump8bits);
        } else if (sourceItem == SourceItem::signedIndex8Bits) {
            jassert(currentParameterIndex < 2);
            setParameterType(currentParameterIndex++, SourceParameterType::signed8bitsIndex);
        }
    }
}

void Opcode::setParameterType(const int parameterIndex, const SourceParameterType parameterType) noexcept
{
    jassert((parameterIndex >= 0) && (parameterIndex <= 1));

    auto& parameter = (parameterIndex == 0) ? parameterType1 : parameterType2;
    parameter = parameterType;
}

std::vector<int> Opcode::getOpcodeBytes() const noexcept
{
    jassert(firstByte >= 0);

    std::vector<int> bytes;
    bytes.emplace_back(firstByte);

    if (secondByte >= 0) {
        bytes.emplace_back(secondByte);

        if (thirdByte >= 0) {
            // Also codes the signed index!
            bytes.emplace_back(signedIndexForThreeBytesOpcodes);
            bytes.emplace_back(thirdByte);
        }
    } else {
        // If there is no second byte, there is no third!
        jassert(thirdByte < 0);
    }

    return bytes;
}

const std::vector<SourceItem>& Opcode::getSourceItems() const noexcept
{
    jassert(!sourceItems.empty());

    return sourceItems;
}

int Opcode::getEncodedSizeWithParameter() const noexcept
{
    return getOpcodeSize() + getParameterEncodingSize(parameterType1) + getParameterEncodingSize(parameterType2);
}

int Opcode::getParameterEncodingSize(const SourceParameterType parameterType) noexcept
{
    switch (parameterType) {
        case SourceParameterType::signed8bitsIndex: [[fallthrough]];
        case SourceParameterType::number8bits: [[fallthrough]];
        case SourceParameterType::relativeJump8bits:
            return 1;
        case SourceParameterType::number16bits:
            return 2;
        case SourceParameterType::absent: [[fallthrough]];
        default:
            return 0;
    }
}

int Opcode::getOpcodeSize() const noexcept
{
    jassert(firstByte >= 0);

    auto result = 1;     // At least one opcode!
    if (secondByte >= 0) {
        ++result;
        if (thirdByte >= 0) {
            ++result;
        }
    }
    return result;
}

bool Opcode::isThreeBytesOpcode() const noexcept
{
    return (firstByte >= 0) && (secondByte >= 0) && (thirdByte >= 0);
}

int Opcode::getSignedIndexForThreeBytesOpcode() const noexcept
{
    jassert(isThreeBytesOpcode());      // If raised, it means this was called for something else than a 3-bytes opcode, which is abnormal.
    return signedIndexForThreeBytesOpcodes;
}

void Opcode::setSignedIndexForThreeBytesOpcode(const int signedIndex) noexcept
{
    jassert(isThreeBytesOpcode());      // If raised, it means this was called for something else than a 3-bytes opcode, which is abnormal.
    signedIndexForThreeBytesOpcodes = signedIndex;
}

bool Opcode::isUndocumented() const noexcept
{
    return undocumented;
}

}    // namespace disark
