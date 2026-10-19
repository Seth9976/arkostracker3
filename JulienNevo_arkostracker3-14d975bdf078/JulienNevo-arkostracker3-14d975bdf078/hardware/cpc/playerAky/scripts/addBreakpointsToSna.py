

# Adds a Breakpoint chunk to the given SNA. It does not test if the chunk
# already exists!
def addToSna(pathToSnapshot, pathToSymbols, prefixToFind):
    addresses = []

    # Opens the input symbol file, finds all the Breakpoints labels. Also search for local labels "Mylabel.BRK" for example.
    with open(pathToSymbols) as file:
        for line in file:
            line = line.rstrip()
            if (line.startswith(prefixToFind) or ("." + prefixToFind in line)):
                addressString = line.split(" ")[1]
                address = int(addressString[1:], 16)
                addresses.append(address)

    if not addresses:
        return

    # Opens the snapshot in binary, appends the BRKS chunk.
    with open(pathToSnapshot, "ab") as file:
        file.write('BRKS'.encode('ascii'))
        chunkSize = len(addresses) * 5
        file.write(bytes([chunkSize & 255, (chunkSize >> 8) & 255 , (chunkSize >> 16) & 255, (chunkSize >> 24) & 255]))       # Filler.
        for address in addresses:
            file.write(bytes([address & 255, (address >> 8) & 255]))    # Address (little-endian).
            file.write(bytes([0]))          # Bank.
            file.write(bytes([0, 0]))       # Condition.

    print("Encoded", len(addresses), "breakpoints to snapshot.")
