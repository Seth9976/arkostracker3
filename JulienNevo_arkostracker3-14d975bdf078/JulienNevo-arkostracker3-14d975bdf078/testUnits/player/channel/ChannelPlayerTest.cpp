#include "../../catch.hpp"

#include "../../../source/player/PsgPeriod.h"
#include "../../../source/player/SongDataProvider.h"
#include "../../../source/player/channel/ChannelPlayer.h"
#include "../../../source/song/psg/PsgFrequency.h"
#include "../../../source/utils/PsgValues.h"

namespace arkostracker 
{

/** A Data provider that returns no sound. */
class BaseDataProvider : public SongDataProvider
{
public:
    BaseDataProvider() :
            instrument1Id(),
            arpeggio1Id()
    {
    }

    Id instrument1Id;
    Id arpeggio1Id;

    InstrumentType getInstrumentTypeFromAudioThread(const OptionalId& /*instrumentId*/) const noexcept override
    {
        return InstrumentType::psgInstrument;
    }

    OptionalId getInstrumentIdFromAudioThread(const int instrumentIndex) const noexcept override
    {
        if (instrumentIndex == 1) {
            return instrument1Id;
        }
        return {};
    }

    SongDataProvider::ExpressionMetadata getExpressionMetadataFromAudioThread(bool /*isArpeggio*/, const OptionalId& /*expressionId*/) const noexcept override
    {
        return { 0, 0, 0 };
    }

    SongDataProvider::PsgInstrumentFrameData getPsgInstrumentFrameDataFromAudioThread(const OptionalId& /*instrumentId*/, int /*cellIndex*/) const noexcept override
    {
        return { Loop(), 0, false, LowLevelPsgInstrumentCell() };
    }

    SampleInstrumentFrameData getSampleInstrumentFrameDataFromAudioThread(const OptionalId& /*instrumentId*/) const noexcept override
    {
        return { Loop(), 11025, 1.0F, nullptr };
    }

    int getExpressionValueFromAudioThread(bool /*isArpeggio*/, const OptionalId& /*expressionId*/, int /*cellIndex*/) const noexcept override
    {
        return 0;
    }

    std::pair<int, float> getPsgFrequencyFromChannelFromAudioThread(int /*channelIndexInSong*/) const noexcept override
    {
        return { PsgFrequency::psgFrequencyCPC, PsgFrequency::defaultReferenceFrequencyHz };
    }

    int getTranspositionFromAudioThread(int /*channelIndexInSong*/) const noexcept override
    {
        return 0;
    }

    OptionalId getExpressionIdFromAudioThread(bool /*isArpeggio*/, const int pExpressionIndex) const noexcept override
    {
        if (pExpressionIndex == 1) {
            return arpeggio1Id;
        }
        return {};
    }

    bool isEffectContextEnabled() const noexcept override
    {
        return false;
    }

    LineContext determineEffectContextFromAudioThread(CellLocationInPosition /*location*/) const noexcept override
    {
        return { };
    }

    LineContext determineEffectContextFromAudioThread(int /*channelIndexInSong*/) const noexcept override
    {
        return { };
    }

    SidPlayerCapability getSidPlayerCapability() const noexcept override
    {
        return SidPlayerCapability::buildForCpc();
    }
};


class DataProviderDecayingSoftOnlySound : public BaseDataProvider
{
public:
    explicit DataProviderDecayingSoftOnlySound(const int pSpeed = 0, const int pArpeggioValueOn0 = 0, const Loop pLoop = Loop(0, 14, false) ) :
            speed(pSpeed),
            arpeggioValueOn0(pArpeggioValueOn0),
            loop(pLoop)
    {
    }

