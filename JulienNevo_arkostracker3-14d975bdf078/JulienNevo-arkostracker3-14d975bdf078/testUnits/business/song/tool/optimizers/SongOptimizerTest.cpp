#include "../../../../catch.hpp"

#include "../../../../../source/business/instrument/GenericInstrumentGenerator.h"
#include "../../../../../source/business/song/tool/optimizers/SongOptimizer.h"
#include "../../../../../source/export/ExportConfiguration.h"
#include "../../../../../source/export/sourceGenerator/SourceGeneratorConfiguration.h"
#include "../../../../../source/import/loader/SongLoader.h"
#include "../../../../helper/SongTestHelper.h"
#include "../../../../helper/TrackTestHelper.h"
#include "BinaryData.h"

namespace arkostracker 
{

class Check
{
public:
    static void checkInstrumentEmpty(const Song& song, const Id& instrumentId) noexcept
    {
        song.performOnConstInstrument(instrumentId, [&](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Empty");
            REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument.getConstPsgPart();
            REQUIRE(psgPart.getLength() == 0x1);
            REQUIRE(psgPart.getCellRefConst(0) == PsgInstrumentCell::buildNoSoftwareNoHardwareCell(0));
        });
    }

    static void checkInstrumentBeep(const Song& song, const Id& instrumentId) noexcept
    {
        song.performOnConstInstrument(instrumentId, [&](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Beep");
            REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument.getConstPsgPart();
            REQUIRE(psgPart.getLength() == 0xf);
            REQUIRE(psgPart.getMainLoop() == Loop(14, 14, false));
            REQUIRE(psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15));
            REQUIRE(psgPart.getCellRefConst(0xe) == PsgInstrumentCell::buildSoftwareCell(1));
        });
    }

    static void checkInstrumentSingle(const Song& song, const Id& instrumentId) noexcept
    {
        song.performOnConstInstrument(instrumentId, [&](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Single");
            REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument.getConstPsgPart();
            REQUIRE(psgPart.getLength() == 0x1);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0, false));
            REQUIRE(psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15));
        });
    }

    static void checkPitchEmpty(const ExpressionHandler& expressionHandler, const Id& expressionId) noexcept
    {
        const auto expression = expressionHandler.getExpressionCopy(expressionId);
        REQUIRE_FALSE(expression.isArpeggio());
        REQUIRE(expression.getName() == "Default");
        REQUIRE(expression.getLength() == 0x1);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getValue(0) == 0);
    }

    static void checkPitch1(const ExpressionHandler& expressionHandler, const Id& expressionId) noexcept
    {
        const auto expression = expressionHandler.getExpressionCopy(expressionId);
        REQUIRE_FALSE(expression.isArpeggio());
        REQUIRE(expression.getName() == "Pitch1");
        REQUIRE(expression.getLength() == 0x8);
        REQUIRE(expression.getLoop() == Loop(0, 7, true));
        REQUIRE(expression.getValue(0) == 0);
        REQUIRE(expression.getValue(1) == 1);
        REQUIRE(expression.getValue(2) == 2);
        REQUIRE(expression.getValue(3) == 1);
        REQUIRE(expression.getValue(4) == 0);
        REQUIRE(expression.getValue(5) == -1);
        REQUIRE(expression.getValue(6) == -2);
        REQUIRE(expression.getValue(7) == -1);
    }

    static void checkPitch2(const ExpressionHandler& expressionHandler, const Id& expressionId) noexcept
    {
        const auto expression = expressionHandler.getExpressionCopy(expressionId);
        REQUIRE_FALSE(expression.isArpeggio());
        REQUIRE(expression.getName() == "Pitch2");
        REQUIRE(expression.getLength() == 0x5);
        REQUIRE(expression.getLoop() == Loop(4, 4, true));
        REQUIRE(expression.getValue(0) == -0x28);
        REQUIRE(expression.getValue(1) == -0x1e);
        REQUIRE(expression.getValue(2) == -0x14);
        REQUIRE(expression.getValue(3) == -0xa);
        REQUIRE(expression.getValue(4) == 0);
    }

    static void checkArpeggioEmpty(const ExpressionHandler& expressionHandler, const Id& expressionId) noexcept
    {
        const auto expression = expressionHandler.getExpressionCopy(expressionId);
        REQUIRE(expression.isArpeggio());
        REQUIRE(expression.getName() == "Default");
        REQUIRE(expression.getLength() == 0x1);
        REQUIRE(expression.getValue(0) == 0);
    }

    static void checkArpeggio1(const ExpressionHandler& expressionHandler, const Id& expressionId) noexcept
    {
        const auto expression = expressionHandler.getExpressionCopy(expressionId);
        REQUIRE(expression.isArpeggio());
        REQUIRE(expression.getName() == "Arp1");
        REQUIRE(expression.getLength() == 0x3);
        REQUIRE(expression.getLoop() == Loop(0, 2, true));
        REQUIRE(expression.getValue(0) == 0);
        REQUIRE(expression.getValue(1) == 4);
        REQUIRE(expression.getValue(2) == 7);
    }

    static void checkArpeggio2(const ExpressionHandler& expressionHandler, const Id& expressionId) noexcept
    {
        const auto expression = expressionHandler.getExpressionCopy(expressionId);
        REQUIRE(expression.isArpeggio());
        REQUIRE(expression.getName() == "Arp2");
        REQUIRE(expression.getLength() == 0x2);
        REQUIRE(expression.getLoop() == Loop(1, 1, true));
        REQUIRE(expression.getValue(0) == 12);
        REQUIRE(expression.getValue(1) == 0);
    }
};


