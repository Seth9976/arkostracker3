#include "../../../catch.hpp"

#include "../../../../source/business/serialization/patternViewer/TrackSerializer.h"
#include "../XmlTestHelper.h"
#include "../../../../source/business/serialization/song/CellSerializer.h"
#include "../../../../source/business/serialization/song/SpecialCellSerializer.h"
#include "../../../../source/utils/XmlHelper.h"

namespace arkostracker 
{

TEST_CASE("Serialization one track, not full capture", "[TrackSerializerTest]")
{
    // Given.
    std::vector<SpecialCell> speedCells;
    std::vector<SpecialCell> eventCells;

    std::vector<CaptureFlags> captureFlagList;
    captureFlagList.emplace_back(false, true, true, true, true, false);

    std::vector<std::vector<Cell>> tracksOfCells;
    {
        std::vector<Cell> trackCells;
        trackCells.emplace_back(Note::buildNote(40), 1);
        trackCells.emplace_back();
        trackCells.emplace_back(Note::buildNote(41), 2);
        trackCells.emplace_back();
        trackCells.emplace_back();
        trackCells.emplace_back(Note::buildNote(42), 3);

        tracksOfCells.push_back(trackCells);
    }

    // When.
    const auto rootElementPtr = TrackSerializer::serialize(tracksOfCells, captureFlagList, speedCells, eventCells);

    // Then.
    REQUIRE(rootElementPtr != nullptr);
    const auto& rootElement = *rootElementPtr;
    REQUIRE(rootElement.hasTagName(TrackSerializer::nodeRoot));
    REQUIRE(rootElement.getNumChildElements() == 2);       // Height and Track.
    XmlTestHelper::checkXmlInt(&rootElement, TrackSerializer::nodeHeight, 6);

    const auto* trackElement = XmlTestHelper::getChildByIndex(rootElement, 1, TrackSerializer::nodeTrack);
    REQUIRE(trackElement != nullptr);

    REQUIRE(trackElement->getNumChildElements() == 4);          // Only 3 cells are non-empty, plus the capture.
    // Checks the Capture.
    const auto* captureElement = trackElement->getChildByName(TrackSerializer::nodeCaptureFlags);
    REQUIRE(captureElement != nullptr);
    REQUIRE(captureElement->getNumChildElements() == 6);
    XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsNoteCaptured, false);
    XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsInstrumentCaptured, true);
    XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect1Captured, true);
    XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect2Captured, true);
    XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect3Captured, true);
    XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect4Captured, false);

    // Checks the Cells.
    const auto cellNodes = XmlHelper::getChildrenList(*trackElement, CellSerializer::nodeCell);
    size_t cellIndex = 0;
    {
        const auto* cellNode = cellNodes.at(cellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 3);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 0);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 40);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 1);
    }
    {
        const auto* cellNode = cellNodes.at(cellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 3);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 2);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 41);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 2);
    }
    {
        const auto* cellNode = cellNodes.at(cellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 3);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 5);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 42);
        XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 3);
    }
    REQUIRE(cellNodes.size() == cellIndex);
}

TEST_CASE("Serialization one event track", "[TrackSerializerTest]")
{
    // Given.
    std::vector<SpecialCell> speedCells;
    std::vector<SpecialCell> eventCells;
    eventCells.push_back(SpecialCell::buildSpecialCell(56));
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildSpecialCell(57));
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildSpecialCell(58));
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());

    std::vector<CaptureFlags> captureFlagList;
    std::vector<std::vector<Cell>> tracksOfCells;

    // When.
    const auto rootElementPtr = TrackSerializer::serialize(tracksOfCells, captureFlagList, speedCells, eventCells);

    // Then.
    REQUIRE(rootElementPtr != nullptr);
    const auto& rootElement = *rootElementPtr;
    REQUIRE(rootElement.hasTagName(TrackSerializer::nodeRoot));
    REQUIRE(rootElement.getNumChildElements() == 2);       // Height and Speed Track.
    XmlTestHelper::checkXmlInt(&rootElement, TrackSerializer::nodeHeight, 9);

    const auto* eventTrackElement = XmlTestHelper::getChildByIndex(rootElement, 1, TrackSerializer::nodeEventTrack);
    REQUIRE(eventTrackElement != nullptr);

    // Checks the Event Track.
    const auto specialCellNodes = XmlHelper::getChildrenList(*eventTrackElement, SpecialCellSerializer::nodeSpecialCell);
    size_t specialCellIndex = 0;
    {
        const auto* cellNode = specialCellNodes.at(specialCellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 2);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeIndex, 0);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeValue, 56);
    }
    {
        const auto* cellNode = specialCellNodes.at(specialCellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 2);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeIndex, 4);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeValue, 57);
    }
    {
        const auto* cellNode = specialCellNodes.at(specialCellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 2);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeIndex, 6);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeValue, 58);
    }
    REQUIRE(specialCellNodes.size() == specialCellIndex);
}