    PsgInstrumentFrameData getPsgInstrumentFrameDataFromAudioThread(const OptionalId& instrumentId, const int cellIndex) const noexcept override
    {
        // Only instrument 1 does something.
        if (instrumentId != instrument1Id) {
            return BaseDataProvider::getPsgInstrumentFrameDataFromAudioThread(instrumentId, cellIndex);
        }

        // Within sound boundaries?
        LowLevelPsgInstrumentCell cell;
        if ((cellIndex >= 0) && (cellIndex <= 15)) {
            const auto arpeggio = (cellIndex == 0) ? arpeggioValueOn0 : 0;
            cell = LowLevelPsgInstrumentCell(PsgInstrumentCellLink::softOnly, 15 - cellIndex, 0, 0,
                                             arpeggio, 0, 4, 8, 0, 0, 0, false,
                                             PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
                                             PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        }

        return { loop, speed, false, cell };
    }

    int getExpressionValueFromAudioThread(const bool isArpeggio, const OptionalId& expressionId, const int cellIndex) const noexcept override
    {
        if (isArpeggio && (expressionId == arpeggio1Id)) {
            switch (cellIndex % 3) {
                case 0:
                    return 0;
                case 1:
                    return 3;
                case 2:
                    return 7;
                default:
                    return 0;
            }
        }

        return 0;
    }

    ExpressionMetadata getExpressionMetadataFromAudioThread(const bool isArpeggio, const OptionalId& expressionId) const noexcept override
    {
        if (isArpeggio && (expressionId == arpeggio1Id)) {
            return { 0, 0, 2 };
        }

        return { 0, 0, 0 };
    }

    const int speed;
    const int arpeggioValueOn0;
    const Loop loop;
};

class DataProviderFullVolume final : public DataProviderDecayingSoftOnlySound
{
public:
    DataProviderFullVolume() :
            DataProviderDecayingSoftOnlySound(0, 0, Loop(0, 0, true))
    {
    }

    PsgInstrumentFrameData getPsgInstrumentFrameDataFromAudioThread(const OptionalId& /*instrumentId*/, int /*cellIndex*/) const noexcept override
    {
        const auto cell = LowLevelPsgInstrumentCell(PsgInstrumentCellLink::softOnly, 15, 0, 0,
                                  0, 0, 4, 8, 0, 0, 0, false,
                                  PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
                                  PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        return { Loop(0, 0, true), 0, false, cell };
    }
};

/** One looping cell of hardware sound. */
class DataProviderHardwareSound : public BaseDataProvider
{
public:
    explicit DataProviderHardwareSound(const PsgInstrumentCellLink pLink = PsgInstrumentCellLink::softToHard, const int pRatio = 4, const int pHardwareEnvelope = 8, const bool pIsInstrumentRetrig = false) :
            link(pLink),
            ratio(pRatio),
            hardwareEnvelope(pHardwareEnvelope),
            isInstrumentRetrig(pIsInstrumentRetrig)
    {
    }

    PsgInstrumentFrameData getPsgInstrumentFrameDataFromAudioThread(const OptionalId& instrumentId, const int cellIndex) const noexcept override
    {
        // Only instrument 1 does something.
        if (instrumentId != instrument1Id) {
            return BaseDataProvider::getPsgInstrumentFrameDataFromAudioThread(instrumentId, cellIndex);
        }

        Loop const loop(0, 0, true);

        // Within sound boundaries?
        LowLevelPsgInstrumentCell cell;
        if ((cellIndex >= 0) && (cellIndex <= 0)) {
            cell = LowLevelPsgInstrumentCell(link, 0, 0, 0,
                                             0, 0, ratio, hardwareEnvelope,
                                             0, 0, 0, false,
                                             PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
                                             PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        }

        return { loop, 0, isInstrumentRetrig, cell };
    }

    const PsgInstrumentCellLink link;
    const int ratio;
    const int hardwareEnvelope;
    const bool isInstrumentRetrig;
};

/** Instrument 2 is a sample. */
class DataProviderSample final : public DataProviderHardwareSound
{
public:
    DataProviderSample() :
        DataProviderHardwareSound()
    {
    }

    SampleInstrumentFrameData getSampleInstrumentFrameDataFromAudioThread(const OptionalId& instrumentId) const noexcept override
    {
        // Only instrument 2 does something.
        if (instrumentId != instrument2Id) {
            return BaseDataProvider::getSampleInstrumentFrameDataFromAudioThread(instrumentId);
        }
        constexpr auto sampleSize = 10;

        const juce::MemoryBlock sampleData(sampleSize, true);
        auto sample = std::make_shared<Sample>(sampleData);
        return { Loop(0, sampleSize - 1, false), 11025, 1.0F, sample };
    }

