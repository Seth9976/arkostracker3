#include "../catch.hpp"

#include "../../source/utils/CircularBuffer.h"

namespace arkostracker 
{

/** Tests the CircularBuffer class. */

TEST_CASE("putAndGetNoCycling", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;

    // When.
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);

    // Then.
    REQUIRE(buffer.readData(0) == 1);
    REQUIRE(buffer.readData(1) == 2);
    REQUIRE(buffer.readData(2) == 3);
    REQUIRE(buffer.readData(3) == 4);
    REQUIRE(buffer.readData(4) == 5);
    REQUIRE(buffer.readData(5) == 6);
    REQUIRE(buffer.readData(6) == 7);
    REQUIRE(buffer.readData(7) == 8);
}


TEST_CASE("putAndGetCycling", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;

    // When.
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    buffer.addData(9);
    buffer.addData(10);
    buffer.addData(11);

    // Then.
    REQUIRE(buffer.readData(0) == 9);
    REQUIRE(buffer.readData(1) == 10);
    REQUIRE(buffer.readData(2) == 11);
    REQUIRE(buffer.readData(3) == 4);
    REQUIRE(buffer.readData(4) == 5);
    REQUIRE(buffer.readData(5) == 6);
    REQUIRE(buffer.readData(6) == 7);
    REQUIRE(buffer.readData(7) == 8);
}

TEST_CASE("getOffsetInBuffer", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;

    // When/then.
    REQUIRE(buffer.getOffsetInBuffer() == 0);
    buffer.addData(1);
    REQUIRE(buffer.getOffsetInBuffer() == 1);
    buffer.addData(2);
    REQUIRE(buffer.getOffsetInBuffer() == 2);
    buffer.addData(3);
    REQUIRE(buffer.getOffsetInBuffer() == 3);
    buffer.addData(4);
    REQUIRE(buffer.getOffsetInBuffer() == 4);
    buffer.addData(5);
    REQUIRE(buffer.getOffsetInBuffer() == 5);
    buffer.addData(6);
    REQUIRE(buffer.getOffsetInBuffer() == 6);
    buffer.addData(7);
    REQUIRE(buffer.getOffsetInBuffer() == 7);
    buffer.addData(8);
    REQUIRE(buffer.getOffsetInBuffer() == 0);
    buffer.addData(9);
    REQUIRE(buffer.getOffsetInBuffer() == 1);
    buffer.addData(10);
    REQUIRE(buffer.getOffsetInBuffer() == 2);
    buffer.addData(11);
    REQUIRE(buffer.getOffsetInBuffer() == 3);
}

TEST_CASE("fillFromNoCycling", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    juce::HeapBlock<unsigned short> bufferToFill(8, true);

    // When.
    buffer.fillFrom(0, bufferToFill.getData(), 8);

    // Then.
    REQUIRE(bufferToFill[0] == 1);
    REQUIRE(bufferToFill[1] == 2);
    REQUIRE(bufferToFill[2] == 3);
    REQUIRE(bufferToFill[3] == 4);
    REQUIRE(bufferToFill[4] == 5);
    REQUIRE(bufferToFill[5] == 6);
    REQUIRE(bufferToFill[6] == 7);
    REQUIRE(bufferToFill[7] == 8);
}

TEST_CASE("fillFromNoCyclingPartialToEnd", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    juce::HeapBlock<unsigned short> bufferToFill(4, true);

    // When.
    buffer.fillFrom(4, bufferToFill.getData(), 4);

    // Then.
    REQUIRE(bufferToFill[0] == 5);
    REQUIRE(bufferToFill[1] == 6);
    REQUIRE(bufferToFill[2] == 7);
    REQUIRE(bufferToFill[3] == 8);
}

TEST_CASE("fillFromNoCyclingPartialMiddle", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    juce::HeapBlock<unsigned short> bufferToFill(8, true);

    // When.
    buffer.fillFrom(2, bufferToFill.getData(), 4);

    // Then.
    REQUIRE(bufferToFill[0] == 3);
    REQUIRE(bufferToFill[1] == 4);
    REQUIRE(bufferToFill[2] == 5);
    REQUIRE(bufferToFill[3] == 6);
    REQUIRE(bufferToFill[4] == 0);
    REQUIRE(bufferToFill[5] == 0);
    REQUIRE(bufferToFill[6] == 0);
    REQUIRE(bufferToFill[7] == 0);
}

TEST_CASE("fillFromCycling", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    juce::HeapBlock<unsigned short> bufferToFill(8, true);

    // When.
    buffer.fillFrom(4, bufferToFill.getData(), 8);

    // Then.
    REQUIRE(bufferToFill[0] == 5);
    REQUIRE(bufferToFill[1] == 6);
    REQUIRE(bufferToFill[2] == 7);
    REQUIRE(bufferToFill[3] == 8);
    REQUIRE(bufferToFill[4] == 1);
    REQUIRE(bufferToFill[5] == 2);
    REQUIRE(bufferToFill[6] == 3);
    REQUIRE(bufferToFill[7] == 4);
}

TEST_CASE("fillFromCyclingPartial", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    juce::HeapBlock<unsigned short> bufferToFill(6, true);

    // When.
    buffer.fillFrom(6, bufferToFill.getData(), 4);

    // Then.
    REQUIRE(bufferToFill[0] == 7);
    REQUIRE(bufferToFill[1] == 8);
    REQUIRE(bufferToFill[2] == 1);
    REQUIRE(bufferToFill[3] == 2);
    REQUIRE(bufferToFill[4] == 0);
    REQUIRE(bufferToFill[5] == 0);
}

TEST_CASE("fillFromCyclingTooMuch", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    juce::HeapBlock<unsigned short> bufferToFill(8, true);

    // When.
    buffer.fillFrom(6, bufferToFill.getData(), 20);

    // Then.
    REQUIRE(bufferToFill[0] == 7);
    REQUIRE(bufferToFill[1] == 8);
    REQUIRE(bufferToFill[2] == 1);
    REQUIRE(bufferToFill[3] == 2);
    REQUIRE(bufferToFill[4] == 3);
    REQUIRE(bufferToFill[5] == 4);
    REQUIRE(bufferToFill[6] == 5);
    REQUIRE(bufferToFill[7] == 6);
}

TEST_CASE("fillFromCyclingStartPositionOverflow", "[CircularBuffer]")
{
    // Given.
    CircularBuffer<unsigned short, 8> buffer;
    buffer.addData(1);
    buffer.addData(2);
    buffer.addData(3);
    buffer.addData(4);
    buffer.addData(5);
    buffer.addData(6);
    buffer.addData(7);
    buffer.addData(8);
    juce::HeapBlock<unsigned short> bufferToFill(8, true);

    // When.
    buffer.fillFrom(4 + 8 * 150, bufferToFill.getData(), 8);    // This raises an assertion.

    // Then.
    REQUIRE(bufferToFill[0] == 5);
    REQUIRE(bufferToFill[1] == 6);
    REQUIRE(bufferToFill[2] == 7);
    REQUIRE(bufferToFill[3] == 8);
    REQUIRE(bufferToFill[4] == 1);
    REQUIRE(bufferToFill[5] == 2);
    REQUIRE(bufferToFill[6] == 3);
    REQUIRE(bufferToFill[7] == 4);
}

}   // namespace arkostracker
