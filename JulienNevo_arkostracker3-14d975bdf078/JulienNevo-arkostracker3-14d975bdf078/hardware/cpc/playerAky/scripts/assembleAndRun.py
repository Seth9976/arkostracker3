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
    "-s", "Z80_PC", "0xc000",
    "-s", "Z80_SP", "0x100",


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

# Checks emulator presence, opens it if not found.
try:
    pid = subprocess.check_output(["pidof", "cpcec-gtk"])
except subprocess.CalledProcessError as e:
    print("Opening emulator...")
    subprocess.call(["cpcec-gtk"])
    # Adds some timers, for reason unknown...
    time.sleep(1)
    # Blocking, waits for the window to appear.
    subprocess.call(["xdotool", "search", "--sync", "--all", "--onlyvisible", "--name", "cpcec"])
    # Opens the sna once and for all. It is monitored by CPCE, so a change will reset the emulator and loads the new SNA automatically!
    subprocess.call(["xdotool", "search", "--all", "--onlyvisible", "--name", "cpcec", "windowactivate"])
    subprocess.call(["xdotool", "key", "--clearmodifiers", "F1"])   # clearmodifiers is necessary, else this key doesn't work.
    # Ctrl+L to open the Open Location.
    subprocess.call(["xdotool", "key", "Ctrl+l"])
    time.sleep(0.5)
    subprocess.call(["xdotool", "type", projectFolder + generatedSnapshot])
    time.sleep(0.5)
    subprocess.call(["xdotool", "key", "Return"])

    print("Done opening the emulator!")
    exit(0)

# Emulator already launched, and with the snapshot already launched at least once.
# Makes it in foreground.
subprocess.call(["xdotool", "search", "--all", "--onlyvisible", "--name", "cpcec", "windowactivate"])

print("Done!")
