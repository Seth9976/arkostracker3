project(DisarkMain VERSION ${PROJECT_VERSION})

set(TargetName ${PROJECT_NAME})

juce_add_console_app(${TargetName}
        PRODUCT_NAME "Disark"
        )

# Sets the name of the exe (else it gets the name of the project).
set_target_properties(DisarkMain PROPERTIES OUTPUT_NAME disark)

target_sources(${TargetName}
        PRIVATE
        Main.cpp
        Tool.cpp
        Tool.h
        utils/commandLine/CommandLineArgumentDescriptor.cpp
        utils/commandLine/CommandLineArgumentDescriptor.h
        utils/commandLine/CommandLineConstants.cpp
        utils/commandLine/CommandLineConstants.h
        utils/commandLine/CommandLineParser.cpp
        utils/commandLine/CommandLineParser.h
        utils/commandLine/Option.cpp
        utils/commandLine/Option.h
        utils/commandLine/Parameter.cpp
        utils/commandLine/Parameter.h
        utils/StreamUtil.cpp
        utils/StreamUtil.h
        utils/StringUtil.cpp
        utils/StringUtil.h
        utils/MapUtil.h
        utils/CollectionUtil.h
        utils/NumberUtil.cpp
        utils/NumberUtil.h
        Disassembler.cpp
        Disassembler.h
        BinaryParser.cpp
        BinaryParser.h
        import/SymbolImporter.cpp
        import/SymbolImporter.h
        base/sourceItemVisitor/SourceItemEncoder.cpp
        base/sourceItemVisitor/SourceItemEncoder.h
        base/sourceItemVisitor/LabelGenerator.cpp
        base/sourceItemVisitor/LabelGenerator.h
        base/sourceItemVisitor/SourceItemVisitor.h
        base/Area.cpp
        base/Area.h
        base/AreaGenerator.cpp
        base/AreaGenerator.h
        base/AreaGenerator.h
        base/AreaTag.cpp
        base/AreaTag.h
        base/ExportConfiguration.cpp
        base/ExportConfiguration.h
        base/Instruction.cpp
        base/Instruction.h
        base/LabelAndAddress.cpp
        base/LabelAndAddress.h
        base/Opcode.cpp
        base/Opcode.h
        base/Opcodes.cpp
        base/Opcodes.h
        base/OpcodesFiller.cpp
        base/OpcodesFiller.h
        base/References.cpp
        base/References.h
        base/Region.cpp
        base/Region.h
        base/RegionDataHolder.cpp
        base/RegionDataHolder.h
        base/Regions.cpp
        base/Regions.h
        base/SourceItem.h
        base/SourceParameterType.h
        base/Symbol.cpp
        base/Symbol.h
        base/WriterUtils.cpp
        base/WriterUtils.h
        )

#target_compile_features(${TargetName} PRIVATE cxx_std_17)

target_compile_definitions(${TargetName}
        PRIVATE
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_console_app` call
        JUCE_USE_CURL=0    # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_console_app` call
        JUCE_MODULE_AVAILABLE_juce_opengl=0
        DONT_SET_USING_JUCE_NAMESPACE=1
        )

target_link_libraries(${TargetName}
        PRIVATE
        juce::juce_core
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        )
