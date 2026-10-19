#include <memory>

#include "../../../catch.hpp"

#include "../../../../source/business/song/validation/CorrectInstrument.h"
#include "../../../../source/song/cells/CellConstants.h"
#include "../../../../source/song/instrument/Instrument.h"

namespace arkostracker 
{

TEST_CASE("correct PSG instrument", "[CorrectInstrument]")
{
    // Given.
    PsgPart psgPart;
    psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(99, 88, 88, 88, 0xffffff, true, 0)); // All illegal but period.
    psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(-99, -88, -88, -88, -0xffffff, true, 0xffffff)); // All illegal
    psgPart.addCell(PsgInstrumentCell::buildHardOnly(99, 30, -60, -0xffffff, 40,  true, 0xffffff));
    psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 30, 50,
        0xffffff, -60, 60, 0xfffff, 99,
        0xffffff, 60, -60, 0xfffff, 99,
        true,
        PsgValues::defaultSidActivated, 9999, 9999, 999, 9999, 9999999      // Too high values.
        ));
    const auto length = psgPart.getLength();
    psgPart.setMainLoop(Loop(50, 60, true));        // Wrong loop.
    psgPart.setAutoSpreadLoop(PsgSection::envelope, Loop(1, 2, true));
    psgPart.setAutoSpreadLoop(PsgSection::noise, Loop(0, 100, false));        // Wrong loop.
    psgPart.setAutoSpreadLoop(PsgSection::primaryPeriod, Loop(200, 100, true));        // Wrong loop.
    psgPart.setSpeed(9999);
    const auto instrument = Instrument::buildPsgInstrument("instr", psgPart, 0x10886655);       // Transparency, not allowed.

    // When.
    CorrectInstrument::correctInstrument(*instrument);

    // Then.
    REQUIRE((instrument->getArgbColor() == 0xff886655));
    const auto& newPsgPart = instrument->getPsgPart();
    REQUIRE((newPsgPart.getSpeed() == 255));
    auto index = 0;
    REQUIRE((newPsgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 31, 11, 10, 0xfff, true, 0)));
    REQUIRE((newPsgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(0, 0, 0, -10, -0xfff, true, 0xfff)));
    REQUIRE((newPsgPart.getCellRefConst(index++) == PsgInstrumentCell::buildHardOnly(31, 11, -10, -0xfff, 0xf, true, 0xffff)));
    REQUIRE((newPsgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 15, 31,
        0xfff, 0, 10, 0xfff, 7,
        0xffff, 11, -10, 0xfff, 15,
        true,
        PsgValues::defaultSidActivated, PsgValues::maximumPercent, PsgValues::maximumVolumeNoHard, PsgValues::sidMaximumRatio,
        PsgValues::sidMaximumArpeggio, PsgValues::sidMaximumPitch
        )));
    REQUIRE((newPsgPart.getLength() == index));
    REQUIRE((newPsgPart.getMainLoop() == Loop(3, 3, true)));
    REQUIRE((newPsgPart.getAutoSpreadLoop(PsgSection::envelope) == Loop(1, 2, true)));
    REQUIRE((newPsgPart.getAutoSpreadLoop(PsgSection::noise) == Loop(0, 3, false)));    // Corrected.
    REQUIRE((newPsgPart.getAutoSpreadLoop(PsgSection::primaryPeriod) == Loop(3, 3, true))); // Corrected.
    REQUIRE((length == index));
}

