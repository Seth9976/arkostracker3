rasm ../PlayerAkgTester_SPECTRUM.asm
IF NOT errorlevel 0 EXIT

rem 33153 = 0x8181
rem 33155 = 0x8183
makesna output.sna 33155 rasmoutput.bin 33153
IF NOT errorlevel 0 EXIT