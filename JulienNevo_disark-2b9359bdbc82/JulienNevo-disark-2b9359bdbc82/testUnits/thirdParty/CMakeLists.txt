cmake_minimum_required(VERSION 3.12)

project(ThirdParty VERSION 1.0.0)

set(TargetName ${PROJECT_NAME})

add_library(${TargetName})

target_compile_definitions(${TargetName} PRIVATE)

target_sources(${TargetName}
        PRIVATE

        rasm/minilib.h
        rasm/rasm.c
        rasm/rasm.h
)