    const Id instrument2Id;
};


/** One looping cell of hardware only, with one arpeggio. */
class DataProviderHardwareOnlyWithOneArp final : public BaseDataProvider
{
public:
    PsgInstrumentFrameData getPsgInstrumentFrameDataFromAudioThread(const OptionalId& instrumentId, const int cellIndex) const noexcept override
    {
        // Only instrument 1 does something.
        if (instrumentId != instrument1Id) {
            return BaseDataProvider::getPsgInstrumentFrameDataFromAudioThread(instrumentId, cellIndex);
        }

        const Loop loop(0, 0, true);

        const LowLevelPsgInstrumentCell cell(PsgInstrumentCellLink::hardOnly, 0, 0, 0,
                                       0, 0, 4, 8,
                                       0, 12 * 4, 0, false,
                                       PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
                                       PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        return { loop, 0, false, cell };
    }
};

// ======================================================================




TEST_CASE("Channel player, nothing", "[ChannelPlayer]")
{
    BaseDataProvider songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, 0);

    // Play lines.
    for (auto cellIndex = 0; cellIndex < 30; ++cellIndex) {
        const auto result = channelPlayer.playStream((cellIndex == 0), (cellIndex < 6));
        REQUIRE_FALSE(result->isNewNotePlayed());
        REQUIRE_FALSE(result->isEffectDeclared());
        REQUIRE(result->getChannelOutputRegisters().isSilent());
    }
}

TEST_CASE("Channel player, decaying software sound", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderDecayingSoftOnlySound songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(4 * 12), 1), channelIndex, {}));
    // Play the lines.
    std::vector expectedVolumes = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0 };   // More than the sound to check the non-loop.
    auto cellIndex = 0;
    while (cellIndex < static_cast<int>(expectedVolumes.size())) {
        auto result = channelPlayer.playStream((cellIndex == 0), (cellIndex < 6));
        REQUIRE(((result->isNewNotePlayed() && (cellIndex == 0)) || (cellIndex > 0)));      // Only first line has a new note played.
        REQUIRE_FALSE(result->isEffectDeclared());
        const auto registers = result->getChannelOutputRegisters();
        const auto expectedVolume = expectedVolumes.at(static_cast<size_t>(cellIndex));
        REQUIRE((registers.getVolume() == expectedVolume));
        REQUIRE((registers.getSoundType() == ((expectedVolume > 0) ? SoundType::softwareOnly : SoundType::noSoftwareNoHardware)));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == 239));
        REQUIRE_FALSE(registers.isRetrig());
        ++cellIndex;
    }
}

TEST_CASE("Channel player, decaying software sound, speed in instrument", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderDecayingSoftOnlySound songDataProvider(2);
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    constexpr auto note = (3 * 12) + 5;
    const auto expectedPeriod = PsgPeriod::getPeriod(PsgFrequency::psgFrequencyCPC, PsgFrequency::defaultReferenceFrequencyHz, note);
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(note), 1), channelIndex, { }));
    // Play the lines. More than the sound to check the non-loop.
    std::vector expectedVolumes = { 15, 15, 15, 14, 14, 14, 13, 13, 13, 12, 12, 12, 11, 11, 11, 10, 10, 10,
                                         9, 9, 9, 8, 8, 8, 7, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
    auto cellIndex = 0;
    while (cellIndex < static_cast<int>(expectedVolumes.size())) {
        auto result = channelPlayer.playStream((cellIndex == 0), (cellIndex < 6));
        REQUIRE(((result->isNewNotePlayed() && (cellIndex == 0)) || (cellIndex > 0)));      // Only first line has a new note played.
        REQUIRE_FALSE(result->isEffectDeclared());
        const auto registers = result->getChannelOutputRegisters();
        const auto expectedVolume = expectedVolumes.at(static_cast<size_t>(cellIndex));
        REQUIRE((registers.getVolume() == expectedVolume));
        REQUIRE((registers.getSoundType() == ((expectedVolume > 0) ? SoundType::softwareOnly : SoundType::noSoftwareNoHardware)));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == expectedPeriod));
        REQUIRE_FALSE(registers.isRetrig());
        ++cellIndex;
    }
}

