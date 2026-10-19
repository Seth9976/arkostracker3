#include "RegionDataHolder.h"

#include <juce_core/juce_core.h>

#include "sourceItemVisitor/SourceItemVisitor.h"

namespace disark
{

RegionDataHolder::RegionDataHolder(const int pStartAddress) :
        startAddress(pStartAddress)
{
}

int RegionDataHolder::getStartAddress() const
{
    return startAddress;
}


// CodeRegionDataHolder
// ============================================================

CodeRegionDataHolder::CodeRegionDataHolder(const int pStartAddress, std::pair<std::vector<Instruction>, std::vector<int>> pInstructionAndLeftOverBytes,
                                           const bool pUndocumentedOpcodesAsBytes) noexcept:
        RegionDataHolder(pStartAddress),
        instructions(std::move(pInstructionAndLeftOverBytes.first)),
        leftOverBytes(std::move(pInstructionAndLeftOverBytes.second)),
        undocumentedOpcodesAsBytes(pUndocumentedOpcodesAsBytes)
{
}

const std::vector<Instruction>& CodeRegionDataHolder::getInstructions() const
{
    return instructions;
}

const std::vector<int>& CodeRegionDataHolder::getLeftOverBytes() const
{
    return leftOverBytes;
}

void CodeRegionDataHolder::parseSourceItems(SourceItemVisitor& sourceItemVisitor) const noexcept
{
    auto address = getStartAddress();

    // Encodes each Instruction.
    for (const auto& instruction: instructions) {
        const auto& opcode = instruction.getOpcode();

        // If this instruction undocumented? If yes and if the configuration prevents us from encoding them, encodes them as DB.
        if (!undocumentedOpcodesAsBytes || !instruction.isUndocumented()) {
            // Normal behavior.
            const auto& sourceItems = opcode.getSourceItems();

            const auto instructionSize = opcode.getEncodedSizeWithParameter();
            sourceItemVisitor.visitInstruction(address, instructionSize, sourceItems, instruction.getParameter1(), instruction.getParameter2());

            address += instructionSize;
        } else {
            // The instruction is undocumented, and the user wants to use DB instead.
            for (const auto byte: opcode.getOpcodeBytes()) {
                std::vector sourceItems = { SourceItem::declareByte, SourceItem::value8Bits };
                sourceItemVisitor.visitInstruction(address, 1, sourceItems, byte, -1);

                ++address;
            }

            // The above encoded the instruction bytes, but not the possible index/values (with an exception explained below!).
            // From the original source items, only keeps the ones about dynamic fields.
            const auto& originalSourceItems = opcode.getSourceItems();
            std::vector<SourceItem> sourceItems;
            auto size = 0;
            for (const auto& sourceItem: originalSourceItems) {
                switch (sourceItem) {
                    case SourceItem::signedIndex8Bits:
                        if (opcode.isThreeBytesOpcode()) {
                            // An exception for instruction such as rl (ix+r),b     #dd, #cb, r, #10
                            // The "r" has already been encoded above, no need to encode it again!
                            break;
                        }
                        // Else, fallthrough.
                    case SourceItem::value8Bits: [[fallthrough]];
                    case SourceItem::relativeJump8Bits:
                        sourceItems = { SourceItem::declareByte,
                                        SourceItem::value8Bits };  // Forces to an 8 bits value, to avoid strange looking lines like db +0 (case of ld (ix+0),b).
                        size += 1;
                        break;
                    case SourceItem::value16Bits: [[fallthrough]];
                    case SourceItem::valueRaw16Bits:
                        sourceItems = { SourceItem::declareWord, sourceItem };
                        size += 2;
                        break;
                    case SourceItem::declareByte: [[fallthrough]];
                    case SourceItem::declareWord: [[fallthrough]];
                    case SourceItem::flagZ: [[fallthrough]];
                    case SourceItem::flagNZ: [[fallthrough]];
                    case SourceItem::flagC: [[fallthrough]];
                    case SourceItem::flagNC: [[fallthrough]];
                    case SourceItem::flagP: [[fallthrough]];
                    case SourceItem::flagPE: [[fallthrough]];
                    case SourceItem::flagPO: [[fallthrough]];
                    case SourceItem::flagM: [[fallthrough]];
                    case SourceItem::registerA: [[fallthrough]];
                    case SourceItem::registerF: [[fallthrough]];
                    case SourceItem::registerB: [[fallthrough]];
                    case SourceItem::registerC: [[fallthrough]];
                    case SourceItem::registerD: [[fallthrough]];
                    case SourceItem::registerE: [[fallthrough]];
                    case SourceItem::registerH: [[fallthrough]];
                    case SourceItem::registerL: [[fallthrough]];
                    case SourceItem::registerAF: [[fallthrough]];
                    case SourceItem::registerAFs: [[fallthrough]];
                    case SourceItem::registerBC: [[fallthrough]];
                    case SourceItem::registerBCs: [[fallthrough]];
                    case SourceItem::registerDE: [[fallthrough]];
                    case SourceItem::registerDEs: [[fallthrough]];
                    case SourceItem::registerHL: [[fallthrough]];
                    case SourceItem::registerHLs: [[fallthrough]];
                    case SourceItem::registerIX: [[fallthrough]];
                    case SourceItem::registerIXH: [[fallthrough]];
                    case SourceItem::registerIXL: [[fallthrough]];
                    case SourceItem::registerIY: [[fallthrough]];
                    case SourceItem::registerIYH: [[fallthrough]];
                    case SourceItem::registerIYL: [[fallthrough]];
                    case SourceItem::registerSP: [[fallthrough]];
                    case SourceItem::registerI: [[fallthrough]];
                    case SourceItem::registerR: [[fallthrough]];
                    case SourceItem::closeParenthesis: [[fallthrough]];
                    case SourceItem::comma: [[fallthrough]];
                    case SourceItem::decorative0: [[fallthrough]];
                    case SourceItem::decorative1: [[fallthrough]];
                    case SourceItem::decorative2: [[fallthrough]];
                    case SourceItem::decorative3: [[fallthrough]];
                    case SourceItem::decorative4: [[fallthrough]];
                    case SourceItem::decorative5: [[fallthrough]];
                    case SourceItem::decorative6: [[fallthrough]];
                    case SourceItem::decorative7: [[fallthrough]];
                    case SourceItem::decorative8: [[fallthrough]];
                    case SourceItem::decorative16: [[fallthrough]];
                    case SourceItem::decorative24: [[fallthrough]];
                    case SourceItem::decorative32: [[fallthrough]];
                    case SourceItem::decorative40: [[fallthrough]];
                    case SourceItem::decorative48: [[fallthrough]];
                    case SourceItem::decorative56: [[fallthrough]];
                    case SourceItem::decorativeImmediate: [[fallthrough]];
                    case SourceItem::opcodeNop: [[fallthrough]];
                    case SourceItem::opcodeBit: [[fallthrough]];
                    case SourceItem::opcodeCcf: [[fallthrough]];
                    case SourceItem::opcodeCp: [[fallthrough]];
                    case SourceItem::opcodeCpd: [[fallthrough]];
                    case SourceItem::opcodeCpdr: [[fallthrough]];
                    case SourceItem::opcodeCpi: [[fallthrough]];
                    case SourceItem::opcodeCpir: [[fallthrough]];
                    case SourceItem::opcodeCpl: [[fallthrough]];
                    case SourceItem::opcodeDaa: [[fallthrough]];
                    case SourceItem::opcodeSet: [[fallthrough]];
                    case SourceItem::opcodeSla: [[fallthrough]];
                    case SourceItem::opcodeSll: [[fallthrough]];
                    case SourceItem::opcodeSra: [[fallthrough]];
                    case SourceItem::opcodeSrl: [[fallthrough]];
                    case SourceItem::opcodeRes: [[fallthrough]];
                    case SourceItem::opcodeLd: [[fallthrough]];
                    case SourceItem::opcodeLdd: [[fallthrough]];
                    case SourceItem::opcodeLddr: [[fallthrough]];
                    case SourceItem::opcodeLdi: [[fallthrough]];
                    case SourceItem::opcodeLdir: [[fallthrough]];
                    case SourceItem::opcodeDjnz: [[fallthrough]];
                    case SourceItem::opcodeIm: [[fallthrough]];
                    case SourceItem::opcodeIn: [[fallthrough]];
                    case SourceItem::opcodeInc: [[fallthrough]];
                    case SourceItem::opcodeIndr: [[fallthrough]];
                    case SourceItem::opcodeIni: [[fallthrough]];
                    case SourceItem::opcodeInir: [[fallthrough]];
                    case SourceItem::opcodeInd: [[fallthrough]];
                    case SourceItem::opcodeDec: [[fallthrough]];
                    case SourceItem::opcodeDi: [[fallthrough]];
                    case SourceItem::opcodeEi: [[fallthrough]];
                    case SourceItem::opcodeAdd: [[fallthrough]];
                    case SourceItem::opcodeAnd: [[fallthrough]];
                    case SourceItem::opcodeAdc: [[fallthrough]];
                    case SourceItem::opcodeSub: [[fallthrough]];
                    case SourceItem::opcodeSbc: [[fallthrough]];
                    case SourceItem::opcodeNeg: [[fallthrough]];
                    case SourceItem::opcodeScf: [[fallthrough]];
                    case SourceItem::opcodeOr: [[fallthrough]];
                    case SourceItem::opcodeOut: [[fallthrough]];
                    case SourceItem::opcodeOuti: [[fallthrough]];
                    case SourceItem::opcodeOutd: [[fallthrough]];
                    case SourceItem::opcodeOtdr: [[fallthrough]];
                    case SourceItem::opcodeOtir: [[fallthrough]];
                    case SourceItem::opcodePop: [[fallthrough]];
                    case SourceItem::opcodePush: [[fallthrough]];
                    case SourceItem::opcodeRet: [[fallthrough]];
                    case SourceItem::opcodeReti: [[fallthrough]];
                    case SourceItem::opcodeRetn: [[fallthrough]];
                    case SourceItem::opcodeJp: [[fallthrough]];
                    case SourceItem::opcodeJr: [[fallthrough]];
                    case SourceItem::opcodeCall: [[fallthrough]];
                    case SourceItem::opcodeRst: [[fallthrough]];
                    case SourceItem::opcodeRl: [[fallthrough]];
                    case SourceItem::opcodeRld: [[fallthrough]];
                    case SourceItem::opcodeRr: [[fallthrough]];
                    case SourceItem::opcodeRrd: [[fallthrough]];
                    case SourceItem::opcodeRla: [[fallthrough]];
                    case SourceItem::opcodeRra: [[fallthrough]];
                    case SourceItem::opcodeRlc: [[fallthrough]];
                    case SourceItem::opcodeRrc: [[fallthrough]];
                    case SourceItem::opcodeRlca: [[fallthrough]];
                    case SourceItem::opcodeRrca: [[fallthrough]];
                    case SourceItem::opcodeEx: [[fallthrough]];
                    case SourceItem::opcodeHalt: [[fallthrough]];
                    case SourceItem::opcodeExx: [[fallthrough]];
                    case SourceItem::opcodeXor: [[fallthrough]];
                    case SourceItem::openParenthesis:
                        break;
                }
            }

            if (!sourceItems.empty()) {
                jassert(size > 0);
                sourceItemVisitor.visitInstruction(address, size, sourceItems, instruction.getParameter1(), instruction.getParameter2());

                address += size;
            }
        }
    }

    // Any left-over?
    for (const auto leftOver: leftOverBytes) {
        std::vector sourceItems = { SourceItem::declareByte, SourceItem::value8Bits };
        sourceItemVisitor.visitInstruction(address, 1, sourceItems, leftOver, -1);

        ++address;
    }
}


// ByteRegionDataHolder
// ============================================================

ByteRegionDataHolder::ByteRegionDataHolder(const int pStartAddress, std::vector<int> pBytes) noexcept:
        RegionDataHolder(pStartAddress),
        bytes(std::move(pBytes))
{
}

const std::vector<int>& ByteRegionDataHolder::getBytes() const noexcept
{
    return bytes;
}

void ByteRegionDataHolder::parseSourceItems(SourceItemVisitor& sourceItemVisitor) const noexcept
{
    auto address = getStartAddress();

    // Declares "db x" for each byte.
    for (const auto byte: bytes) {
        std::vector sourceItems = { SourceItem::declareByte, SourceItem::value8Bits };
        sourceItemVisitor.visitInstruction(address, 1, sourceItems, byte, -1);

        ++address;
    }
}


// PointerRegionDataHolder
// ============================================================

PointerRegionDataHolder::PointerRegionDataHolder(const int pStartAddress, const std::pair<std::vector<int>, int>& pWordsAndLeftOver, const bool pReferenceCanBeInferred) noexcept:
        RegionDataHolder(pStartAddress),
        words(pWordsAndLeftOver.first),
        leftOver(pWordsAndLeftOver.second),
        referenceCanBeInferred(pReferenceCanBeInferred)
{
}

const std::vector<int>& PointerRegionDataHolder::getWords() const noexcept
{
    return words;
}

int PointerRegionDataHolder::getLeftOver() const
{
    return leftOver;
}

void PointerRegionDataHolder::parseSourceItems(SourceItemVisitor& sourceItemVisitor) const noexcept
{
    auto address = getStartAddress();

    // Declares "dw x" for each word.
    for (const auto word: words) {
        std::vector sourceItems = { SourceItem::declareWord,
                                                referenceCanBeInferred ? SourceItem::value16Bits : SourceItem::valueRaw16Bits };
        sourceItemVisitor.visitInstruction(address, 2, sourceItems, word, -1);

        address += 2;
    }

    // Any left-over?
    if (leftOver >= 0) {
        const std::vector sourceItems = { SourceItem::declareByte, SourceItem::value8Bits };
        sourceItemVisitor.visitInstruction(address, 1, sourceItems, leftOver, -1);
    }
}

}    // namespace disark
