#pragma once

#include "../../source/controllers/SongControllerNoOp.h"

namespace arkostracker
{

/** A SongController with only minimal method implementations. */
class SongControllerForTest final : public SongControllerNoOp
{
public:
    explicit SongControllerForTest(std::shared_ptr<Song> song);

    std::shared_ptr<Song> getSong() override;
    std::shared_ptr<const Song> getConstSong() const override;
    Observers<LinkerObserver>& getLinkerObservers() noexcept override;
    Id getCurrentSubsongId() const noexcept override;
    void performOnConstSubsong(const Id& subsongId, const std::function<void(const Subsong&)>& function) const noexcept override;
    void performOnSubsong(const Id& subsongId, const std::function<void(Subsong&)>& function) const noexcept override;
    ExpressionHandler& getExpressionHandler(bool isArpeggio) noexcept override;
    int getPsgCount(const Id& subsongId) const noexcept override;
    std::vector<Psg> getPsgs(const Id& subsongId) const noexcept override;

private:
    std::shared_ptr<Song> song;
    Observers<LinkerObserver> linkerObservers;
};

}   // namespace arkostracker
