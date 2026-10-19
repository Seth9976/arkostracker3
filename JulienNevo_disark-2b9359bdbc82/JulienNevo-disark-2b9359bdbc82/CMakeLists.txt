cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME Disark)
file(STRINGS "ProjectVersion.txt" PROJECT_VERSION)      # Defines the project version from the file, also used by the CI.

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

# Including CPM.cmake, a package manager:
# https://github.com/TheLartians/CPM.cmake
include(cmakeScripts/CPM.cmake)

# Uses C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Gets JUCE from GIT, via CPM.
CPMAddPackage(
        NAME JUCE
        GITHUB_REPOSITORY juce-framework/JUCE
        GIT_TAG 7.0.4)

add_subdirectory(sources)
add_subdirectory(testUnits)

# Defines "full warnings" and "no warnings" flag, used below according to the project.
if ((CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") OR (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC"))
    set(WARNING_FLAGS /Wall /WX)
    set(NO_WARNING_FLAGS /w)
elseif ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    # Same as for GCC below, but without -Wnoexcept and -Wstrict-null-sentinel
    # which are unknown.
    set(WARNING_FLAGS
            -Wall -Wextra -pedantic -pedantic-errors -Wunused-variable
            -Werror -Wconversion -Wsign-conversion -Wcast-align
            -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2
            -Winit-self -Wmissing-include-dirs -Woverloaded-virtual
            -Wredundant-decls -Wshadow -Wstrict-overflow=5
            -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
            )
    set(NO_WARNING_FLAGS -w)
else()  # GNU (=GCC)
    # JUCE cannot compile with -Wundef -Wold-style-cast -Wcast-qual -Wlogical-op.
    set(WARNING_FLAGS
            -Wall -Wextra -pedantic -pedantic-errors -Wunused-variable
            -Werror -Wconversion -Wsign-conversion -Wcast-align
            -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2
            -Winit-self -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual
            -Wredundant-decls -Wshadow -Wstrict-null-sentinel -Wstrict-overflow=5
            -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
            )
    set(NO_WARNING_FLAGS -w)
endif()

# For our code (only!), make sure we get all the warnings.
target_compile_options(DisarkMain PRIVATE ${WARNING_FLAGS})
target_compile_options(TestUnits PRIVATE ${WARNING_FLAGS})
target_compile_options(ThirdParty PRIVATE ${NO_WARNING_FLAGS})

# Packaging via CPack.
include(cmakeScripts/CPackOptions.cmake)
