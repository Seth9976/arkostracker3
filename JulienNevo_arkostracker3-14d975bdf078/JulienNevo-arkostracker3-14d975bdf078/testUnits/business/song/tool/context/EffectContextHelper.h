#pragma once

#include "../../../../../source/business/song/tool/context/EffectContextImpl.h"

namespace arkostracker
{

class SongController;

/** Helper class to reach the private methods of the Effect Context. We don't want the multi-threading management to get in our way! */
class EffectContextTest
{
public:
    explicit EffectContextTest(SongController& pSongController) :
            songController(pSongController),
            effectContext(pSongController, false)       // Don't observe!
    {
    }

    void buildContext()
    {
        const auto subsongId = songController.getCurrentSubsongId();
        effectContext.targetSubsongId = subsongId;

        auto result = effectContext.buildContext();
        effectContext.positionsContext_protectedByMutex = std::move(result);
    }

    LineContext determineContext(const CellLocationInPosition& location)
    {
        // Makes sure we use.
        constexpr juce::int64 now = 0;
        effectContext.modificationTimestamp = now + EffectContextImpl::timeDifferenceMsToConsiderModification + 1;

        return effectContext.determineContext(location, now);
    }

    Id getPitchId(const int pitchIndex) const
    {
        return songController.getExpressionHandler(false).getId(pitchIndex).getValue();
    }

    Id getArpeggioId(const int arpeggioIndex) const
    {
        return songController.getExpressionHandler(true).getId(arpeggioIndex).getValue();
    }

private:
    SongController& songController;
    EffectContextImpl effectContext;
};

}   // namespace arkostracker
