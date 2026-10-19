#pragma once

#include "SourceItemVisitor.h"

namespace disark
{

class ExportConfiguration;

/**
 * Visitor that will generate labels from the given instructions.
 */
class LabelGenerator final : public SourceItemVisitor
{
public:
    /**
     * Constructor.
     * @param references holds the references to labels.
     * @param configuration the source configuration to use.
     */
    LabelGenerator(References& references, const ExportConfiguration& configuration) noexcept;

    void visitInstruction(int address, int instructionSize, const std::vector<SourceItem>& sourceItems, int parameter1Value, int parameter2Value) const noexcept override;

private:
    const ExportConfiguration& configuration;                                     // The source configuration to use.
};

}    // namespace disark