TEST_CASE("Channel player, softToHard sound, ratio 4", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderHardwareSound songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(4 * 12), 1), channelIndex, { }));
    // Play the lines.
    for (auto cellIndex = 0; cellIndex < 30; ++cellIndex) {
        auto result = channelPlayer.playStream((cellIndex == 0), (cellIndex < 6));
        REQUIRE(((result->isNewNotePlayed() && (cellIndex == 0)) || (cellIndex > 0)));      // Only first line has a new note played.
        REQUIRE_FALSE(result->isEffectDeclared());
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 16));
        REQUIRE((registers.getSoundType() == SoundType::softwareAndHardware));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getHardwareEnvelope() == 8));
        REQUIRE((registers.getSoftwarePeriod() == 239));
        REQUIRE((registers.getHardwarePeriod() == 15));
        REQUIRE_FALSE(registers.isRetrig());
    }
}

TEST_CASE("Channel player, softToHard sound, envelope 10, ratio 5, instrument retrig", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderHardwareSound songDataProvider(PsgInstrumentCellLink::softToHard, 5, 10, true);
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(4 * 12), 1), channelIndex, { }));
    // Play the lines.
    for (auto cellIndex = 0; cellIndex < 30; ++cellIndex) {
        auto result = channelPlayer.playStream((cellIndex == 0), (cellIndex < 6));
        REQUIRE(((result->isNewNotePlayed() && (cellIndex == 0)) || (cellIndex > 0)));      // Only first line has a new note played.
        REQUIRE_FALSE(result->isEffectDeclared());
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 16));
        REQUIRE((registers.getSoundType() == SoundType::softwareAndHardware));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getHardwareEnvelope() == 10));
        REQUIRE((registers.getSoftwarePeriod() == 239));
        REQUIRE((registers.getHardwarePeriod() == 7));
        REQUIRE((registers.isRetrig() == (cellIndex == 0)));      // Retrig only on first line.
    }
}

TEST_CASE("Channel player, software sound with arpeggio, with arpeggio effect", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderDecayingSoftOnlySound songDataProvider(0, 12, Loop(1, 5, true));
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    const CellEffects cellEffects({ { Effect::arpeggioTable, 1 }});
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(3 * 12), 1, cellEffects), channelIndex, { }));

    std::vector expectedVolumes = {
            15, 14, 13, 12, 11, 10,
            14, 13, 12, 11, 10,
            14, 13, 12, 11, 10,
            14, 13, 12, 11, 10
    };
    std::vector expectedSoftwarePeriod = {
            239, 402, 319, 478, 402, 319,
            478, 402, 319, 478, 402,
            319, 478, 402, 319, 478,
            402, 319, 478, 402, 319
    };
    REQUIRE((expectedVolumes.size() == expectedSoftwarePeriod.size()));

    // Play the lines.
    for (auto cellIndex = 0; cellIndex < static_cast<int>(expectedVolumes.size()); ++cellIndex) {
        auto result = channelPlayer.playStream((cellIndex == 0), (cellIndex < 6));
        REQUIRE(((result->isNewNotePlayed() && (cellIndex == 0)) || (cellIndex > 0)));      // Only first line has a new note played.
        REQUIRE(((result->isEffectDeclared() && (cellIndex == 0)) || (cellIndex > 0)));     // Effect declared on the first line.
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == expectedVolumes.at(static_cast<size_t>(cellIndex))));
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod.at(static_cast<size_t>(cellIndex))));
        REQUIRE_FALSE(registers.isRetrig());
    }
}

/**
 * Calculates a hardware period, using the Z80 algorithm (remainder of the last iteration only matters).
 * @param inputPeriod the input period.
 * @param ratio the ratio (>=0, <=7).
 * @return the new period.
 */
static int calculateHardPeriod(const int inputPeriod, int ratio)
{
    auto period = static_cast<float>(inputPeriod);

    auto remaining = false;
    while (ratio > 0) {
        period = period / 2.0F;
        remaining = !juce::exactlyEqual(std::floor(period), period);

        period = std::floor(period);

        --ratio;
    }

    if (remaining) {
        ++period;
    }

    return static_cast<int>(period);
}

static int getPeriod(const int note)
{
    return PsgPeriod::getPeriod(PsgFrequency::psgFrequencyCPC, PsgFrequency::defaultReferenceFrequencyHz, note);
}

