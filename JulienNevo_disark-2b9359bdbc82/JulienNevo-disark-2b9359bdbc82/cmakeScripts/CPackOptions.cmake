# CPack set-up file. Indicates what to put in the output archive.

# Help from https://github.com/nextcloud/desktop/blob/master/CMakeLists.txt
#           https://github.com/nextcloud/desktop/blob/master/NextcloudCPack.cmake
#           https://github.com/nextcloud/desktop/blob/master/NEXTCLOUD.cmake

set(CPACK_GENERATOR ZIP)

set(CPACK_PACKAGE_NAME "Disark")
set(CPACK_PACKAGE_VENDOR "Arkos")
set(CPACK_PACKAGE_FILE_NAME "Disark")       # Must not have space.

set(ZIP_NAME "Disark")

set(OUTPUT_COMPONENT Program)               # Should be meaningful.
string(TOUPPER ${OUTPUT_COMPONENT} OUTPUT_COMPONENT_UPPER)
set(DESTINATION_FOLDER .)                   # Folder inside the generated zip.

# Only installs the desired components (no junk besides what we want).
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL ${OUTPUT_COMPONENT})

set(CPACK_SOURCE_STRIP_FILES true)
set(CPACK_STRIP_FILES true)

# ZIP setup.
set(CPACK_ARCHIVE_${OUTPUT_COMPONENT_UPPER}_FILE_NAME ${ZIP_NAME})      # Name of the ZIP.

install(TARGETS
        DisarkMain
        DESTINATION ${DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
        )

include(CPack)