TEST_CASE("Serialization three tracks, and both speed and event tracks", "[TrackSerializerTest]")
{
    // Given.
    std::vector<SpecialCell> speedCells;
    speedCells.push_back(SpecialCell::buildEmptySpecialCell());
    speedCells.push_back(SpecialCell::buildSpecialCell(12));
    speedCells.push_back(SpecialCell::buildSpecialCell(13));
    speedCells.push_back(SpecialCell::buildEmptySpecialCell());

    std::vector<SpecialCell> eventCells;
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());
    eventCells.push_back(SpecialCell::buildEmptySpecialCell());

    std::vector<CaptureFlags> captureFlagList;
    captureFlagList.emplace_back(false, false, true, true, true, true);
    captureFlagList.emplace_back(true, true, true, true, true, true);
    captureFlagList.emplace_back(true, true, true, true, false, false);

    std::vector<std::vector<Cell>> tracksOfCells;
    {
        // Track 0.
        std::vector<Cell> trackCells;
        trackCells.emplace_back();
        trackCells.emplace_back(Note::buildNote(40), 0);
        trackCells.emplace_back(Note::buildNote(41), 2);
        trackCells.emplace_back(Note::buildNote(42), 255);

        tracksOfCells.push_back(trackCells);
    }
    {
        // Track 1.
        std::vector<Cell> trackCells;
        trackCells.emplace_back();
        trackCells.emplace_back();
        trackCells.emplace_back();
        trackCells.emplace_back();

        tracksOfCells.push_back(trackCells);
    }
    {
        // Track 2.
        std::vector<Cell> trackCells;
        trackCells.emplace_back(Note::buildNote(1), 10);
        trackCells.emplace_back();
        trackCells.emplace_back(Note::buildNote(2), 11);
        trackCells.emplace_back();

        tracksOfCells.push_back(trackCells);
    }

    // When.
    const auto rootElementPtr = TrackSerializer::serialize(tracksOfCells, captureFlagList, speedCells, eventCells);

    // Then.
    REQUIRE(rootElementPtr != nullptr);
    const auto& rootElement = *rootElementPtr;
    REQUIRE(rootElement.hasTagName(TrackSerializer::nodeRoot));
    REQUIRE(rootElement.getNumChildElements() == 6);       // Height, 3 Tracks, 2 Special Tracks.
    XmlTestHelper::checkXmlInt(&rootElement, TrackSerializer::nodeHeight, 4);

    // Checks Track 0.
    {
        const auto* trackElement = XmlTestHelper::getChildByIndex(rootElement, 1, TrackSerializer::nodeTrack);
        REQUIRE(trackElement != nullptr);

        REQUIRE(trackElement->getNumChildElements() == 4);          // Only 3 cells are non-empty, plus the capture.
        // Checks the Capture.
        const auto* captureElement = trackElement->getChildByName(TrackSerializer::nodeCaptureFlags);
        REQUIRE(captureElement != nullptr);
        REQUIRE(captureElement->getNumChildElements() == 6);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsNoteCaptured, false);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsInstrumentCaptured, false);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect1Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect2Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect3Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect4Captured, true);

        // Checks the Cells.
        const auto cellNodes = XmlHelper::getChildrenList(*trackElement, CellSerializer::nodeCell);
        size_t cellIndex = 0;
        {
            const auto* cellNode = cellNodes.at(cellIndex++);
            REQUIRE(cellNode->getNumChildElements() == 3);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 1);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 40);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 0);
        }
        {
            const auto* cellNode = cellNodes.at(cellIndex++);
            REQUIRE(cellNode->getNumChildElements() == 3);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 2);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 41);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 2);
        }
        {
            const auto* cellNode = cellNodes.at(cellIndex++);
            REQUIRE(cellNode->getNumChildElements() == 3);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 3);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 42);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 255);
        }
        REQUIRE(cellNodes.size() == cellIndex);
    }

    // Checks Track 1.
    {
        const auto* trackElement = XmlTestHelper::getChildByIndex(rootElement, 2, TrackSerializer::nodeTrack);
        REQUIRE(trackElement != nullptr);

        REQUIRE(trackElement->getNumChildElements() == 1);          // All cells are empty, so there is only the capture.
        // Checks the Capture.
        const auto* captureElement = trackElement->getChildByName(TrackSerializer::nodeCaptureFlags);
        REQUIRE(captureElement != nullptr);
        REQUIRE(captureElement->getNumChildElements() == 6);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsNoteCaptured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsInstrumentCaptured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect1Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect2Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect3Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect4Captured, true);

        // Checks that no Cells are encoded.
        REQUIRE(trackElement->getChildByName(CellSerializer::nodeCell) == nullptr);
    }

    // Checks Track 2.
    {
        const auto* trackElement = XmlTestHelper::getChildByIndex(rootElement, 3, TrackSerializer::nodeTrack);
        REQUIRE(trackElement != nullptr);

        REQUIRE(trackElement->getNumChildElements() == 3);          // Only 2 cells are non-empty, plus the capture.
        // Checks the Capture.
        const auto* captureElement = trackElement->getChildByName(TrackSerializer::nodeCaptureFlags);
        REQUIRE(captureElement != nullptr);
        REQUIRE(captureElement->getNumChildElements() == 6);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsNoteCaptured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsInstrumentCaptured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect1Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect2Captured, true);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect3Captured, false);
        XmlTestHelper::checkXmlBool(captureElement, TrackSerializer::nodeIsEffect4Captured, false);

        // Checks the Cells.
        const auto cellNodes = XmlHelper::getChildrenList(*trackElement, CellSerializer::nodeCell);
        size_t cellIndex = 0;
        {
            const auto* cellNode = cellNodes.at(cellIndex++);
            REQUIRE(cellNode->getNumChildElements() == 3);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 0);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 1);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 10);
        }
        {
            const auto* cellNode = cellNodes.at(cellIndex++);
            REQUIRE(cellNode->getNumChildElements() == 3);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeIndex, 2);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeNote, 2);
            XmlTestHelper::checkXmlInt(cellNode, CellSerializer::nodeInstrument, 11);
        }
        REQUIRE(cellNodes.size() == cellIndex);
    }

    // Checks the Speed track.
    const auto* speedTrackElement = XmlTestHelper::getChildByIndex(rootElement, 4, TrackSerializer::nodeSpeedTrack);
    REQUIRE(speedTrackElement != nullptr);

    // Checks the Event Track.
    const auto specialCellNodes = XmlHelper::getChildrenList(*speedTrackElement, SpecialCellSerializer::nodeSpecialCell);
    size_t specialCellIndex = 0;
    {
        const auto* cellNode = specialCellNodes.at(specialCellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 2);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeIndex, 1);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeValue, 12);
    }
    {
        const auto* cellNode = specialCellNodes.at(specialCellIndex++);
        REQUIRE(cellNode->getNumChildElements() == 2);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeIndex, 2);
        XmlTestHelper::checkXmlInt(cellNode, SpecialCellSerializer::nodeValue, 13);
    }
    REQUIRE(specialCellNodes.size() == specialCellIndex);

    // Checks the Event Track. It is empty.
    const auto* eventTrackElement = XmlTestHelper::getChildByIndex(rootElement, 5, TrackSerializer::nodeEventTrack);
    REQUIRE(eventTrackElement != nullptr);

    REQUIRE(eventTrackElement->getNumChildElements() == 0);
}