TEST_CASE("Channel player, softToHard, pitch up", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    constexpr auto ratio = 4;
    constexpr auto hardwareEnvelope = 10;
    DataProviderHardwareSound songDataProvider(PsgInstrumentCellLink::softToHard, ratio, hardwareEnvelope);
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    constexpr auto note = 4 * 12;
    const CellEffects cellEffects({{ Effect::pitchUp, 0x100 }});
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(note), 1, cellEffects), channelIndex, { }));

    const auto baseSoftPeriod = getPeriod(note);
    std::vector expectedSoftwarePeriods = {
            baseSoftPeriod - 1, baseSoftPeriod - 2, baseSoftPeriod - 3, baseSoftPeriod - 4, baseSoftPeriod - 5,
            baseSoftPeriod - 6, baseSoftPeriod - 7, baseSoftPeriod - 8, baseSoftPeriod - 9, baseSoftPeriod - 10
    };

    // Play the lines.
    for (auto cellIndex = 0; cellIndex < static_cast<int>(expectedSoftwarePeriods.size()); ++cellIndex) {
        auto result = channelPlayer.playStream((cellIndex == 0), true);    // To be sure the pitch continues endlessly.
        REQUIRE(((result->isNewNotePlayed() && (cellIndex == 0)) || (cellIndex > 0)));      // Only first line has a new note played.
        REQUIRE(((result->isEffectDeclared() && (cellIndex == 0)) || (cellIndex > 0)));      // Effect declared on first line.
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 16));
        REQUIRE((registers.getSoundType() == SoundType::softwareAndHardware));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getHardwareEnvelope() == hardwareEnvelope));
        const auto expectedSoftwarePeriod = expectedSoftwarePeriods.at(static_cast<size_t>(cellIndex));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod));
        REQUIRE((registers.getHardwarePeriod() == calculateHardPeriod(expectedSoftwarePeriod, ratio)));
        REQUIRE_FALSE(registers.isRetrig());
    }
}

TEST_CASE("Channel player, hardware sound, pitch down", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    constexpr auto ratio = 2;
    constexpr auto hardwareEnvelope = 12;
    DataProviderHardwareSound songDataProvider(PsgInstrumentCellLink::softToHard, ratio, hardwareEnvelope);
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    constexpr auto note = 4 * 12;

    const CellEffects cellEffects({{ Effect::pitchDown, 0x80 }});
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(note), 1, cellEffects), channelIndex, { }));

    const auto basePeriod = getPeriod(note);
    std::vector expectedSoftwarePeriods = {
            basePeriod + 0, basePeriod + 1,
            basePeriod + 1, basePeriod + 2, basePeriod + 2, basePeriod + 3,
            basePeriod + 3, basePeriod + 4, basePeriod + 4, basePeriod + 5,
            basePeriod + 5
    };

    // Play the lines.
    for (auto iterationIndex = 0; iterationIndex < static_cast<int>(expectedSoftwarePeriods.size()); ++iterationIndex) {
        auto result = channelPlayer.playStream((iterationIndex == 0), true);         // To force the effect to continue.
        REQUIRE(((result->isNewNotePlayed() && (iterationIndex == 0)) || (iterationIndex > 0)));      // Only first line has a new note played.
        REQUIRE(((result->isEffectDeclared() && (iterationIndex == 0)) || (iterationIndex > 0)));      // Effect declared on first line.
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 16));
        REQUIRE((registers.getSoundType() == SoundType::softwareAndHardware));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getHardwareEnvelope() == hardwareEnvelope));
        const auto expectedSoftwarePeriod = expectedSoftwarePeriods.at(static_cast<size_t>(iterationIndex));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod));
        REQUIRE((registers.getHardwarePeriod() == calculateHardPeriod(expectedSoftwarePeriod, ratio)));
        REQUIRE_FALSE(registers.isRetrig());
    }
}

TEST_CASE("Channel player, glide up, software sound", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderFullVolume songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((1 * 12) + 9), 1), channelIndex, { }));       // A-1

    // Play the lines.
    std::vector expectedSoftwarePeriod = {
            1136, 1136, 1136, 1136, 1136, 1136,

            1120, 1104, 1088, 1072, 1056, 1040,
            1024, 1008, 992, 976, 960, 944,
            928, 912, 896, 880, 864,

            851,
            851, 851, 851, 851, 851, 851
    };
    const auto iterationCount = expectedSoftwarePeriod.size();

    auto tick = 0;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        constexpr auto speed = 6;
        // Plays a glide if at the second line.
        if (iterationIndex == speed) {
            const CellEffects cellEffects({ { Effect::pitchGlide, 0xfff } });
            channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((2 * 12) + 2), { }, cellEffects), channelIndex, { }));       // D-2 GFFF
        }

        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        REQUIRE(((((result->isNewNotePlayed() && ((iterationIndex == 0)) || (iterationIndex == 6)))) || !result->isNewNotePlayed()));      // Only the first 2 lines have a new note played.
        REQUIRE(((result->isEffectDeclared() && (iterationIndex == speed)) || !result->isEffectDeclared()));            // Glide effect only on second line.
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 15));
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod.at(iterationIndex)));
        REQUIRE_FALSE(registers.isRetrig());

        tick = (tick + 1) % speed;
    }
}