TEST_CASE("SongOptimizer, optimize", "[SongOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());           // 2, unused.
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());              // 3.
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForAttackSustainDecay()); // 4 used by only after limit, so cut.
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 5, same as 1, so optimized away.

    {
        auto& arpeggioHandler = originalSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));
        arpeggioHandler.addExpression(Expression::build("a1", true, { 0, 3, 7 }));      // Unused.
        arpeggioHandler.addExpression(Expression::build("a2", true, { 0, 4, 7, 12 }));

        auto& pitchHandler = originalSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
        pitchHandler.addExpression(Expression::build("p1", false, { 12, 5, -5 }));          // Unused after optimization.
        pitchHandler.addExpression(Expression::build("p2", false, { -10, 0, 10, 40, 0 }));  // Unused.
        pitchHandler.addExpression(Expression::build("p3", false, { 12, 5, -5 }));          // Unused after optimization.
    }

    SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 1,
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                                       Pattern({ 7, 8, 9 }, 1, 1),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                           { 12,  Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 127, Cell::build(12, 4, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 5) },
                                                                           { 12, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                           { 12,  Cell::build(12, 3, CellEffects({
                                                                                                                         { Effect::arpeggioTable, 2 },
                                                                                                                         { Effect::arpeggioTable, 2 }
                                                                                                                 })) },
                                                                           { 120, Cell::build(12, 4, CellEffects({{ Effect::pitchTable, 3 }})) },
                                                                   }),
                                       // Track 3. Unused.
                                       TrackTestHelper::buildTrack({
                                                                           { 0,  Cell::build(12, 3, CellEffects({{ Effect::pitchTable, 1 }})) },
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 28, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 1 }})) },
                                                                           { 30, Cell::build(20, 3, CellEffects({{ Effect::pitchTable, 3 }})) },
                                                                   }),
                                       // Track 4. Unused.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 5. Unused.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 6. Unused
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 7
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 64, Cell::build(12, 4, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 8.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 5) },
                                                                           { 12, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 65, Cell::build(12, 4, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 9.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 66, Cell::build(12, 4, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       // Speed Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 64, SpecialCell::buildSpecialCell(10) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                                       // Event Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                                  { 64, SpecialCell::buildSpecialCell(1) },
                                                                          }),
                               }
    );

    // When.
    const auto newSong = SongOptimizer::optimize(*originalSong, { originalSong->getFirstSubsongId() });
    REQUIRE((newSong != nullptr));

    const auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    {
        auto& arpeggioHandler = expectedSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));
        arpeggioHandler.addExpression(Expression::build("a2", true, { 0, 4, 7, 12 }));

        auto& pitchHandler = expectedSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
    }

    SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 1,
                               {
                                       Position(0, 64),
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 0, 0, 0 }, 0, 0),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 }})) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                               }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("SongOptimizer, illegal instruments and expressions", "[SongOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());              // 2. Unused.

    {
        auto& arpeggioHandler = originalSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));
        arpeggioHandler.addExpression(Expression::build("a1", true, { 0, 3, 7 }));      // Unused.

        auto& pitchHandler = originalSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
        pitchHandler.addExpression(Expression::build("p1", false, { 12, 5, -5 }));          // Unused after optimization.
    }

    SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 0,
                               {
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 1),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 0, Cell::buildRst() },
                                                                           { 2, Cell::build(10, 1) },
                                                                           { 3, Cell::build(12, 1, CellEffects({{ Effect::pitchTable, 10 }})) },
                                                                           { 4, Cell::build(12, 1, CellEffects({{ Effect::arpeggioTable, 20 }})) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 0, Cell::build(12, 100) },
                                                                           { 2, Cell::build(10, 1) },
                                                                           { 3, Cell::build(12, 1, CellEffects({{ Effect::pitchTable, 10 }})) },
                                                                           { 4, Cell::build(12, 1, CellEffects({{ Effect::arpeggioTable, 20 }})) },
                                                                   }),
                                       // Track 3. Unused.
                                       TrackTestHelper::buildTrack({
                                                                           { 0,  Cell::build(12, 3, CellEffects({{ Effect::pitchTable, 1 }})) },
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 28, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 1 }})) },
                                                                           { 30, Cell::build(20, 3, CellEffects({{ Effect::pitchTable, 3 }})) },
                                                                   }),
                                       // Track 4. Unused.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 5. Unused.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 6. Unused
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 7. Unused
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 64, Cell::build(12, 4, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 8.. Unused
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 5) },
                                                                           { 12, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 65, Cell::build(12, 4, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 9.. Unused
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 3, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 66, Cell::build(12, 4, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildEmptySpecialTrack(),
                                       // Speed Track 1. Unused
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 64, SpecialCell::buildSpecialCell(10) },
                                                                          }),
                               },
                               {
                                       // Event Track 0. Unused
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                                       // Event Track 1.
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );


    // When.
    const auto newSong = SongOptimizer::optimize(*originalSong, { originalSong->getFirstSubsongId() });
    REQUIRE((newSong != nullptr));

    const auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    {
        auto& arpeggioHandler = expectedSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));

        auto& pitchHandler = expectedSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
    }

    SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 0,
                               {
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 0, 1, 1 }, 0, 0),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 0, Cell::buildRst() },
                                                                           { 2, Cell::build(10, 1) },
                                                                           { 3, Cell::build(12, 1, CellEffects({{ Effect::pitchTable, 0 }})) },
                                                                           { 4, Cell::build(12, 1, CellEffects({{ Effect::arpeggioTable, 0 }})) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("PatternOptimizer, Sarkboteur", "[PatternOptimizer]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At2Sarkboteur_aks, BinaryData::At2Sarkboteur_aksSize, false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult != nullptr);
    REQUIRE(loadResult->errorReport != nullptr);
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { song->getFirstSubsongId() }, "label_", 0x4000,
                                            SampleEncoderFlags::buildNoExport());
    const auto newSong = SongOptimizer::optimize(*song, exportConfiguration);
    REQUIRE(newSong != nullptr);

    // Then.
    const auto newSubsongId = newSong->getFirstSubsongId();
    REQUIRE(newSong->getSubsongCount() == 1);
    REQUIRE(newSong->getInstrumentCount() == 11);
    REQUIRE(newSong->getExpressionHandler(true).getCount() == 8);
    REQUIRE(newSong->getExpressionHandler(false).getCount() == 4);
    newSong->performOnConstSubsong(newSubsongId, [&](const Subsong& subsong) {
        REQUIRE(subsong.getTrackCount() == 45);
        REQUIRE(subsong.getSpecialTrackCount(true) == 1);
        REQUIRE(subsong.getSpecialTrackCount(false) == 3);
    });
}

