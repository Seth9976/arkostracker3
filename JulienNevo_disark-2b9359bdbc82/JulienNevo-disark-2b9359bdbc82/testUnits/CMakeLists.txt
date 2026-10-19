cmake_minimum_required(VERSION 3.12)

project(TestUnits VERSION 1.0.0)

set(TargetName ${PROJECT_NAME})

juce_add_console_app(${TargetName}
        PRODUCT_NAME "Test Units")

add_subdirectory(thirdParty)
add_subdirectory(testUnitResources)

target_sources(${TargetName}
        PRIVATE
        Main.cpp

        ../sources/utils/commandLine/CommandLineArgumentDescriptor.cpp
        ../sources/utils/commandLine/CommandLineArgumentDescriptor.h
        ../sources/utils/commandLine/CommandLineConstants.cpp
        ../sources/utils/commandLine/CommandLineConstants.h
        ../sources/utils/commandLine/CommandLineParser.cpp
        ../sources/utils/commandLine/CommandLineParser.h
        ../sources/utils/commandLine/Option.cpp
        ../sources/utils/commandLine/Option.h
        ../sources/utils/commandLine/Parameter.cpp
        ../sources/utils/commandLine/Parameter.h
        ../sources/utils/StreamUtil.cpp
        ../sources/utils/StreamUtil.h
        ../sources/utils/StringUtil.cpp
        ../sources/utils/StringUtil.h
        ../sources/utils/MapUtil.h
        ../sources/utils/CollectionUtil.h
        ../sources/utils/NumberUtil.cpp
        ../sources/utils/NumberUtil.h
        ../sources/Disassembler.cpp
        ../sources/Disassembler.h
        ../sources/BinaryParser.cpp
        ../sources/BinaryParser.h
        ../sources/import/SymbolImporter.cpp
        ../sources/import/SymbolImporter.h
        ../sources/base/sourceItemVisitor/SourceItemEncoder.cpp
        ../sources/base/sourceItemVisitor/SourceItemEncoder.h
        ../sources/base/sourceItemVisitor/LabelGenerator.cpp
        ../sources/base/sourceItemVisitor/LabelGenerator.h
        ../sources/base/sourceItemVisitor/SourceItemVisitor.h
        ../sources/base/Area.cpp
        ../sources/base/Area.h
        ../sources/base/AreaGenerator.cpp
        ../sources/base/AreaGenerator.h
        ../sources/base/AreaGenerator.h
        ../sources/base/AreaTag.cpp
        ../sources/base/AreaTag.h
        ../sources/base/ExportConfiguration.cpp
        ../sources/base/ExportConfiguration.h
        ../sources/base/Instruction.cpp
        ../sources/base/Instruction.h
        ../sources/base/LabelAndAddress.cpp
        ../sources/base/LabelAndAddress.h
        ../sources/base/Opcode.cpp
        ../sources/base/Opcode.h
        ../sources/base/Opcodes.cpp
        ../sources/base/Opcodes.h
        ../sources/base/OpcodesFiller.cpp
        ../sources/base/OpcodesFiller.h
        ../sources/base/References.cpp
        ../sources/base/References.h
        ../sources/base/Region.cpp
        ../sources/base/Region.h
        ../sources/base/RegionDataHolder.cpp
        ../sources/base/RegionDataHolder.h
        ../sources/base/Regions.cpp
        ../sources/base/Regions.h
        ../sources/base/SourceItem.h
        ../sources/base/SourceParameterType.h
        ../sources/base/Symbol.cpp
        ../sources/base/Symbol.h
        ../sources/base/WriterUtils.cpp
        ../sources/base/WriterUtils.h

        # Test helpers.
        utils/MemoryBlockUtil.cpp
        utils/MemoryBlockUtil.h
        utils/BinaryParserTest.h
        utils/DisassemblerTest.h
        utils/RasmHelper.cpp
        utils/RasmHelper.h
        utils/PlayerType.h
        utils/TargetHardware.h
        utils/FileUtil.cpp
        utils/FileUtil.h

        # The tests themselves.
        DisarkTest.cpp
        DisarkBaseTest.cpp
        SymbolImporterTest.cpp
)

target_compile_features(${TargetName} PRIVATE cxx_std_11)

target_compile_definitions(${TargetName}
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_console_app` call
        JUCE_USE_CURL=0    # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_console_app` call
        JUCE_MODULE_AVAILABLE_juce_opengl=0
        DONT_SET_USING_JUCE_NAMESPACE=1
        )

target_link_libraries(${TargetName}
        PRIVATE
        juce::juce_core
        ThirdParty
        TestUnitResources
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)