TEST_CASE("Channel player, glide down, software sound", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderFullVolume songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((2 * 12) + 9), 1), channelIndex, { }));       // A-2

    // Play the lines.
    std::vector expectedSoftwarePeriod = {
            568, 568, 568, 568, 568, 568,

            583, 599, 615, 631, 647, 663,
            679, 695, 711, 727, 743, 759,
            775, 791, 807, 823, 839,

            851,
            851, 851, 851, 851, 851, 851
    };
    const auto iterationCount = expectedSoftwarePeriod.size();

    auto tick = 0;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        constexpr auto speed = 6;
        // Plays a glide if at the second line.
        if (iterationIndex == speed) {
            const CellEffects cellEffects({ { Effect::pitchGlide, 0xfff } });
            channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((2 * 12) + 2), { }, cellEffects), channelIndex, { }));       // D-2 GFFF
        }

        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        REQUIRE(((((result->isNewNotePlayed() && ((iterationIndex == 0)) || (iterationIndex == 6)))) || !result->isNewNotePlayed()));      // Only the first 2 lines have a new note played.
        REQUIRE(((result->isEffectDeclared() && (iterationIndex == speed)) || !result->isEffectDeclared()));            // Glide effect only on second line.
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 15));
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod.at(iterationIndex)));
        REQUIRE_FALSE(registers.isRetrig());

        tick = (tick + 1) % speed;
    }
}

TEST_CASE("Channel player, pitch up, software sound", "[ChannelPlayer]")
{
    DataProviderFullVolume songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, 0);

    // A-3
    //      u380
    //      ----
    //      ----
    //      u000

    // Play the lines.
    std::vector expectedSoftwarePeriod = {
            284, 284, 284, 284, 284, 284,

            280, 277, 273, 270, 266, 263,
            259, 256, 252, 249, 245, 242,
            238, 235, 231, 228, 224, 221,

            221, 221, 221, 221, 221, 221,
    };
    const auto iterationCount = expectedSoftwarePeriod.size();

    auto tick = 0;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        constexpr auto speed = 6;
        // Posts cells.
        if (tick == 0) {
            constexpr auto channelIndex = 0;
            const auto cellIndex = iterationIndex / speed;
            switch (cellIndex) {
                case 0:
                {
                    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((3 * 12) + 9), 1), channelIndex, { }));       // A-3
                    break;
                }
                case 1:
                {
                    const CellEffects cellEffects({ { Effect::pitchUp, 0x380} });
                    channelPlayer.postCell(CellToPlay(Cell(OptionalValue<Note>(), OptionalInt(), cellEffects), channelIndex, { }));       // u380
                    break;
                }
                case 4:
                {
                    const CellEffects cellEffects({ { Effect::pitchUp, 0x000} });
                    channelPlayer.postCell(CellToPlay(Cell(OptionalValue<Note>(), OptionalInt(), cellEffects), channelIndex, { }));       // u000
                    break;
                }
                default:
                    break;
            }
        }

        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 15));
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod.at(iterationIndex)));
        REQUIRE_FALSE(registers.isRetrig());

        tick = (tick + 1) % speed;
    }
}