// ========================================================================

TEST_CASE("Deserialization, one track", "[TrackSerializerTest]")
{
    // Given.
    juce::XmlElement rootNode(TrackSerializer::nodeRoot);
    XmlHelper::addValueNode(rootNode, TrackSerializer::nodeHeight, 6);
    // Track.
    {
        auto& trackNode = XmlHelper::addNode(rootNode, TrackSerializer::nodeTrack);
        {
            auto& cellNode = XmlHelper::addNode(trackNode, CellSerializer::nodeCell);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeIndex, 2);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeNote, 40);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeInstrument, 1);
        }
        {
            auto& cellNode = XmlHelper::addNode(trackNode, CellSerializer::nodeCell);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeIndex, 4);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeNote, 41);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeInstrument, 10);
        }

        // CaptureFlag.
        {
            auto& captureFlag = XmlHelper::addNode(trackNode, TrackSerializer::nodeCaptureFlags);
            XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsNoteCaptured, false);
            XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsInstrumentCaptured, true);
            XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect1Captured, true);
            XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect2Captured, true);
            XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect3Captured, true);
            XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect4Captured, false);
        }
    }

    // When.
    const auto result = TrackSerializer::deserialize(rootNode);

    // Then.
    REQUIRE(result.isValid());
    REQUIRE(result.height == 6);
    REQUIRE(result.speedCells.empty());
    REQUIRE(result.eventCells.empty());
    REQUIRE(result.captureFlags.size() == 1);
    {
        const auto& captureFlag = result.captureFlags.at(0);
        REQUIRE_FALSE(captureFlag.isNoteCaptured());
        REQUIRE(captureFlag.isInstrumentCaptured());
        REQUIRE(captureFlag.isEffect1Captured());
        REQUIRE(captureFlag.isEffect2Captured());
        REQUIRE(captureFlag.isEffect3Captured());
        REQUIRE_FALSE(captureFlag.isEffect4Captured());
    }
    REQUIRE(result.tracksToCells.size() == 1);
    {
        const auto& cells = result.tracksToCells.at(0);
        size_t cellIndex = 0;
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell(Note::buildNote(40), 1));
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell(Note::buildNote(41), 10));
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.size() == cellIndex);
    }
}

