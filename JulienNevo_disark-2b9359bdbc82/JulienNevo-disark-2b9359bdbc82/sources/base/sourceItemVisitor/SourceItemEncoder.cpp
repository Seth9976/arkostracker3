#include "SourceItemEncoder.h"

#include "../../utils/CollectionUtil.h"
#include "../ExportConfiguration.h"
#include "../References.h"
#include "../WriterUtils.h"

namespace disark
{

SourceItemEncoder::SourceItemEncoder(References& pReferences, juce::OutputStream& pOutputStream, const ExportConfiguration& pConfiguration) noexcept :
    SourceItemVisitor(pReferences),
    configuration(pConfiguration),
    outputStream(pOutputStream)
{
}

void SourceItemEncoder::visitInstruction(int address, int instructionSize, const std::vector<SourceItem>& sourceItems, int parameter1Value, int parameter2Value) const noexcept
{
    jassert((instructionSize > 0) && (instructionSize < 8));
    jassert(!sourceItems.empty());      // Sanity check, abnormal.
    if (sourceItems.empty()) {
        return;
    }

    // A corner case for Vasm: it doesn't accept a Set is a label is before. If that's the case, force a return-carriage.
    auto forceReturnCarriageAfterLabel = (configuration.isNoLabelBeforeSetInstruction() && (sourceItems.front() == SourceItem::opcodeSet));

    // Are there labels here?
    auto result = manageLabels(address, instructionSize, forceReturnCarriageAfterLabel);

    std::array<int, 2U> parameters = { parameter1Value, parameter2Value };
    size_t currentParameterIndex = 0U;

    const auto postOpcodeSeparator = configuration.getMnemonicPostfix();
    
    // Parses all the Source Items, encodes each of them.
    // WARNING: whenever a parameter is read, the index must be increased.
    for (const auto& sourceItem : sourceItems) {
        switch (sourceItem) {
            case SourceItem::declareByte:
                result += configuration.getDeclareByteMnemonic() + postOpcodeSeparator;
                break;
            case SourceItem::declareWord:
                result += configuration.getDeclareWordMnemonic() + postOpcodeSeparator;
                break;

            case SourceItem::value8Bits:
                result += encode8BitsNumber(parameters.at(currentParameterIndex++));
                break;
            case SourceItem::value16Bits: [[fallthrough]];
            case SourceItem::valueRaw16Bits: {
                // Can we use a reference here? This "area" might be marked as "don't reference".
                // Also, raw value don't want to references to be inferred.
                auto referencingType = (sourceItem == SourceItem::valueRaw16Bits) ? ReferencingType::forceNonReference
                                           : references.getReferencingType(address);       // The first address only is used. Is it a problem?

                result += encode16BitsNumber(parameters.at(currentParameterIndex++), referencingType);
                break;
            }
            case SourceItem::relativeJump8Bits:
                result += encode8BitRelativeJump(address, parameters.at(currentParameterIndex++));
                break;
            case SourceItem::signedIndex8Bits:
                result += encodeUnsigned8BitsToSignedNumber(parameters.at(currentParameterIndex++));
                break;

            case SourceItem::openParenthesis:
                result += "(";
                break;
            case SourceItem::closeParenthesis:
                result += ")";
                break;
            case SourceItem::comma:
                result += ",";
                break;

            // Flags.
            case SourceItem::flagC: result += "c"; break;
            case SourceItem::flagNC: result += "nc"; break;
            case SourceItem::flagP: result += "p"; break;
            case SourceItem::flagPE: result += "pe"; break;
            case SourceItem::flagPO: result += "po"; break;
            case SourceItem::flagM: result += "m"; break;
            case SourceItem::flagZ: result += "z"; break;
            case SourceItem::flagNZ: result += "nz"; break;

            case SourceItem::decorative0: result += "0"; break;
            case SourceItem::decorative1: result += "1"; break;
            case SourceItem::decorative2: result += "2"; break;
            case SourceItem::decorative3: result += "3"; break;
            case SourceItem::decorative4: result += "4"; break;
            case SourceItem::decorative5: result += "5"; break;
            case SourceItem::decorative6: result += "6"; break;
            case SourceItem::decorative7: result += "7"; break;
            case SourceItem::decorative8: result += "8"; break;
            case SourceItem::decorative16: result += "16"; break;
            case SourceItem::decorative24: result += "24"; break;
            case SourceItem::decorative32: result += "32"; break;
            case SourceItem::decorative40: result += "40"; break;
            case SourceItem::decorative48: result += "48"; break;
            case SourceItem::decorative56: result += "56"; break;
            case SourceItem::decorativeImmediate: result += configuration.getImmediateDataDeclarationSymbol(); break;

                // Opcodes.
            case SourceItem::opcodeNop: result += "nop"; break;
            case SourceItem::opcodeBit: result += "bit" + postOpcodeSeparator; break;
            case SourceItem::opcodeCcf: result += "ccf" + postOpcodeSeparator; break;
            case SourceItem::opcodeCp: result += "cp" + postOpcodeSeparator; break;
            case SourceItem::opcodeCpd: result += "cpd" + postOpcodeSeparator; break;
            case SourceItem::opcodeCpdr: result += "cpdr" + postOpcodeSeparator; break;
            case SourceItem::opcodeCpi: result += "cpi" + postOpcodeSeparator; break;
            case SourceItem::opcodeCpir: result += "cpir" + postOpcodeSeparator; break;
            case SourceItem::opcodeCpl: result += "cpl" + postOpcodeSeparator; break;
            case SourceItem::opcodeDaa: result += "daa"; break;
            case SourceItem::opcodeSet: result += "set" + postOpcodeSeparator; break;
            case SourceItem::opcodeSla: result += "sla" + postOpcodeSeparator; break;
            case SourceItem::opcodeSll: result += "sll" + postOpcodeSeparator; break;
            case SourceItem::opcodeSra: result += "sra" + postOpcodeSeparator; break;
            case SourceItem::opcodeSrl: result += "srl" + postOpcodeSeparator; break;
            case SourceItem::opcodeRes: result += "res" + postOpcodeSeparator; break;
            case SourceItem::opcodeLd: result += "ld" + postOpcodeSeparator; break;
            case SourceItem::opcodeLdd: result += "ldd"; break;
            case SourceItem::opcodeLddr: result += "lddr"; break;
            case SourceItem::opcodeLdi: result += "ldi"; break;
            case SourceItem::opcodeLdir: result += "ldir"; break;
            case SourceItem::opcodeDjnz: result += "djnz" + postOpcodeSeparator; break;
            case SourceItem::opcodeIm: result += "im" + postOpcodeSeparator; break;
            case SourceItem::opcodeIn: result += "in" + postOpcodeSeparator; break;
            case SourceItem::opcodeInc: result += "inc" + postOpcodeSeparator; break;
            case SourceItem::opcodeIndr: result += "indr" + postOpcodeSeparator; break;
            case SourceItem::opcodeIni: result += "ini"; break;
            case SourceItem::opcodeInir: result += "inir"; break;
            case SourceItem::opcodeInd: result += "ind"; break;
            case SourceItem::opcodeDec: result += "dec" + postOpcodeSeparator; break;
            case SourceItem::opcodeDi: result += "di"; break;
            case SourceItem::opcodeEi: result += "ei"; break;
            case SourceItem::opcodeAdd: result += "add" + postOpcodeSeparator; break;
            case SourceItem::opcodeAnd: result += "and" + postOpcodeSeparator; break;
            case SourceItem::opcodeAdc: result += "adc" + postOpcodeSeparator; break;
            case SourceItem::opcodeSub: result += "sub" + postOpcodeSeparator; break;
            case SourceItem::opcodeSbc: result += "sbc" + postOpcodeSeparator; break;
            case SourceItem::opcodeNeg: result += "neg"; break;
            case SourceItem::opcodeScf: result += "scf"; break;
            case SourceItem::opcodeOr: result += "or" + postOpcodeSeparator; break;
            case SourceItem::opcodeOut: result += "out" + postOpcodeSeparator; break;
            case SourceItem::opcodeOuti: result += "outi"; break;
            case SourceItem::opcodeOutd: result += "outd"; break;
            case SourceItem::opcodeOtdr: result += "otdr"; break;
            case SourceItem::opcodeOtir: result += "otir"; break;
            case SourceItem::opcodePop: result += "pop" + postOpcodeSeparator; break;
            case SourceItem::opcodePush: result += "push" + postOpcodeSeparator; break;
            case SourceItem::opcodeRet: result += "ret" + postOpcodeSeparator; break;       // Space needed because may be followed by a flag.
            case SourceItem::opcodeReti: result += "reti"; break;
            case SourceItem::opcodeRetn: result += "retn"; break;
            case SourceItem::opcodeJp: result += "jp" + postOpcodeSeparator; break;
            case SourceItem::opcodeJr: result += "jr" + postOpcodeSeparator; break;
            case SourceItem::opcodeCall: result += "call" + postOpcodeSeparator; break;
            case SourceItem::opcodeRst: result += "rst" + postOpcodeSeparator; break;
            case SourceItem::opcodeRl: result += "rl" + postOpcodeSeparator; break;
            case SourceItem::opcodeRld: result += "rld" + postOpcodeSeparator; break;
            case SourceItem::opcodeRr: result += "rr" + postOpcodeSeparator; break;
            case SourceItem::opcodeRrd: result += "rrd" + postOpcodeSeparator; break;
            case SourceItem::opcodeRla: result += "rla" + postOpcodeSeparator; break;
            case SourceItem::opcodeRra: result += "rra" + postOpcodeSeparator; break;
            case SourceItem::opcodeRlc: result += "rlc" + postOpcodeSeparator; break;
            case SourceItem::opcodeRrc: result += "rrc" + postOpcodeSeparator; break;
            case SourceItem::opcodeRlca: result += "rlca" + postOpcodeSeparator; break;
            case SourceItem::opcodeRrca: result += "rrca" + postOpcodeSeparator; break;
            case SourceItem::opcodeEx: result += "ex" + postOpcodeSeparator; break;
            case SourceItem::opcodeHalt: result += "halt"; break;
            case SourceItem::opcodeExx: result += "exx"; break;
            case SourceItem::opcodeXor: result += "xor" + postOpcodeSeparator; break;

            // Registers.
            case SourceItem::registerA: result += "a"; break;
            case SourceItem::registerF: result += "f"; break;
            case SourceItem::registerB: result += "b"; break;
            case SourceItem::registerC: result += "c"; break;
            case SourceItem::registerD: result += "d"; break;
            case SourceItem::registerE: result += "e"; break;
            case SourceItem::registerH: result += "h"; break;
            case SourceItem::registerL: result += "l"; break;
            case SourceItem::registerI: result += "i"; break;
            case SourceItem::registerR: result += "r"; break;
            case SourceItem::registerHL: result += "hl"; break;
            case SourceItem::registerDE: result += "de"; break;
            case SourceItem::registerBC: result += "bc"; break;
            case SourceItem::registerAF: result += "af"; break;
            case SourceItem::registerAFs: result += "af'"; break;
            case SourceItem::registerIX: result += "ix"; break;
            case SourceItem::registerIXL: result += "ixl"; break;
            case SourceItem::registerIXH: result += "ixh"; break;
            case SourceItem::registerIY: result += "iy"; break;
            case SourceItem::registerIYL: result += "iyl"; break;
            case SourceItem::registerIYH: result += "iyh"; break;
            case SourceItem::registerSP: result += "sp"; break;

            case SourceItem::registerBCs: [[fallthrough]];
            case SourceItem::registerDEs: [[fallthrough]];
            case SourceItem::registerHLs: [[fallthrough]];
            default:
                jassertfalse;           // Should never happen!
                result += "Internal error, source item unknown.";
                break;
        }
    }

    manageComments(address, result);

    WriterUtils::writeString(outputStream, result);
}

juce::String SourceItemEncoder::manageLabels(const int startAddress, const int instructionSize, const bool forceReturnCarriageAfterLabel) const noexcept
{
    // Is there any label that could be "stuck" between the first byte and the last (both excluded)? If yes, they should be encoded,
    // else they will never be.
    // Instruction of 1 will be automatically skipped.
    // The format is: <label> equ $+1
    for (auto address = startAddress + 1, endAddress = startAddress + instructionSize; address < endAddress; ++address) {
        auto labels = references.getExactReferences(address);
        for (const auto& label : labels) {
            // SkipPostFix is used only for "equ", SDCC.
            const auto skipPostFix = configuration.isNoPostFixAfterLabelWithEqu();

            const auto& labelName = label.getName();
            auto labelDeclaration = WriterUtils::getLabelForDeclaration(configuration, labelName, label.isExternal(), skipPostFix);
            auto result = WriterUtils::getLabelDeclarationWithoutValue(configuration, labelDeclaration);

            const auto offset = address - startAddress;
            jassert(offset > 0);
            // Adds "$+x".
            result += configuration.getCurrentAddressSymbol() + WriterUtils::getStringForDecimalNumber(configuration, offset, true);      // Forces the "+".

            WriterUtils::writeString(outputStream, result);

            // This label is now declared.
            references.markLabelAsDeclared(labelName);
        }
    }

    juce::String result;
    // Any labels at this location? There may be multiple ones.
    auto labels = references.getExactReferences(startAddress);
    // If the user doesn't want external labels (no SDCC), do not encode them. Filters them.
    if (!configuration.isGenerateExternalLabels()) {
        CollectionUtil::removeIfAndResize(labels, [](const auto& label) { return label.isExternal(); }  );
    }

    const auto labelCount = static_cast<int>(labels.size());
    if (labelCount > 0) {
        // Writes the labels. Only the last one doesn't have a return carriage.
        auto labelIndex = 0;
        for (const auto& label : labels) {
            const auto& originalLabelName = label.getName();
            const auto labelName = WriterUtils::getLabelForDeclaration(configuration, originalLabelName, label.isExternal(), false);

            if (labelIndex == (labelCount - 1)) {
                result += labelName;
                // Last label. There will be an instruction after, so writes a separator.
                if (!forceReturnCarriageAfterLabel) {
                    result += " ";
                } else {
                    // We are asked to force a return-carriage after the last label. Also adds a tabulation for the next instruction.
                    WriterUtils::writeString(outputStream, labelName);
                    result = configuration.getTabulation();
                }
            } else {
                // Not the last one. Writes only the label.
                WriterUtils::writeString(outputStream, labelName);
            }
            ++labelIndex;

            // This label is now declared.
            references.markLabelAsDeclared(originalLabelName);
        }
    } else {
        // No label: adds a tabulation.
        result += configuration.getTabulation();
    }

    return result;
}

juce::String SourceItemEncoder::encode8BitsNumber(const int value) const noexcept
{
    jassert((value >= 0) && (value <= 255));

    return configuration.isEncode8BitNumberAsHex()
        ? (configuration.getPreHexSymbol() + juce::String::toHexString(value) + configuration.getPostHexSymbol())
        : (configuration.getPreDecimalSymbol() + juce::String(value) + configuration.getPostDecimalSymbol());
}

juce::String SourceItemEncoder::encodeUnsigned8BitsToSignedNumber(const int value) const noexcept
{
    jassert((value >= 0) && (value <= 257));            // 257, not 255, because JR is shifted of 2, but index for IX are not. Not perfect, oh well...

    const auto c = static_cast<signed char>(value);                        // Converts the unsigned number to signed.
    return encodeSigned8BitsToNumber(c);
}

juce::String SourceItemEncoder::encodeSigned8BitsToNumber(const int value) const noexcept
{
    return WriterUtils::getStringForDecimalNumber(configuration, value, true);
}

juce::String SourceItemEncoder::encode16BitsNumber(const int value, const ReferencingType referencingType) const noexcept
{
    jassert((value >= 0) && (value <= 65535));

    // Can a reference be used? Only if wanted.
    auto labelWithOffset = (referencingType == ReferencingType::forceNonReference) ? juce::String()
                               : tryToGetReferenceAndIncreaseReferenceCounter(value, (referencingType == ReferencingType::forceReference));
    // If no reference. Encodes the parameter raw.
    return labelWithOffset.isNotEmpty() ? labelWithOffset : WriterUtils::getHexStringFromNumber(configuration, value);
}

juce::String SourceItemEncoder::encode8BitRelativeJump(const int currentAddress, const int unsignedValue) const noexcept
{
    jassert((unsignedValue >= 0) && (unsignedValue <= 255));

    const auto offset = static_cast<signed char>(unsignedValue) + 2;         // JR $ is actually $+2.

    // Can a reference by used?
    auto labelWithOffset = tryToGetReferenceAndIncreaseReferenceCounter(currentAddress + offset);
    if (labelWithOffset.isNotEmpty()) {
        return labelWithOffset;
    }

    // Encodes the "$ + x", as there is no label. Don't encode the offset if 0.
    return configuration.getCurrentAddressSymbol() + ((offset != 0) ? encodeSigned8BitsToNumber(offset) : "");
}

juce::String SourceItemEncoder::tryToGetReferenceAndIncreaseReferenceCounter(const int address, const bool forceReferencing) const noexcept
{
    // Can a reference be used?
    const auto reference = references.getReference(address, forceReferencing);
    if (!reference.isReferencePresent()) {
        return { };
    }

    // A reference can be used.
    const auto& label = reference.label;

    // Marks the label as "referred to".
    references.markLabelAsReferredTo(label);

    const auto offset = reference.offset;
    // If the offset is 0, no need to encode it, the label is enough.
    if (offset == 0) {
        return label;
    }
    // Encodes the label and the index, in decimal.
    // Note that the +/- are INVERTED, because the offset is calculated from the other direction.
    return label + WriterUtils::getStringForDecimalNumber(configuration, -offset, true);
}

void SourceItemEncoder::manageComments(const int address, juce::String& result) const noexcept
{
    // Nothing to add in the comments? Then exits.
    if (!configuration.isGenerateAddressesInComments()) {
        return;
    }

    result += "     " + configuration.getCommentSymbol() + WriterUtils::getHexStringFromNumber(configuration, address);
}

void SourceItemEncoder::executeAfterVisit() const noexcept
{
    // Once everything is written, maybe there are referenced labels that are NOT written.
    // This happens with code like this:
    //      jp init
    //      ld hl,#4000
    //init  equ #c000
    //      ret
    // The Init label is never written. So we add them at the end of the source.
    // For now, we force such declaration as "number only". We could improve (?) and use a reference also. However, make sure the reference
    // does not refer ITSELF! Such as "init equ init".
    const auto labelsToWrite = references.getUndeclaredReferencedLabels();

    for (const auto& label : labelsToWrite) {
        auto labelDeclaration = WriterUtils::getLabelForDeclaration(configuration, label.getLabel(), false, configuration.isNoPostFixAfterLabelWithEqu());
        auto result = WriterUtils::getLabelDeclarationWithoutValue(configuration, labelDeclaration) + encode16BitsNumber(label.getAddress(), ReferencingType::forceNonReference);
        WriterUtils::writeString(outputStream, result);
    }
}

}    // namespace disark