TEST_CASE("Channel player, pitch down, software sound", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderFullVolume songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // A-3
    //      d380
    //      ----
    //      ----
    //      d000

    // Play the lines.
    std::vector expectedSoftwarePeriod = {
            284, 284, 284, 284, 284, 284,

            287, 291, 294, 298, 301, 305,
            308, 312, 315, 319, 322, 326,
            329, 333, 336, 340, 343, 347,

            347, 347, 347, 347, 347, 347,
            347, 347, 347, 347, 347, 347,
    };
    const auto iterationCount = expectedSoftwarePeriod.size();

    auto tick = 0;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        constexpr auto speed = 6;
        // Posts cells.
        if (tick == 0) {
            const auto cellIndex = iterationIndex / speed;
            switch (cellIndex) {
                case 0:
                {
                    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((3 * 12) + 9), 1), channelIndex, { }));       // A-3
                    break;
                }
                case 1:
                {
                    const CellEffects cellEffects({ { Effect::pitchDown, 0x380} });
                    channelPlayer.postCell(CellToPlay(Cell(OptionalValue<Note>(), OptionalInt(), cellEffects), channelIndex, { }));       // d380
                    break;
                }
                case 4:
                {
                    const CellEffects cellEffects({ { Effect::pitchDown, 0x000} });
                    channelPlayer.postCell(CellToPlay(Cell(OptionalValue<Note>(), OptionalInt(), cellEffects), channelIndex, { }));       // d000
                    break;
                }
                default:
                    break;
            }
        }

        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 15));
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod.at(iterationIndex)));
        REQUIRE_FALSE(registers.isRetrig());

        tick = (tick + 1) % speed;
    }
}

TEST_CASE("Channel player, high-pitched hard only with arp within sound, overflow", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderHardwareOnlyWithOneArp songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // Posts the cell.
    constexpr auto note = (6 * 12) + 7;       // G-6. With the arp, is limited the maximum note.

    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(note), 1), channelIndex, { }));

    // Play the lines.
    for (auto iterationIndex = 0; iterationIndex < 20; ++iterationIndex) {
        auto result = channelPlayer.playStream((iterationIndex == 0), false);
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 16));
        REQUIRE((registers.getSoundType() == SoundType::hardwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getHardwarePeriod() == 2));
        REQUIRE((registers.getHardwareEnvelope() == 8));
        REQUIRE_FALSE(registers.isRetrig());
    }
}

TEST_CASE("Channel player, glide up then down, software sound", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderFullVolume songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    // D-5
    // E-5  g200        // Up.
    // C-5  g200        // Down.

    // Play the lines.
    std::vector expectedSoftwarePeriod = {
            100, 100, 100, 100, 100, 100, 100, 100, 100, 100,

            98, 96, 94, 92, 90, 89, 89, 89, 89, 89,

            91, 93, 95, 97, 99, 101, 103, 105, 107, 109,
            111, 113, 113, 113, 113, 113, 113, 113, 113, 113,
    };
    const auto iterationCount = expectedSoftwarePeriod.size();

    auto tick = 0;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        constexpr auto speed = 10;
        // Posts cells.
        if (tick == 0) {
            const auto cellIndex = iterationIndex / speed;
            switch (cellIndex) {
                case 0:
                {
                    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((5 * 12) + 3), 1), channelIndex, { }));       // D-5
                    break;
                }
                case 1:
                {
                    const CellEffects cellEffects({ { Effect::pitchGlide, 0x200} });
                    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((5 * 12) + 5), { }, cellEffects), channelIndex, { }));       // E-5 g200
                    break;
                }
                case 2:
                {
                    const CellEffects cellEffects({ { Effect::pitchGlide, 0x200} });
                    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((5 * 12) + 1), { }, cellEffects), channelIndex, { }));       // C-5 g200
                    break;
                }
                default:
                    break;
            }
        }

        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == 15));
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == expectedSoftwarePeriod.at(iterationIndex)));
        REQUIRE_FALSE(registers.isRetrig());

        tick = (tick + 1) % speed;
    }
}

TEST_CASE("Channel player, PSG instrument is well stopped by sample instrument", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderHardwareSound songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    auto tick = 0;
    constexpr auto speed = 10;
    constexpr auto iterationCount = 5 * speed;
    constexpr auto sampleCellIndex = 2;
    constexpr auto sampleIterationIndex = sampleCellIndex * speed;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        // Posts cells.
        if (tick == 0) {
            const auto cellIndex = iterationIndex / speed;
            switch (cellIndex) {
                case 0:
                {
                    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote((5 * 12) + 3), 1), channelIndex, { }));       // D-5.
                    break;
                }
                case sampleCellIndex:
                {
                    channelPlayer.postCell(CellToPlay(Cell(Note::buildNote(6 * 12), 2), channelIndex, { }));           // Sample.
                    break;
                }
                default:
                    break;
            }
        }

        const auto isBeforeSampleTriggered = (iterationIndex < sampleIterationIndex);
        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getVolume() == (isBeforeSampleTriggered ? 16 : 0)));
        REQUIRE((registers.getSoundType() == (isBeforeSampleTriggered ? SoundType::softwareAndHardware : SoundType::noSoftwareNoHardware)));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == 100));
        REQUIRE_FALSE(registers.isRetrig());

        tick = (tick + 1) % speed;
    }
}

