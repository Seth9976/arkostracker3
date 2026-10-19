rem A simple batch to assemble all the testers, making sure they are still compiling.
rem No output files are generated.
rem WARNING! Don't forget to generate the players before (with the Python script in the Jenkins folder).
rem RASM MUST be on the Path!

rasm -no tester/PlayerAkyTester_CPC.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkyTester_MSX.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkyTester_PENTAGON.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkyTester_SPECTRUM.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkyTester6Channels_TurboSound_SPECTRUM.asm
IF NOT errorlevel 0 GOTO err
rasm -no tester/PlayerAkyTester9Channels_SPECNEXT.asm
IF NOT errorlevel 0 GOTO err


echo OK !
PAUSE
EXIT

:err
echo ****************************************** ERROR ******************************************
PAUSE
