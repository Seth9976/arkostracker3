#pragma once

#include <juce_core/juce_core.h>

#include "../../../controllers/SongController.h"
#include "../../../utils/task/Task.h"

namespace arkostracker
{

class SongController;

/** Task to save a sample into WAV. */
class SaveSampleTask : public Task<std::unique_ptr<bool>>
{
public:
    /**
         * Constructor.
         * @param songController the Song Controller.
         * @param instrumentId the instrument ID. Should be a sample!
         * @param fileToSave the file (WAV, etc.).
         */
    explicit SaveSampleTask(SongController& songController, Id instrumentId, juce::String fileToSave) noexcept;

    // Task method implementations.
    // ===================================================
    std::pair<bool, std::unique_ptr<bool>> performTask() noexcept override;

private:
    SongController& songController;
    Id instrumentId;
    juce::String fileToSave;

};

}   // namespace arkostracker