TEST_CASE("Channel player, Reset must stop the volume out", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderFullVolume songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    std::vector expectedVolumes = {
        14,     // 0. Volume is triggered from the start.
        14,     // 1.
        13,     // 2.
        13,     // 3.
        12,     // 4.
        12,     // 5.

        11,     // 6.
        11,     // 7.
        10,     // 8.
        10,     // 9.
        9,      // 10.
        9,      // 11.

        15,     // 12. Reset to F.
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
        15,
    };

    auto tick = 0;
    constexpr auto speed = 6;
    const auto iterationCount = expectedVolumes.size();
    constexpr auto resetIterationIndex = 2 * speed;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        // Posts cells.
        switch (iterationIndex) {
            // First cell: sound with a volume out.
            case 0:
            {
                const auto cell = Cell(Note::buildNote((5 * 12) + 3), 1, CellEffects({
                                               { Effect::volumeOut, 0x080 }
                }));
                channelPlayer.postCell(CellToPlay(cell, channelIndex, { })); // D-5.
                break;
            }
            case resetIterationIndex:
            {
                const auto cell = Cell({ }, { }, CellEffects({
                                               { Effect::reset, 0x0 }
                }));
                channelPlayer.postCell(CellToPlay(cell, channelIndex, { }));
                break;
            }
            default:
                break;
        }

        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == 100));
        REQUIRE_FALSE(registers.isRetrig());

        const auto readVolume = registers.getVolume();
        const auto expectedVolume = expectedVolumes.at(iterationIndex);
        REQUIRE((readVolume == expectedVolume));

        tick = (tick + 1) % speed;
    }
}

TEST_CASE("Channel player, Reset must stop the volume out. Reset uses an inverted volume", "[ChannelPlayer]")
{
    constexpr auto channelIndex = 0;
    DataProviderFullVolume songDataProvider;
    ChannelPlayer channelPlayer(songDataProvider, channelIndex);

    std::vector expectedVolumes = {
        14,     // 0. Volume is triggered from the start.
        14,     // 1.
        13,     // 2.
        13,     // 3.
        12,     // 4.
        12,     // 5.

        11,     // 6.
        11,     // 7.
        10,     // 8.
        10,     // 9.
        9,      // 10.
        9,      // 11.

        13,     // 12. Reset to 0xD.
        13,
        13,
        13,
        13,
        13,
        13,
        13,
        13,
        13,
        13,
    };

    auto tick = 0;
    constexpr auto speed = 6;
    const auto iterationCount = expectedVolumes.size();
    constexpr auto resetIterationIndex = 2 * speed;
    for (size_t iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        // Posts cells.
        switch (iterationIndex) {
            // First cell: sound with a volume out.
            case 0:
            {
                const auto cell = Cell(Note::buildNote((5 * 12) + 3), 1, CellEffects({
                                               { Effect::volumeOut, 0x080 }
                }));
                channelPlayer.postCell(CellToPlay(cell, channelIndex, { })); // D-5.
                break;
            }
            case resetIterationIndex:
            {
                const auto cell = Cell({ }, { }, CellEffects({
                                               { Effect::reset, 0x2 }
                }));
                channelPlayer.postCell(CellToPlay(cell, channelIndex, { }));
                break;
            }
            default:
                break;
        }

        auto result = channelPlayer.playStream((tick == 0), (tick < speed));
        const auto registers = result->getChannelOutputRegisters();
        REQUIRE((registers.getSoundType() == SoundType::softwareOnly));
        REQUIRE((registers.getNoise() == 0));
        REQUIRE((registers.getSoftwarePeriod() == 100));
        REQUIRE_FALSE(registers.isRetrig());

        const auto readVolume = registers.getVolume();
        const auto expectedVolume = expectedVolumes.at(iterationIndex);
        REQUIRE((readVolume == expectedVolume));

        tick = (tick + 1) % speed;
    }
}

}   // namespace arkostracker