TEST_CASE("correct a valid PSG instrument", "[CorrectInstrument]")
{
    // Given. The instrument is completely valid, nothing should change.
    PsgPart psgPart;
    psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 31, 11, 10, 0xfff, true, 0xfff));
    psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0, 0, 0, 0, -0xfff, false, 0));
    psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 3, 10,
        123, 4, -3, -400, 4,
        456, 2, 6, 400, 15,
        false,
        PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
        PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch
        ));
    const auto length = psgPart.getLength();
    psgPart.setMainLoop(Loop(1, 2, true));
    psgPart.setAutoSpreadLoop(PsgSection::envelope, Loop(0, 2, true));
    psgPart.setAutoSpreadLoop(PsgSection::primaryPeriod, Loop(1, 1, false));
    psgPart.setAutoSpreadLoop(PsgSection::secondaryArpeggioOctave, Loop(2, 2, true));
    psgPart.setSpeed(12);
    const auto instrument = Instrument::buildPsgInstrument("instr", psgPart);

    // When.
    CorrectInstrument::correctInstrument(*instrument);

    // Then.
    REQUIRE((instrument->getArgbColor() == Instrument::defaultColor));
    const auto& newPsgPart = instrument->getPsgPart();
    REQUIRE((newPsgPart.getSpeed() == 12));
    auto index = 0;
    REQUIRE((newPsgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 31, 11, 10, 0xfff, true, 0xfff)));
    REQUIRE((newPsgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(0, 0, 0, 0, -0xfff, false, 0)));
    REQUIRE((newPsgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 3, 10,
        123, 4, -3, -400, 4,
        456, 2, 6, 400, 15,
        false,
        PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
        PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch
        )));
    REQUIRE((newPsgPart.getLength() == index));
    REQUIRE((newPsgPart.getMainLoop() == Loop(1, 2, true)));
    REQUIRE((newPsgPart.getAutoSpreadLoop(PsgSection::envelope) == Loop(0, 2, true)));
    REQUIRE((newPsgPart.getAutoSpreadLoop(PsgSection::primaryPeriod) == Loop(1, 1, false)));
    REQUIRE((newPsgPart.getAutoSpreadLoop(PsgSection::secondaryArpeggioOctave) == Loop(2, 2, true)));
    REQUIRE((length == index));
}

TEST_CASE("correct a valid SPL instrument", "[CorrectInstrument]")
{
    constexpr auto sampleLength = 50;
    const juce::MemoryBlock data(sampleLength, true);       // Fake sample data.
    const auto sample = std::make_shared<Sample>(data);
    SamplePart samplePart(sample, Loop(0, sampleLength - 1, true));
    samplePart.setAmplificationRatio(0.5F);
    samplePart.setDigidrumNote(14);
    samplePart.setFrequencyHz(9000);
    const auto instrument = Instrument::buildSampleInstrument("instr", samplePart);

    // When.
    CorrectInstrument::correctInstrument(*instrument);

    // Then.
    const auto& newSamplePart = instrument->getSamplePart();
    REQUIRE((newSamplePart.getLoop() == Loop(0, sampleLength - 1, true)));
    REQUIRE(juce::approximatelyEqual(newSamplePart.getAmplificationRatio(), 0.5F));
    REQUIRE((newSamplePart.getDigidrumNote() == 14));
    REQUIRE((newSamplePart.getFrequencyHz() == 9000));
}

TEST_CASE("correct a SPL instrument", "[CorrectInstrument]")
{
    // Given.
    constexpr auto sampleLength = 50;
    const juce::MemoryBlock data(sampleLength, true);       // Fake sample data.
    const auto sample = std::make_shared<Sample>(data);
    SamplePart samplePart(sample, Loop(30, 5000, true));
    samplePart.setAmplificationRatio(999.0F);
    samplePart.setDigidrumNote(10000);
    samplePart.setFrequencyHz(99999999);
    const auto instrument = Instrument::buildSampleInstrument("instr", samplePart);

    // When.
    CorrectInstrument::correctInstrument(*instrument);

    // Then.
    const auto& newSamplePart = instrument->getSamplePart();
    REQUIRE((newSamplePart.getLoop() == Loop(30, sampleLength - 1, true)));
    REQUIRE(juce::approximatelyEqual(newSamplePart.getAmplificationRatio(), PsgValues::maximumSampleAmplificationRatio));
    REQUIRE((newSamplePart.getDigidrumNote() == CellConstants::maximumNote));
    REQUIRE((newSamplePart.getFrequencyHz() == PsgFrequency::maximumSampleFrequency));
}

}   // namespace arkostracker
