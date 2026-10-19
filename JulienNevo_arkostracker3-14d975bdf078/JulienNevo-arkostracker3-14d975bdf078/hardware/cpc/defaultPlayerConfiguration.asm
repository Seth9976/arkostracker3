; Configuration that can be included to Arkos Tracker 2 players.
; It indicates what parts of code are useful to the song/sound effects, to save both memory and CPU.
; The players may or may not take advantage of these flags, it is up to it.

; You can either:
; - Include this to the source that also includes the player (BEFORE the player is included) (recommended solution).
; - Include this at the beginning of the player code.
; - Copy/paste this directly in the player.
; If you use one player but several songs, don't worry, these declarations will stack up.
; If no configuration is used, the player will use default values (full code used).

	PLY_CFG_ConfigurationIsPresent = 1
	PLY_CFG_UseSpeedTracks = 1
	PLY_CFG_UseEventTracks = 1
	PLY_CFG_UseTranspositions = 1
	PLY_CFG_UseHardwareSounds = 1
	PLY_CFG_UseEffects = 1
	PLY_CFG_UseRetrig = 1
	PLY_CFG_UseInstrumentRetrig = 1
	PLY_CFG_UseInstrumentLoopTo = 1
	PLY_CFG_NoSoftNoHard = 1
	PLY_CFG_NoSoftNoHard_Noise = 1
	PLY_CFG_SoftOnly = 1
	PLY_CFG_SoftOnly_Noise = 1
	PLY_CFG_SoftOnly_ForcedSoftwarePeriod = 1
	PLY_CFG_SoftOnly_SoftwareArpeggio = 1
	PLY_CFG_SoftOnly_SoftwarePitch = 1
	PLY_CFG_SoftToHard = 1
	PLY_CFG_SoftToHard_Noise = 1
	PLY_CFG_SoftToHard_ForcedSoftwarePeriod = 1
	PLY_CFG_SoftToHard_SoftwareArpeggio = 1
	PLY_CFG_SoftToHard_SoftwarePitch = 1
	PLY_CFG_SoftToHard_HardwarePitch = 1
	PLY_CFG_SoftToHard_Retrig = 1
	PLY_CFG_HardOnly = 1
	PLY_CFG_HardOnly_Noise = 1
	PLY_CFG_HardOnly_ForcedHardwarePeriod = 1
	PLY_CFG_HardOnly_HardwareArpeggio = 1
	PLY_CFG_HardOnly_HardwarePitch = 1
	PLY_CFG_HardOnly_Retrig = 1
	PLY_CFG_HardToSoft = 1
	PLY_CFG_HardToSoft_Noise = 1
	PLY_CFG_HardToSoft_ForcedHardwarePeriod = 1
	PLY_CFG_HardToSoft_HardwareArpeggio = 1
	PLY_CFG_HardToSoft_HardwarePitch = 1
	PLY_CFG_HardToSoft_SoftwarePitch = 1
	PLY_CFG_HardToSoft_Retrig = 1
	PLY_CFG_SoftAndHard = 1
	PLY_CFG_SoftAndHard_Noise = 1
	PLY_CFG_SoftAndHard_ForcedSoftwarePeriod = 1
	PLY_CFG_SoftAndHard_SoftwareArpeggio = 1
	PLY_CFG_SoftAndHard_SoftwarePitch = 1
	PLY_CFG_SoftAndHard_ForcedHardwarePeriod = 1
	PLY_CFG_SoftAndHard_HardwareArpeggio = 1
	PLY_CFG_SoftAndHard_HardwarePitch = 1
	PLY_CFG_SoftAndHard_Retrig = 1
	PLY_CFG_SFX_LoopTo = 1
	PLY_CFG_SFX_NoSoftNoHard = 1
	PLY_CFG_SFX_NoSoftNoHard_Noise = 1
	PLY_CFG_SFX_SoftOnly = 1
	PLY_CFG_SFX_SoftOnly_Noise = 1
	PLY_CFG_SFX_HardOnly = 1
	PLY_CFG_SFX_HardOnly_Noise = 1
	PLY_CFG_SFX_HardOnly_Retrig = 1
	PLY_CFG_SFX_SoftAndHard = 1
	PLY_CFG_SFX_SoftAndHard_Noise = 1
	PLY_CFG_SFX_SoftAndHard_Retrig = 1
	PLY_CFG_UseEffect_Legato = 1
	PLY_CFG_UseEffect_Reset = 1
	PLY_CFG_UseEffect_ForcePitchTableSpeed = 1
	PLY_CFG_UseEffect_ForceArpeggioSpeed = 1
	PLY_CFG_UseEffect_ForceInstrumentSpeed = 1
	PLY_CFG_UseEffect_PitchGlide = 1
	PLY_CFG_UseEffect_PitchUp = 1
	PLY_CFG_UseEffect_PitchDown = 1
	PLY_CFG_UseEffect_PitchTable = 1
	PLY_CFG_UseEffect_Arpeggio3Notes = 1
	PLY_CFG_UseEffect_Arpeggio4Notes = 1
	PLY_CFG_UseEffect_ArpeggioTable = 1
	PLY_CFG_UseEffect_SetVolume = 1
	PLY_CFG_UseEffect_VolumeIn = 1
	PLY_CFG_UseEffect_VolumeOut = 1
