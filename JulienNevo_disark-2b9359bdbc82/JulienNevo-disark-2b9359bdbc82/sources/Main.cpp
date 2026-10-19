#include "Tool.h"

/**
 * Command line for Disark (Z80 disassembler).
 * @param argc how many arguments.
 * @param argv the arguments.
 * @return 0 if everything went fine.
 */
int main (const int argc, char* argv[])      // NOLINT(*-avoid-c-arrays,clion-misra-cpp2008-3-1-3)
{
    return disark::Tool::execute(argc, argv);
}