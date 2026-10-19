rem A simple batch to assemble all the testers, making sure they are still compiling.
rem No output files are generated.
rem WARNING! Don't forget to generate the players before (with the Python script in the Jenkins folder).
rem RASM MUST be on the Path!

rasm -no tester/PlayerAkgTester_CPC.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkgTester_MSX.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkgTester_PENTAGON.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkgTester_SPECTRUM.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkgWithSoundEffectTester_CPC.asm
IF NOT errorlevel 0 GOTO err


echo OK !
PAUSE
EXIT

:err
echo ****************************************** ERROR ******************************************
PAUSE
