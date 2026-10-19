#include "SongTestHelper.h"

#include "../../source/import/loader/SongLoader.h"
#include "../../source/utils/ZipHelper.h"

namespace arkostracker 
{

std::unique_ptr<Song> SongTestHelper::createSong() noexcept
{
    return std::make_unique<Song>("testSong", "testAuthor", "testComposer", "testComments");
}

const Subsong& SongTestHelper::addSubsong(Song& song, const int psgCount, const int initialSpeed, const int loopStartPosition,
                              const int endPosition, const std::vector<Position>& positions,
                              const std::vector<Pattern>& patterns, const std::vector<Track>& tracks,
                              const std::vector<SpecialTrack>& speedTracks, const std::vector<SpecialTrack>& eventTracks) noexcept
{
    auto subsong = createSubsong(psgCount, initialSpeed, loopStartPosition, endPosition, positions, patterns,
        tracks, speedTracks, eventTracks);
    const auto& subsongRef = *subsong;

    song.addSubsong(std::move(subsong));

    // ReSharper disable once CppDFALocalValueEscapesFunction
    return subsongRef;  // No point in this warning in the context.
}

std::unique_ptr<Subsong> SongTestHelper::createSubsong(const int psgCount, int initialSpeed, const int loopStartPosition, const int endPosition,
    const std::vector<Position>& positions, const std::vector<Pattern>& patterns, const std::vector<Track>& tracks, const std::vector<SpecialTrack>& speedTracks,
    const std::vector<SpecialTrack>& eventTracks) noexcept
{
    // Adds the PSGs (CPC).
    auto psgs = std::vector<Psg>();
    for (auto psgIndex = 0; psgIndex < psgCount; ++psgIndex) {
        psgs.emplace_back(Psg::buildForCpc());
    }

    auto subsong = std::make_unique<Subsong>("testSubsong", initialSpeed, 50.0F, 1, 4, 4, 0, 0, psgs, SidPlayerCapability::buildForCpc(), false);

    // This DOES change the loop, so it is set after.
    for (const auto& position : positions) {
        subsong->addPosition(position);
    }
    subsong->setLoopAndEndStartPosition(loopStartPosition, endPosition);

    for (const auto& pattern : patterns) {
        subsong->addPattern(pattern);
    }
    for (const auto& track : tracks) {
        subsong->addTrack(track);
    }
    for (const auto& specialTrack : speedTracks) {
        subsong->addSpecialTrack(true, specialTrack);
    }
    for (const auto& specialTrack : eventTracks) {
        subsong->addSpecialTrack(false, specialTrack);
    }

    return subsong;
}

bool SongTestHelper::areSongMusicallyEqual(const Song& firstSong, const Song& secondSong) noexcept
{
    // Compares the Instruments.
    const auto instrumentCount = firstSong.instruments.size();
    if (instrumentCount != secondSong.instruments.size()) {
        jassertfalse;
        return false;
    }
    for (size_t instrumentIndex = 0U; instrumentIndex < instrumentCount; ++instrumentIndex) {
        if (!firstSong.instruments.at(instrumentIndex)->isMusicallyEqualTo(*secondSong.instruments.at(instrumentIndex))) {
            jassertfalse;
            return false;
        }
    }

    // Subsongs.
    const auto subsongCount = firstSong.subsongs.size();
    if (subsongCount != secondSong.subsongs.size()) {
        jassertfalse;
        return false;
    }
    for (size_t subsongIndex = 0U; subsongIndex < subsongCount; ++subsongIndex) {
        if (!firstSong.subsongs.at(subsongIndex)->isMusicallyEqual(*secondSong.subsongs.at(subsongIndex))) {
            jassertfalse;
            return false;
        }
    }

    // Compares the Expressions.
    {
        const auto arpeggioCount = firstSong.arpeggios.expressions.size();
        if (arpeggioCount != secondSong.arpeggios.expressions.size()) {
            jassertfalse;
            return false;
        }
        for (size_t arpeggioIndex = 0U; arpeggioIndex < arpeggioCount; ++arpeggioIndex) {
            if (!firstSong.arpeggios.expressions.at(arpeggioIndex)->isMusicallyEqualTo(*secondSong.arpeggios.expressions.at(arpeggioIndex))) {
                jassertfalse;
                return false;
            }
        }
    }

    {
        const auto pitchCount = firstSong.pitches.expressions.size();
        if (pitchCount != secondSong.pitches.expressions.size()) {
            jassertfalse;
            return false;
        }
        for (size_t pitchIndex = 0U; pitchIndex < pitchCount; ++pitchIndex) {
            if (!firstSong.pitches.expressions.at(pitchIndex)->isMusicallyEqualTo(*secondSong.pitches.expressions.at(pitchIndex))) {
                jassertfalse;
                return false;
            }
        }
    }

    return true;
}

std::shared_ptr<Song> SongTestHelper::loadSong(const char* inputSongData, const size_t inputSongSize) noexcept
{
    juce::MemoryInputStream zippedMemoryInputStream(inputSongData, inputSongSize, false);
    const auto zippedInputStream = ZipHelper::unzip(zippedMemoryInputStream);
    auto& inputStream = (zippedInputStream != nullptr) ? *zippedInputStream : zippedMemoryInputStream;

    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    auto songUniquePtr = std::move(loadResult->song);
    auto song = std::shared_ptr(std::move(songUniquePtr));

    return song;
}

}   // namespace arkostracker
