#include "FurnaceInstrumentReader.h"

#include "../../business/song/tool/builder/SongBuilder.h"
#include "../../song/instrument/psg/PsgPartConstants.h"
#include "../../utils/NumberUtil.h"
#include "../../utils/StreamUtil.h"

namespace arkostracker
{
const std::map<std::pair<int, int>, int> FurnaceInstrumentReader::numDenToRatio = { // NOLINT(cert-err58-cpp, *-statically-constructed-objects)
    { { 0, 8 }, 1 },
    { { 0, 4 }, 2 },
    { { 0, 2 }, 3 },
    { { 8, 8 }, 4 },
    { { 8, 8 }, 5 },
};


bool FurnaceInstrumentReader::readInstrument(SongBuilder& songBuilder, juce::InputStream& inputStream, const int blockSize, const int currentInstrumentIndex) noexcept
{
    const auto blockEndPosition = inputStream.getPosition() + blockSize;

    inputStream.skipNextBytes(2);   // Format version.
    const auto instrumentType = inputStream.readShort();

    songBuilder.startInstrument(currentInstrumentIndex, InstrumentType::psgInstrument);
    const auto isPsgInstrument = (instrumentType == 6);     // AY-3-8910.

    juce::String instrumentName;
    auto success = true;

    // Reads all the "features".
    auto featureCode = juce::String();
    while (success && (inputStream.getPosition() != blockEndPosition)) {
        featureCode = StreamUtil::extractString(inputStream, 2, success);
        if (featureCode == "EN") {
            break;
        }
        const auto featureSize = inputStream.readShort();

        const auto inputStreamCurrentPosition = inputStream.getPosition();

        DBG("   feature = " + featureCode);

        if (featureCode == "NA") {
            instrumentName = inputStream.readString();
        } else if (isPsgInstrument && (featureCode == "MA")) {      // Skips all data if not PSG Instrument.
            readInstrumentMacro(songBuilder, inputStream);
        }

        // As a security, always use the size to go to the next feature.
        inputStream.setPosition(inputStreamCurrentPosition + featureSize);
    }

    if (instrumentName.isEmpty()) {
        instrumentName = "Instrument " + juce::String(currentInstrumentIndex);
    }
    songBuilder.setCurrentInstrumentName(instrumentName);

    // Creates a fake instrument if not PSG, or the instrument might only contain the "NA", nothing else.
    // In this case, create a simple Beep instrument (which is what happens in Furnace with an empty Instrument).
    if (songBuilder.getCurrentInstrumentLength() == 0) {
        songBuilder.startNewPsgInstrumentCell();

        songBuilder.setCurrentPsgInstrumentCell(PsgInstrumentCell::buildSoftwareCell(15));
        songBuilder.finishCurrentPsgInstrumentCell();

        // Don't make the sound loop for non-PSG instrument. May sound too harsh.
        songBuilder.setCurrentPsgInstrumentMainLoop(0, 0, isPsgInstrument);
    }

    songBuilder.finishCurrentInstrument();

    return success;
}

bool FurnaceInstrumentReader::readInstrumentMacro(SongBuilder& songBuilder, juce::InputStream& inputStream) noexcept
{
    inputStream.skipNextBytes(2);       // Length of header.

    std::vector<int> volumes;
    std::vector<int> softwareArpeggios;
    std::vector<int> noises;
    std::vector<int> areToneNoiseEnvelopes;     // Bit 0 = Tone? 1 = Noise? 2 = Hardware envelope?
    std::vector<int> pitches;
    std::vector<int> resets;    // = retrig.
    std::vector<int> envelopes;
    std::vector<int> autoEnvNum;
    std::vector<int> autoEnvDen;
    std::vector<int> forceSoftwarePeriods;
    std::vector<int> forceHardwarePeriods;
    // If adding new tables, add it to the list below.

    auto speed = 0;
    OptionalInt loopStart;      // There is always loop. If none is set, we consider it loops on the last item.

    auto macroCode = static_cast<unsigned char>(inputStream.readByte());
    while (macroCode != 255) {
        // Links the code to an array to fill.
        std::vector<int>* tablePt = nullptr;
        switch (macroCode) {
            case 0:
                tablePt = &volumes;
                break;
            case 1:
                tablePt = &softwareArpeggios;
                break;
            case 2:     // "Duty" in the doc.
                tablePt = &noises;
                break;
            case 3:     // "Wave" in the doc.
                tablePt = &areToneNoiseEnvelopes;
                break;
            case 4:
                tablePt = &pitches;
                break;
            case 14:
                tablePt = &resets;      // "phaseReset" = retrig.
                break;
            case 6:
                tablePt = &envelopes;
                break;
            case 7:
                tablePt = &autoEnvNum;
                break;
            case 8:
                tablePt = &autoEnvDen;
                break;
            case 15:
                tablePt = &forceSoftwarePeriods;
                break;
            case 16:
                tablePt = &forceHardwarePeriods;
                break;
            default:
                tablePt = nullptr;
                break;
        }

        const auto macroLength = static_cast<unsigned char>(inputStream.readByte());
        const auto macroLoop = static_cast<unsigned char>(inputStream.readByte());
        // If present, we consider the loop start is defined by the "volume".
        if ((macroLoop != 255) && (macroCode == 0)) {
            loopStart = macroLoop;
        }

        inputStream.skipNextBytes(1);       // Release. Ignored.
        inputStream.skipNextBytes(1);       // Macro mode. Ignored.

        // Bits 2/1 are "00" for raw values.
        const auto macroOpenTypeWordSize = static_cast<unsigned char>(inputStream.readByte());
        const auto wordSizeBits = (static_cast<unsigned int>(macroOpenTypeWordSize) >> 6U) & 0b11U;
        const auto macroMode = (static_cast<unsigned int>(macroOpenTypeWordSize) >> 1U) & 0b11U;
        auto wordSize = 1;
        auto isDataSigned = true;
        switch (wordSizeBits) {
            case 0:                 // 8 bits unsigned.
                isDataSigned = false;
                [[fallthrough]];
            case 1:                 // 8 bits signed.
                wordSize = 1;
                break;
            case 2:
                wordSize = 2;       // 16 bits signed.
                break;
            case 3:
                wordSize = 4;       // 32 bits signed.
                break;
            default:
                jassertfalse;       // Huh?
                break;
        }

        inputStream.skipNextBytes(1);           // Delay. Ignored.
        const auto macroSpeed = static_cast<unsigned char>(inputStream.readByte()); // >= 1.
        speed = std::max(speed, static_cast<int>(macroSpeed) - 1);          // We consider the speed is the largest found among each macro.
        speed = NumberUtil::correctNumber(speed, PsgPartConstants::minimumSpeed, PsgPartConstants::maximumSpeed);

        juce::MemoryBlock macroData;
        inputStream.readIntoMemoryBlock(macroData, static_cast<juce::int64>(macroLength) * wordSize);

        // Reads the raw data into the related table, if we know what to do with this!
        if (tablePt != nullptr) {
            for (auto i = 0U; i < macroData.getSize();) {
                auto val = 0;
                if ((wordSize == 1) && isDataSigned) {
                    val = static_cast<signed char>(macroData[i++]); // NOLINT(*-signed-char-misuse, *-str34-c)
                } else if ((wordSize == 1) && !isDataSigned) {
                    val = static_cast<unsigned char>(macroData[i++]);
                } else if (wordSize == 2) {
                    jassert(isDataSigned);
                    val = static_cast<juce::int16>(static_cast<unsigned char>(macroData[i]) + (static_cast<unsigned char>(macroData[i + 1]) * 256));
                    i += 2;
                } else if (wordSize == 4) {
                    i += 4;             // Data type not managed, simply skip it.
                } else {
                    jassertfalse;       // Abnormal. Undocumented?
                    i += 4;
                }

                tablePt->push_back(val);
            }

            // If not Sequence (0) (=ADSR (1) / LFO (2)), dismisses the whole stuff. Default values below will be used instead.
            if (macroMode != 0) {
                tablePt->clear();
            }
        }

        macroCode = static_cast<unsigned char>(inputStream.readByte());
    }

    // Makes sure there is at least one entry in each table, for default value.
    size_t instrumentLength = 0;
    for (auto* table : { &softwareArpeggios, &noises, &pitches, &envelopes, &resets, &autoEnvNum, &autoEnvDen, &forceSoftwarePeriods, &forceHardwarePeriods }) {
        if (table->empty()) {
            table->emplace_back(0);
        }
        instrumentLength = std::max(instrumentLength, table->size());
    }
    if (volumes.empty()) {
        volumes.emplace_back(15);      // If nothing, volume is 15.
    }
    instrumentLength = std::max(instrumentLength, volumes.size());

    if (areToneNoiseEnvelopes.empty()) {
        areToneNoiseEnvelopes.emplace_back(1);      // If nothing, tone is present by default.
    }
    instrumentLength = std::max(instrumentLength, areToneNoiseEnvelopes.size());

    // Writes the arrays into the current instrument.
    for (auto i = 0U; i < instrumentLength; ++i) {
        songBuilder.startNewPsgInstrumentCell();

        const auto volume = getValue(i, volumes);
        songBuilder.setCurrentPsgInstrumentCellVolume(volume);
        songBuilder.setCurrentPsgInstrumentCellPrimaryArpeggio(getValue(i, softwareArpeggios));

        const auto forcedHardwarePeriod = getValue(i, forceHardwarePeriods);
        const auto isForcedHardwarePeriod = (forcedHardwarePeriod > 0);

        const auto isToneNoiseEnvelope = static_cast<unsigned int>(areToneNoiseEnvelopes.at(std::min(static_cast<size_t>(i), areToneNoiseEnvelopes.size() - 1)));

        const auto isHardwareEnvelope = ((isToneNoiseEnvelope & 100U) != 0);
        const auto isNoise = ((isToneNoiseEnvelope & 10U) != 0);
        const auto isTone = ((isToneNoiseEnvelope & 1U) != 0);

        auto link = PsgInstrumentCellLink::softOnly;
        if (!isTone && !isHardwareEnvelope) {
            link = PsgInstrumentCellLink::noSoftNoHard;
        } else if (!isTone && isHardwareEnvelope) {
            link = PsgInstrumentCellLink::hardOnly;
        } else if (isTone && isHardwareEnvelope && !isForcedHardwarePeriod) {
            link = PsgInstrumentCellLink::softToHard;
        }  else if (isTone && isHardwareEnvelope && isForcedHardwarePeriod) {
            link = PsgInstrumentCellLink::softAndHard;
        }
        songBuilder.setCurrentPsgInstrumentCellLink(link);

        // If forced hardware period, we switch to either HardOnly or SoftAndHard.
        if (isForcedHardwarePeriod) {
            if (link == PsgInstrumentCellLink::hardOnly) {
                songBuilder.setCurrentPsgInstrumentCellPrimaryPeriod(forcedHardwarePeriod);
            } else {
                jassert(link == PsgInstrumentCellLink::softAndHard);
                songBuilder.setCurrentPsgInstrumentCellSecondaryPeriod(forcedHardwarePeriod);
            }
        }

        // Forced software period? Bypassed if hard to soft.
        const auto forcedSoftwarePeriod = getValue(i, forceSoftwarePeriods);
        if ((forcedSoftwarePeriod > 0) && (link != PsgInstrumentCellLink::hardOnly)) {
            songBuilder.setCurrentPsgInstrumentCellPrimaryPeriod(forcedSoftwarePeriod);
        }

        if (isNoise) {
            const auto rawNoise = getValue(i, noises);
            if (rawNoise != 0) {        // 0 is possible when there is Noise flag declared, but the value is dismissed (because ADSR/LFO).
                const auto noise = NumberUtil::correctNumber(31 - rawNoise, 1, PsgValues::maximumNoise);    // Furnace is inverted.
                songBuilder.setCurrentPsgInstrumentCellNoise(noise);
            }
        }

        if (isHardwareEnvelope) {
            const auto rawEnvelopeCurve = getValue(i, envelopes);
            songBuilder.setCurrentPsgInstrumentCellHardwareEnvelope(PsgValues::convertEnvelopeCurveToAt(rawEnvelopeCurve));
            songBuilder.setCurrentPsgInstrumentCellVolume(0);      // Just to please the equality test.

            // Tries to determine the ratio. I don't understand how this work in Furnace, so sorry for the brutal approximation.
            auto ratio = 4;
            const auto num = getValue(i, autoEnvNum);
            const auto den = getValue(i, autoEnvDen);
            if (auto it = numDenToRatio.find({ num, den }); it != numDenToRatio.cend()) {
                ratio = it->second;
            }
            songBuilder.setCurrentPsgInstrumentCellRatio(ratio);

            // Retrig?
            const auto rawReset = getValue(i, resets);
            if (rawReset > 0) {
                songBuilder.setCurrentPsgInstrumentCellRetrig(true);
            }
        }

        const auto pitch = getValue(i, pitches);
        songBuilder.setCurrentPsgInstrumentCellPrimaryPitch(pitch);

        songBuilder.finishCurrentPsgInstrumentCell();
    }

    songBuilder.setCurrentPsgInstrumentSpeed(speed);
    // If no loop is set, considers the last item is the loop start.
    if (loopStart.isAbsent()) {
        loopStart = static_cast<int>(instrumentLength) - 1;
    }
    songBuilder.setCurrentPsgInstrumentMainLoop(loopStart.getValue(), static_cast<int>(instrumentLength) - 1, true);  // Sounds always loop!

    return true;
}

}   // namespace arkostracker