TEST_CASE("Deserialization, three tracks, speed track, event track empty", "[TrackSerializerTest]")
{
    // Given.
    juce::XmlElement rootNode(TrackSerializer::nodeRoot);
    XmlHelper::addValueNode(rootNode, TrackSerializer::nodeHeight, 8);
    // Track 0.
    {
        auto& trackNode = XmlHelper::addNode(rootNode, TrackSerializer::nodeTrack);
        {
            auto& cellNode = XmlHelper::addNode(trackNode, CellSerializer::nodeCell);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeIndex, 0);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeNote, 40);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeInstrument, 1);
        }
        {
            auto& cellNode = XmlHelper::addNode(trackNode, CellSerializer::nodeCell);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeIndex, 7);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeNote, 41);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeInstrument, 10);
        }

        auto& captureFlag = XmlHelper::addNode(trackNode, TrackSerializer::nodeCaptureFlags);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsNoteCaptured, false);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsInstrumentCaptured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect1Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect2Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect3Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect4Captured, true);
    }
    // Track 1 (empty).
    {
        auto& trackNode = XmlHelper::addNode(rootNode, TrackSerializer::nodeTrack);

        auto& captureFlag = XmlHelper::addNode(trackNode, TrackSerializer::nodeCaptureFlags);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsNoteCaptured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsInstrumentCaptured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect1Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect2Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect3Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect4Captured, true);
    }
    // Track 2.
    {
        auto& trackNode = XmlHelper::addNode(rootNode, TrackSerializer::nodeTrack);
        {
            auto& cellNode = XmlHelper::addNode(trackNode, CellSerializer::nodeCell);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeIndex, 4);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeNote, 80);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeInstrument, 0);
        }
        {
            auto& cellNode = XmlHelper::addNode(trackNode, CellSerializer::nodeCell);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeIndex, 5);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeNote, 81);
            XmlHelper::addValueNode(cellNode, CellSerializer::nodeInstrument, 255);
        }

        auto& captureFlag = XmlHelper::addNode(trackNode, TrackSerializer::nodeCaptureFlags);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsNoteCaptured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsInstrumentCaptured, false);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect1Captured, false);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect2Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect3Captured, true);
        XmlHelper::addValueNode(captureFlag, TrackSerializer::nodeIsEffect4Captured, true);
    }

    // Speed Cells.
    {
        auto& speedTrackNode = XmlHelper::addNode(rootNode, TrackSerializer::nodeSpeedTrack);
        {
            auto& specialCellNode = XmlHelper::addNode(speedTrackNode, SpecialCellSerializer::nodeSpecialCell);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 4);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 10);
        }
        {
            auto& specialCellNode = XmlHelper::addNode(speedTrackNode, SpecialCellSerializer::nodeSpecialCell);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 5);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 15);
        }
        {
            auto& specialCellNode = XmlHelper::addNode(speedTrackNode, SpecialCellSerializer::nodeSpecialCell);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 6);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 255);
        }
        {
            auto& specialCellNode = XmlHelper::addNode(speedTrackNode, SpecialCellSerializer::nodeSpecialCell);        // Out of bounds! Ignored.
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 50);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 255);
        }
    }
    // Event Cells (empty).
    {
        XmlHelper::addNode(rootNode, TrackSerializer::nodeEventTrack);
    }

    // When.
    const auto result = TrackSerializer::deserialize(rootNode);

    // Then.
    REQUIRE(result.isValid());
    REQUIRE(result.height == 8);
    REQUIRE(result.captureFlags.size() == 3);
    {
        const auto& captureFlag = result.captureFlags.at(0);
        REQUIRE_FALSE(captureFlag.isNoteCaptured());
        REQUIRE(captureFlag.isInstrumentCaptured());
        REQUIRE(captureFlag.isEffect1Captured());
        REQUIRE(captureFlag.isEffect2Captured());
        REQUIRE(captureFlag.isEffect3Captured());
        REQUIRE(captureFlag.isEffect4Captured());
    }
    {
        const auto& captureFlag = result.captureFlags.at(1);
        REQUIRE(captureFlag.isNoteCaptured());
        REQUIRE(captureFlag.isInstrumentCaptured());
        REQUIRE(captureFlag.isEffect1Captured());
        REQUIRE(captureFlag.isEffect2Captured());
        REQUIRE(captureFlag.isEffect3Captured());
        REQUIRE(captureFlag.isEffect4Captured());
    }
    {
        const auto& captureFlag = result.captureFlags.at(2);
        REQUIRE(captureFlag.isNoteCaptured());
        REQUIRE_FALSE(captureFlag.isInstrumentCaptured());
        REQUIRE_FALSE(captureFlag.isEffect1Captured());
        REQUIRE(captureFlag.isEffect2Captured());
        REQUIRE(captureFlag.isEffect3Captured());
        REQUIRE(captureFlag.isEffect4Captured());
    }
    REQUIRE(result.tracksToCells.size() == 3);
    {
        const auto& cells = result.tracksToCells.at(0);
        size_t cellIndex = 0;
        REQUIRE(cells.at(cellIndex++) == Cell(Note::buildNote(40), 1));
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell(Note::buildNote(41), 10));
        REQUIRE(cells.size() == cellIndex);
    }
    {
        const auto& cells = result.tracksToCells.at(1);
        size_t cellIndex = 0;
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.size() == cellIndex);
    }
    {
        const auto& cells = result.tracksToCells.at(2);
        size_t cellIndex = 0;
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell(Note::buildNote(80), 0));
        REQUIRE(cells.at(cellIndex++) == Cell(Note::buildNote(81), 255));
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.at(cellIndex++) == Cell());
        REQUIRE(cells.size() == cellIndex);
    }

    // Speed Cells.
    {
        auto cells = result.speedCells;
        size_t index = 0;
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildSpecialCell(10));
        REQUIRE(cells.at(index++) == SpecialCell::buildSpecialCell(15));
        REQUIRE(cells.at(index++) == SpecialCell::buildSpecialCell(255));
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.size() == index);
    }

    // Event Cells.
    {
        auto cells = result.eventCells;
        size_t index = 0;
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.size() == index);
    }
}

