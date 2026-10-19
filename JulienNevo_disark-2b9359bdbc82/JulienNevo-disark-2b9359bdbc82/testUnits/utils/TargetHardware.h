#pragma once

namespace disark
{

/** The target of the PSG hardware. */
enum class TargetHardware : int
{
    cpc = 0,
    spectrum = 1,
    pentagon = 2,
    msx = 3,
    sharpMz = 4,

    cpcPlayCity = 5,
    spectrumTurboSound = 6,
    spectrumNext = 7,
    msxFpgaPsg = 8,
    msxDarky = 9,

    none
};

}    // namespace disark
