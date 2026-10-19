#include "SongControllerForTest.h"

namespace arkostracker
{

SongControllerForTest::SongControllerForTest(std::shared_ptr<Song> pSong) :
        song(std::move(pSong)),
        linkerObservers()
{
}

std::shared_ptr<Song> SongControllerForTest::getSong()
{
    return song;
}

std::shared_ptr<const Song> SongControllerForTest::getConstSong() const
{
    return song;
}

Observers<LinkerObserver>& SongControllerForTest::getLinkerObservers() noexcept
{
    return linkerObservers;
}

Id SongControllerForTest::getCurrentSubsongId() const noexcept
{
    return song->getFirstSubsongId();
}

void SongControllerForTest::performOnConstSubsong(const Id& subsongId, const std::function<void(const Subsong&)>& function) const noexcept
{
    song->performOnConstSubsong(subsongId, function);
}

void SongControllerForTest::performOnSubsong(const Id& subsongId, const std::function<void(Subsong&)>& function) const noexcept
{
    song->performOnSubsong(subsongId, function);
}

ExpressionHandler& SongControllerForTest::getExpressionHandler(const bool isArpeggio) noexcept
{
    return song->getExpressionHandler(isArpeggio);
}

int SongControllerForTest::getPsgCount(const Id& subsongId) const noexcept
{
    auto psgCount = 0;
    song->performOnConstSubsong(subsongId, [&] (const Subsong& subsong) noexcept {
        psgCount = subsong.getPsgCount();
    });

    return psgCount;
}

std::vector<Psg> SongControllerForTest::getPsgs(const Id& subsongId) const noexcept
{
    std::vector<Psg> psgs;
    song->performOnConstSubsong(subsongId, [&] (const Subsong& subsong) noexcept {
        psgs = subsong.getPsgs();
    });

    return psgs;
}
}   // namespace arkostracker
