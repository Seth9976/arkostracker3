rem Creates the DSK on which to add the files. The base file has the BASIC program.
copy BASEBasicInterruptionsCpc_BasicPrg.dsk BasicInterruptions_CPC.dsk

rem Put the music files.
cpcfs BasicInterruptions_CPC.dsk p music.akg,0x7000 -b -e
IF %errorlevel% NEQ 0 EXIT
cpcfs BasicInterruptions_CPC.dsk p sfx.akx,0x9000 -b -e
IF %errorlevel% NEQ 0 EXIT

rem Assembles the interruption player.
rasm BasicInterruptions_CPC.asm -o player
IF %errorlevel% NEQ 0 EXIT

rem Puts it in the DSK
cpcfs BasicInterruptions_CPC.dsk p player.bin,0x9500,0x9500 -b -e