TEST_CASE("Deserialization, event track only", "[TrackSerializerTest]")
{
    // Given.
    juce::XmlElement rootNode(TrackSerializer::nodeRoot);
    XmlHelper::addValueNode(rootNode, TrackSerializer::nodeHeight, 4);

    // Event Cells.
    {
        auto& eventTrackNode = XmlHelper::addNode(rootNode, TrackSerializer::nodeEventTrack);
        {
            auto& specialCellNode = XmlHelper::addNode(eventTrackNode, SpecialCellSerializer::nodeSpecialCell);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 0);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 1);
        }
        {
            auto& specialCellNode = XmlHelper::addNode(eventTrackNode, SpecialCellSerializer::nodeSpecialCell);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 1);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 50);
        }
        {
            auto& specialCellNode = XmlHelper::addNode(eventTrackNode, SpecialCellSerializer::nodeSpecialCell);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 3);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 100);
        }
        {
            auto& specialCellNode = XmlHelper::addNode(eventTrackNode, SpecialCellSerializer::nodeSpecialCell);            // Out of bounds, ignored.
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeIndex, 4);
            XmlHelper::addValueNode(specialCellNode, SpecialCellSerializer::nodeValue, 100);
        }
    }

    // When.
    const auto result = TrackSerializer::deserialize(rootNode);

    // Then.
    REQUIRE(result.isValid());
    REQUIRE(result.height == 4);
    REQUIRE(result.captureFlags.empty());
    REQUIRE(result.tracksToCells.empty());
    REQUIRE(result.speedCells.empty());

    // Event Cells.
    {
        auto cells = result.eventCells;
        size_t index = 0;
        REQUIRE(cells.at(index++) == SpecialCell::buildSpecialCell(1));
        REQUIRE(cells.at(index++) == SpecialCell::buildSpecialCell(50));
        REQUIRE(cells.at(index++) == SpecialCell::buildEmptySpecialCell());
        REQUIRE(cells.at(index++) == SpecialCell::buildSpecialCell(100));
        REQUIRE(cells.size() == index);
    }
}

}   // namespace arkostracker
