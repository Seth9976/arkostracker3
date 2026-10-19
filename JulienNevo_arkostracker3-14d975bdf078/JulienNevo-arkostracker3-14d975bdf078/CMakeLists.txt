cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME ArkosTracker)
file(STRINGS "ProjectVersion.txt" PROJECT_VERSION)      # Defines the project version from the file, also used by the CI.
file(STRINGS "FapVersion.txt" FAP_VERSION)              # Useful for some display.

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

# Including CPM.cmake, a package manager:
# https://github.com/TheLartians/CPM.cmake
#include(cmakeScripts/CPM.cmake)

# Download CPM.cmake. https://github.com/cpm-cmake/CPM.cmake/wiki/Downloading-CPM.cmake-in-CMake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.8/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=78ba32abdf798bc616bab7c73aac32a17bbd7b06ad9e26a6add69de8f3ae4791
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# Uses C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set this *locally* to build only on arm64, in case compilation fails on Mac (because only one architecture is available).
if (NOT DEFINED ENV{USE_ONLY_ARM64})
    set(CMAKE_OSX_ARCHITECTURES "arm64 x86_64")     # To build on Mac M1, but also Intel.
endif()


if (DEFINED ENV{USE_INTERPROCEDURAL_OPTIMIZATION})
    message("Interprocedural optimization ON")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)   # Linking too slow if set! So only for the CI.
endif()

#set(CMAKE_CXX_FLAGS_RELEASE "-O0 -g")           # Useful to debug in Release!

# Gets JUCE from GIT, via CPM.
# Note that a forked JUCE is used in order to patch the JUCE 7.0.1.2 for XCode 16, as JUCE 7 has no LTS version
# (some useless methods to discard, not used).
CPMAddPackage(
        NAME JUCE
        GITHUB_REPOSITORY JulienNevo/JUCE_7_0_1_2_Xcode16
        GIT_TAG 7.0.12_patch
)

add_subdirectory(binaryResources)
add_subdirectory(source)
add_subdirectory(thirdParty/fap)
add_subdirectory(thirdParty/lzh)
add_subdirectory(thirdParty/rasm)
add_subdirectory(thirdParty/serial)
# Note: the Z80 emulator is not a project because has no .cpp, so is included directly as a directory in the TU project.
add_subdirectory(testUnits EXCLUDE_FROM_ALL)            # Prevents CPack to build the test units, useless. Yet allows building manually! --> Not from Windows it seems?!
add_subdirectory(testUnitResources EXCLUDE_FROM_ALL)

add_subdirectory(source/commandLineTools/baseCli)
add_subdirectory(source/commandLineTools/baseExport)
add_subdirectory(source/commandLineTools/songToAkg)
add_subdirectory(source/commandLineTools/songToAkm)
add_subdirectory(source/commandLineTools/songToAky)
add_subdirectory(source/commandLineTools/songToFap)
add_subdirectory(source/commandLineTools/songToEvents)
add_subdirectory(source/commandLineTools/songToRaw)
add_subdirectory(source/commandLineTools/songToRawLinear)
add_subdirectory(source/commandLineTools/songToYm)
add_subdirectory(source/commandLineTools/songToVgm)
add_subdirectory(source/commandLineTools/songToWav)
add_subdirectory(source/commandLineTools/songToSfx)
add_subdirectory(source/commandLineTools/songToSamples)
add_subdirectory(source/commandLineTools/z80Profiler)




# Defines "full warnings" and "no warnings" flag, used below according to the project.
if ((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))
    set(WARNING_FLAGS /W4)              # /Wall impractical, switched to /W4. /WX = warning as error, removed.
    #set(NO_WARNING_FLAGS /w)
elseif ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    # Same as for GCC below, but without -Wnoexcept and -Wstrict-null-sentinel
    # which are unknown.
    set(WARNING_FLAGS
            -Wall -Wextra -pedantic -pedantic-errors -Wunused-variable
            #-Werror                                        # I'd like to, but too many false positive.
            #-Wno-conditional-uninitialized                 # Too many false positive, but this flag seems ignored.
            -Wsign-conversion -Wcast-align
            -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2
            -Winit-self -Wmissing-include-dirs -Woverloaded-virtual
            -Wredundant-decls -Wshadow -Wstrict-overflow=5
            -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
            )
else()  # GNU (=GCC)
    # JUCE cannot compile with -Wundef -Wold-style-cast -Wcast-qual -Wlogical-op -Wconversion -Wnoexcept
    set(WARNING_FLAGS
            -Wall -Wextra -pedantic -pedantic-errors -Wunused-variable
            -Werror -Wsign-conversion -Wcast-align
            -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2
            -Winit-self -Wmissing-include-dirs -Woverloaded-virtual
            -Wredundant-decls -Wshadow -Wstrict-null-sentinel -Wstrict-overflow=5
            -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
            )

    # GCC will emit a warning about serial compilation of LTRANS jobs when
    # no explicit parameter is passed. It must be an integer, auto, or jobserver.
    set(CMAKE_EXE_LINKER_FLAGS
            "-flto=auto" CACHE STRING "Force enable Link-Time Optimization" FORCE
            )
endif()

# For our code (only!), make sure we get all the warnings.
target_compile_options(MainSoftware PRIVATE ${WARNING_FLAGS})
target_compile_options(TestUnits PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToAkg PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToAkm PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToAky PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToFap PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToEvents PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToRaw PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToRawLinear PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToWav PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToYm PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToVgm PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToSoundEffects PRIVATE ${WARNING_FLAGS})
target_compile_options(SongToSamples PRIVATE ${WARNING_FLAGS})
target_compile_options(Z80Profiler PRIVATE ${WARNING_FLAGS})
target_compile_options(BaseExport PRIVATE ${WARNING_FLAGS})
target_compile_options(BaseCli PRIVATE ${WARNING_FLAGS})
#target_compile_options(ThirdParty PRIVATE ${NO_WARNING_FLAGS})     # This actually doesn't work. Fallback on pragmas...

# Packaging via CPack.
include(cpack/CPackOptions.cmake)
