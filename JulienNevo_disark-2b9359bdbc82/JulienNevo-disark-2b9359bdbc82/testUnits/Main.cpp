// This file is only useful to declare this once.
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(const int argc, char* argv[])      // NOLINT(*-avoid-c-arrays,clion-misra-cpp2008-3-1-3)
{
    return Catch::Session().run(argc, argv);
}