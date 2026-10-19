#pragma once

namespace disark
{

class ExportConfiguration;
class Parameter;

class Tool
{
public:
    static int execute(int argc, char* argv[]);     // NOLINT(*-avoid-c-arrays,clion-misra-cpp2008-3-1-3)

private:
    static bool manageSourceProfile(const Parameter& sourceProfileParameter, ExportConfiguration& exportConfiguration);
};

}    // namespace disark
