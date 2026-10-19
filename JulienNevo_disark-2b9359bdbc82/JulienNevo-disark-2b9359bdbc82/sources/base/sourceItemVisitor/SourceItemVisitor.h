#pragma once

#include <vector>

#include "../SourceItem.h"

namespace disark
{

class References;

/**
 * Abstract visitor on each Source items of a full instruction (which can be a single byte declaration, or a full opcode with parameters!). But it is valid.
 * Implementation can do anything: generates sources, or don't generate anything but gather labels, or anything else.
 */
class SourceItemVisitor
{
public:
    /**
     * Constructor.
     * @param pReferences keeps the Reference (labels, etc.).
     */
    explicit SourceItemVisitor(References& pReferences) noexcept :
        references(pReferences)
    {
    }

    /** Destructor. */
    virtual ~SourceItemVisitor() = default;

    /**
     * Visits the given instruction (via Source Items). The source items must come from one line of source only (ld hl,#1234) for example.
     * Its parameters may be replaced by references, but this should be up to the References object to decide.
     * @param address the address of this instruction.
     * @param instructionSize the size of the whole instruction, in bytes. Useful to know if some inter-labels must be encoded there. >0.
     * @param sourceItems the items the instruction is composed of.
     * @param parameter1Value the first parameter, or -1 if not present.
     * @param parameter2Value the second parameter, or -1 if not present.
     */
    virtual void visitInstruction(int address, int instructionSize, const std::vector<SourceItem>& sourceItems, int parameter1Value, int parameter2Value) const noexcept = 0;

    /** Called after the visit of all the instructions has been done. The default implementation does nothing. */
    virtual void executeAfterVisit() const noexcept
    {
    }

protected:
    References& references;                                                         // Keeps the Reference (labels, etc.).
};

}    // namespace disark