TEST_CASE("SongOptimizer, one out of several subsongs, instruments are still present", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongs_xml, static_cast<size_t>(BinaryData::At3_6subsongs_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto song = SongOptimizer::optimize(*originalSong, { originalSong->getFirstSubsongId() });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getInstrumentCount() == 2);
}

TEST_CASE("SongOptimizer, all subsongs, instruments are not duplicated", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongs_xml, static_cast<size_t>(BinaryData::At3_6subsongs_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        const auto subsongIds = originalSong->getSubsongIds();

        // When.
        const auto song = SongOptimizer::optimize(*originalSong, subsongIds);
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getInstrumentCount() == 2);
        REQUIRE(song->getConstExpressionHandler(true).getCount() == 1);
        REQUIRE(song->getConstExpressionHandler(false).getCount() == 1);
}

TEST_CASE("SongOptimizer, subsongs with more data, subsong1", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);
        REQUIRE(originalSong->getSubsongCount() == 6);

        // When.
        const auto subsongId = originalSong->getSubsongIds().at(0);
        const auto song = SongOptimizer::optimize(*originalSong, { subsongId });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 1);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 2);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());
        Check::checkInstrumentBeep(*song, song->getInstrumentId(1).getValue());

        REQUIRE(arpeggioHandler.getCount() == 1);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());

        REQUIRE(pitchHandler.getCount() == 1);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
}

TEST_CASE("SongOptimizer, subsongs with more data, subsong2", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto subsongId = originalSong->getSubsongIds().at(1);
        const auto song = SongOptimizer::optimize(*originalSong, { subsongId });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 1);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 1);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());

        REQUIRE(arpeggioHandler.getCount() == 1);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());

        REQUIRE(pitchHandler.getCount() == 1);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
}

