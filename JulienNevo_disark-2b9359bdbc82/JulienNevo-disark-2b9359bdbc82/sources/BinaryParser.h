#pragma once

#include <utility>

#include <juce_core/juce_core.h>

#include "base/Opcodes.h"
#include "base/Instruction.h"

namespace disark
{

class ExportConfiguration;

/**
 * This class parses the given bytes and build Instructions.
 * This is typically called once for every Region.
 */
class BinaryParser
{
public:
    friend class BinaryParserTest;                      // For test units.

    /** Class for objects that can provides bytes for disassembling. */
    class BytesProvider
    {
    public:
        /** Destructor. */
        virtual ~BytesProvider() = default;

        /**
         * Asks for an unsigned byte (0-255), -1 if none could be (end of file, end of region, etc.).
         * @return an unsigned byte.
         */
        virtual int fetchByte() = 0;

        /** @return true if there are still more byte to send. */
        virtual bool hasNext() = 0;
    };

    /**
     * Constructor.
     * @param exportConfiguration the configuration for the source export.
     * @param bytesProvider the provider of bytes to read.
     */
    explicit BinaryParser(const ExportConfiguration& exportConfiguration, BytesProvider& bytesProvider) noexcept;

    /**
     * Reads the bytes as long as possible and builds Instructions. At the end, there might be opcode/parameter bytes left if they couldn't be read fully.
     * @return the Instructions, plus some bytes that couldn't be fully read.
     */
    std::pair<std::vector<Instruction>, std::vector<int>> buildAllInstructions() noexcept;

    /**
     * Reads the bytes as long as possible. This can be called only for a byte only Region, but not for a code region.
     * @return the bytes.
     */
    std::vector<int> buildByteRegion() noexcept;

    /**
     * Reads the words (16 bits) as long as possible.
     * @return the words, and a possible left-over (-1 if not present).
     */
    std::pair<std::vector<int>, int> buildWordRegion() noexcept;

private:
    class ReadResult
    {
    public:
        /** @return an object in case of success. */
        static ReadResult buildSuccess()
        {
            return { true, {} };
        }
        /** @return an object in case of error. */
        static ReadResult buildError(std::vector<int> readBytes)
        {
            return { false, std::move(readBytes)};
        }

        bool isSuccess() const
        {
            return success;
        }

        const std::vector<int>& getReadBytesIfError() const
        {
            return readBytesIfError;
        }

    private:
        /**
         * Constructor.
         * @param pSuccess true if success.
         * @param pReadBytesIfError the bytes that were read, in case of error.
         */
        ReadResult(const bool pSuccess, std::vector<int> pReadBytesIfError) noexcept:
            success(pSuccess),
            readBytesIfError(std::move(pReadBytesIfError))
        {
        }
        const bool success;
        const std::vector<int> readBytesIfError;
    };

    /**
     * Reads an opcode from the BytesProvider. Important note: 3-byte opcodes read 4 bytes, the always-present signed index is on the third position (op-op-d-op).
     * @return the opcode and a result. The opcode is irrelevant if the result is a failure.
     */
    std::pair<Opcode, ReadResult> readOpcode() noexcept;

    /**
     * Reads an instruction, thanks to an already ready and valid opcode. This will read the possible parameters.
     * This may fail if we can't read any more bytes, or if the region stopped, etc.
     * In this case, all the bytes of the parameters are returned: if the first parameter was OK but not the second, both data are returned.
     * @param opcode the opcode. Must be valid, may contain parameters.
     * @return the instruction if it was a success or nullptr, plus the result, including the read bytes in case of failure.
     */
    std::pair<std::unique_ptr<Instruction>, ReadResult> readInstruction(const Opcode& opcode) noexcept;

    /**
     * Attempts to read bytes, according to the parameter type.
     * @param type the parameter type.
     * @param success set to true if everything went fine.
     * @return the bytes. If an error occurred, only the ones that could be retrieved are returned.
     */
    std::vector<int> readBytesFromParameterType(SourceParameterType type, bool& success) noexcept;

    /**
     * Builds a parameter from the given bytes. This is only concatenation if bytes!
     * @param bytes the bytes. May be 0, 1 or 2.
     * @return the parameter value. -1 if there are no bytes.
     */
    static int buildParameter(const std::vector<int>& bytes) noexcept;

    BytesProvider& bytesProvider;                                                   // The provider of bytes to read.
    Opcodes opcodes;                                                                // Holds all the opcodes.
};

}    // namespace disark
