import subprocess
import sys
import time
import pathlib
from addBreakpointsToSna import addToSna
from assemble import assembleSources

# To run this command, check the ~/.atom/global-shell-commands.cson scripts to add new shortcuts.

# Assembles.
# -----------------------------------

result = assembleSources()

if result.returncode != 0:
    print("Assembling FAILED! Error code: ", result.returncode)
    exit(result.returncode)


# Creates snapshot.
# -----------------------------------

generatedSnapshot = "generated/output.sna"
projectFolder = str(pathlib.Path().resolve()) + "/"

result = subprocess.run([
    "createSnapshot",
    generatedSnapshot,

    "-s", "GA_PAL:0", "0x44",
    "-s", "GA_PAL:1", "0x4b",
    "-s", "GA_PAL:16", "0x54", #"0x54",
    "-s", "CRTC_TYPE", "0",
    "-s", "Z80_PC", "0x100",
    "-s", "Z80_SP", "0xc000",

    "-l", "generated/main.bin", "0x100",


    ])

if result.returncode != 0:
    print("Create snapshot FAILED! Error code: ", result.returncode)
    exit(result.returncode)


# Adds breakpoints to the snapshot.
# -----------------------------------

addToSna(pathToSnapshot = generatedSnapshot, pathToSymbols = "generated/symbols.txt", prefixToFind = "AAA")


# Opens the emulator.
# -----------------------------------

print("Transfering to M4Board...")

# Copies the SNA to the root of the SD Card.
cpcIp = "192.168.43.17"
subprocess.call(["scripts/pyxfer.py", "-u", cpcIp, "generated/output.sna", "/"])
subprocess.call(["scripts/pyxfer.py", "-x", cpcIp, "generated/output.sna"])

print("Done!")
