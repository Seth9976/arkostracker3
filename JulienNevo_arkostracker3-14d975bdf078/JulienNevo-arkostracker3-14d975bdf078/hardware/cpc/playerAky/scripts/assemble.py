import subprocess
import sys
sys.path.append('sources')

# Assembles the sources.
def assembleSources():
    result = subprocess.run([
        "rasm",
        "-ob", "generated/main.bin",

        "-sw",
        "-sa",
        "-os", "generated/symbols.txt",

        "-twe",

        "-xr",
        "sources/main.asm"])

    return result





def main():
    assembleSources()

if __name__ == "__main__":
    main()