TEST_CASE("SongOptimizer, subsongs with more data, subsong3", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto subsongId = originalSong->getSubsongIds().at(2);
        const auto song = SongOptimizer::optimize(*originalSong, { subsongId });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 1);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 2);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());
        Check::checkInstrumentSingle(*song, song->getInstrumentId(1).getValue());

        REQUIRE(arpeggioHandler.getCount() == 2);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());
        Check::checkArpeggio1(arpeggioHandler, arpeggioHandler.getId(1).getValue());

        REQUIRE(pitchHandler.getCount() == 1);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
}

TEST_CASE("SongOptimizer, subsongs with more data, subsong4", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto subsongId = originalSong->getSubsongIds().at(3);
        const auto song = SongOptimizer::optimize(*originalSong, { subsongId });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 1);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 3);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());
        Check::checkInstrumentBeep(*song, song->getInstrumentId(1).getValue());
        Check::checkInstrumentSingle(*song, song->getInstrumentId(2).getValue());

        REQUIRE(arpeggioHandler.getCount() == 1);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());

        REQUIRE(pitchHandler.getCount() == 1);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
}

TEST_CASE("SongOptimizer, subsongs with more data, subsong5", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto subsongId = originalSong->getSubsongIds().at(4);
        const auto song = SongOptimizer::optimize(*originalSong, { subsongId });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 1);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 3);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());
        Check::checkInstrumentBeep(*song, song->getInstrumentId(1).getValue());
        Check::checkInstrumentSingle(*song, song->getInstrumentId(2).getValue());

        REQUIRE(arpeggioHandler.getCount() == 3);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());
        Check::checkArpeggio1(arpeggioHandler, arpeggioHandler.getId(1).getValue());
        Check::checkArpeggio2(arpeggioHandler, arpeggioHandler.getId(2).getValue());

        REQUIRE(pitchHandler.getCount() == 3);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
        Check::checkPitch1(pitchHandler, pitchHandler.getId(1).getValue());
        Check::checkPitch2(pitchHandler, pitchHandler.getId(2).getValue());
}

TEST_CASE("SongOptimizer, subsongs with more data, subsong6", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto subsongId = originalSong->getSubsongIds().at(5);
        const auto song = SongOptimizer::optimize(*originalSong, { subsongId });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 1);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 2);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());
        Check::checkInstrumentBeep(*song, song->getInstrumentId(1).getValue());

        REQUIRE(arpeggioHandler.getCount() == 1);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());

        REQUIRE(pitchHandler.getCount() == 2);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
        Check::checkPitch2(pitchHandler, pitchHandler.getId(1).getValue());
}

TEST_CASE("SongOptimizer, subsongs with more data, all subsongs", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto subsongIds = originalSong->getSubsongIds();
        const auto song = SongOptimizer::optimize(*originalSong, subsongIds);
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 6);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 3);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());
        Check::checkInstrumentBeep(*song, song->getInstrumentId(1).getValue());
        Check::checkInstrumentSingle(*song, song->getInstrumentId(2).getValue());

        REQUIRE(arpeggioHandler.getCount() == 3);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());
        Check::checkArpeggio1(arpeggioHandler, arpeggioHandler.getId(1).getValue());
        Check::checkArpeggio2(arpeggioHandler, arpeggioHandler.getId(2).getValue());

        REQUIRE(pitchHandler.getCount() == 3);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
        Check::checkPitch1(pitchHandler, pitchHandler.getId(1).getValue());
        Check::checkPitch2(pitchHandler, pitchHandler.getId(2).getValue());
}

TEST_CASE("SongOptimizer, subsongs with more data, subsong 3 and 4", "[SongOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongsMoreData_xml, static_cast<size_t>(BinaryData::At3_6subsongsMoreData_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        // When.
        const auto subsongIds = originalSong->getSubsongIds();
        const auto song = SongOptimizer::optimize(*originalSong, { subsongIds.at(2), subsongIds.at(3) });
        REQUIRE(song != nullptr);

        // Then.
        REQUIRE(song->getSubsongCount() == 2);

        const auto& arpeggioHandler = song->getConstExpressionHandler(true);
        const auto& pitchHandler = song->getConstExpressionHandler(false);

        REQUIRE(song->getInstrumentCount() == 3);
        Check::checkInstrumentEmpty(*song, song->getInstrumentId(0).getValue());
        Check::checkInstrumentBeep(*song, song->getInstrumentId(1).getValue());
        Check::checkInstrumentSingle(*song, song->getInstrumentId(2).getValue());

        REQUIRE(arpeggioHandler.getCount() == 2);
        Check::checkArpeggioEmpty(arpeggioHandler, arpeggioHandler.getId(0).getValue());
        Check::checkArpeggio1(arpeggioHandler, arpeggioHandler.getId(1).getValue());

        REQUIRE(pitchHandler.getCount() == 1);
        Check::checkPitchEmpty(pitchHandler, pitchHandler.getId(0).getValue());
}

}   // namespace arkostracker
