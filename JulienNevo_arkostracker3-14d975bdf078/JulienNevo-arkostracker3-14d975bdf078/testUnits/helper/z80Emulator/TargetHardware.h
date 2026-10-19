#pragma once

#include <juce_core/juce_core.h>

#include "PlayerType.h"

namespace arkostracker
{

/** The target of the PSG hardware. */
enum class TargetHardware : unsigned char
{
    cpc,
    spectrum,
    pentagon,
    msx,

    pcw,
    svi,

    sharpMz,

    cpcPlayCity,
    pcwTurboSound,
    spectrumTurboSound,
    spectrumNext,
    msxFpgaPsg,
    msxDarky
};

class TargetHardwareHelper
{
public:
    /**
     * @return the "conventional" targets.
     * To avoid too long tests, and since the OUT code is the same, SVI and PCW are not returned. Force the hardware to use them.
     * @param playerType the player type used. Some players can't handle all the platforms.
     */
    static std::vector<TargetHardware> getNormal(const PlayerType playerType)
    {
        if (playerType == PlayerType::akyStabilized) {      // Only available on CPC.
            return { TargetHardware::cpc };
        }
        if (playerType == PlayerType::akyMultiPsg9Channels) {
            jassertfalse;       // Must not be called. The target hardware must be forced.
            return { TargetHardware::cpcPlayCity };
        }

        return { TargetHardware::cpc, TargetHardware::spectrum, TargetHardware::pentagon, TargetHardware::msx };
    }

    static juce::String getDisplayableName(const TargetHardware targetHardware)
    {
        switch (targetHardware) {
            case TargetHardware::cpcPlayCity:
                return "CPC-PlayCity";
            case TargetHardware::pcwTurboSound:
                return "PCW-TurboSound";
            case TargetHardware::spectrumTurboSound:
                return "Spectrum-TurboSound";
            case TargetHardware::spectrumNext:
                return "SpecNext";
            case TargetHardware::msxFpgaPsg:
                return "MSX-Fpga";
            case TargetHardware::msxDarky:
                return "MSX-Darky";
            case TargetHardware::cpc:
                return "CPC";
            case TargetHardware::spectrum:
                return "Spectrum";
            case TargetHardware::pentagon:
                return "Pentagon";
            case TargetHardware::msx:
                return "MSX";
            case TargetHardware::sharpMz:
                return "SharpMz";
            case TargetHardware::pcw:
                return "PCW";
            case TargetHardware::svi:
                return "SVI";
            default:
                jassertfalse;       // Unknown hardware!
                return "???";
        }
    }

    /** Indicates whether the given hardware is "special", that is, is not built in to a machine (like PlayCity, Turbosound, etc.), or is SpecNext. */
    static bool isSpecialHardware(const TargetHardware targetHardware)
    {
        switch (targetHardware) {
            case TargetHardware::cpcPlayCity:
            case TargetHardware::pcwTurboSound:
            case TargetHardware::spectrumTurboSound:
            case TargetHardware::spectrumNext:
            case TargetHardware::msxFpgaPsg:
            case TargetHardware::msxDarky:
                return true;
            default:
                jassertfalse;       // Unknown hardware!
            case TargetHardware::cpc:
            case TargetHardware::spectrum:
            case TargetHardware::pentagon:
            case TargetHardware::msx:
            case TargetHardware::sharpMz:
            case TargetHardware::pcw:
            case TargetHardware::svi:
                return false;
        }
    }
};

}   // namespace arkostracker
