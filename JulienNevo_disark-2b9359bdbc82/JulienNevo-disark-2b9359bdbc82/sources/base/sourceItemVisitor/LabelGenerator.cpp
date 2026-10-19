#include "LabelGenerator.h"

#include "../../utils/NumberUtil.h"
#include "../ExportConfiguration.h"
#include "../References.h"
#include "../Symbol.h"

namespace disark
{

LabelGenerator::LabelGenerator(References& pReferences, const ExportConfiguration& pConfiguration) noexcept :
    SourceItemVisitor(pReferences),
    configuration(pConfiguration)
{
}

void LabelGenerator::visitInstruction(int address, int /*instructionSize*/, const std::vector<SourceItem>& /*sourceItems*/, int /*parameter1Value*/,
        int /*parameter2Value*/) const noexcept
{
    // Generates a label here.
    jassert((address >= 0) && (address <= 0xffff));

    auto label = configuration.getGeneratedBaseLabel() + NumberUtil::toHexFourDigits(address);
    references.storeSymbol({ label, address, true });
}

}    // namespace disark