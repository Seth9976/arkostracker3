# CPack set-up file. Indicates what to put in the output archive.
# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html

# Help from https://github.com/nextcloud/desktop/blob/master/CMakeLists.txt
#           https://github.com/nextcloud/desktop/blob/master/NextcloudCPack.cmake
#           https://github.com/nextcloud/desktop/blob/master/NEXTCLOUD.cmake
# https://github.com/fluent/fluent-bit/blob/master/CMakeLists.txt
#
# https://manpages.ubuntu.com/manpages/focal/en/man7/cpack-generators.7.html
# https://stackoverflow.com/questions/46011440/cmake-cpack-preferred-package-generators-for-different-platforms
# MAC:
# https://forum.juce.com/t/prepare-plugins-for-distribution-on-macos-notarization-code-signing-etc/53124
# https://stackoverflow.com/questions/52894614/sign-executable-files-on-macos-using-cmake-and-packagemaker-cpack-generator
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cpack/PackageGenerators
# https://cmake.cmake.narkive.com/6mkvpWhK/cpack-generator-for-the-mac-app-store
# https://stackoverflow.com/questions/6323445/create-an-application-plist/6323462#6323462

# This file must be set from the template files. This is overwritten by the CI (or you locally) by only of the template files.
# It is useful to set specific vars for ZIP files (as opposed to other generators). This is a hack, but cannot find any other way to produce
# two families of generators without having to rebuild everything. Changing this file will NOT indicate Cmake something has changed.
# But adding a NEW var WILL!!! So start with the ZIP generator, then the other one (which contains a new var, allowing a fast rebuild).
include(cpack/usedConfig.cmake)


set(CPACK_PACKAGE_NAME "Arkos Tracker")
set(CPACK_PACKAGE_VENDOR "Arkos")

# Important: ONLY the files/target belonging the component "Program" will be put in the
# generated archive. If we don't do that, other lib/bin files are included,
# they are unwanted!
set(OUTPUT_COMPONENT Program)               # Also displayed by NSIS, so it should be meaningful!
string(TOUPPER ${OUTPUT_COMPONENT} OUTPUT_COMPONENT_UPPER)
set(TOOLS_DESTINATION_FOLDER ${DESTINATION_FOLDER}/tools)   # Folder inside the generated zip.

set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL ${OUTPUT_COMPONENT})

set(CPACK_SOURCE_STRIP_FILES true)
set(CPACK_STRIP_FILES true)

# All the generated files will have this name.
set (CPACK_PACKAGE_FILE_NAME "ArkosTracker")

# The installers may present these.
set(CPACK_PACKAGE_CONTACT "contact@julien-nevo.com")
set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/cpack/README.txt)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/cpack/LICENSE.txt)
set(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_SOURCE_DIR}/cpack/InstallerWelcome.txt)

# ZIP setup.
set(CPACK_ARCHIVE_${OUTPUT_COMPONENT_UPPER}_FILE_NAME ${PROJECT_NAME})
# RPM setup.
set(CPACK_RPM_MAIN_COMPONENT ${OUTPUT_COMPONENT})
# DEB setup.
#set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS YES)? See https://decovar.dev/blog/2021/09/23/cmake-cpack-package-deb-apt/
set(CPACK_DEBIAN_FILE_NAME ${PROJECT_NAME}.deb)
set(CPACK_DEBIAN_PACKAGE_NAME "ArkosTracker3")   # NO spaces allowed! Else will fail on install. This will show in the installer. Without spaces, doesn't look so good.
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "The ultimate AY/YM tracker!")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Targhan <${CPACK_PACKAGE_CONTACT}>")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libfreetype6-dev, libx11-dev, libxinerama-dev, libxrandr-dev, libxcursor-dev, mesa-common-dev, libasound2-dev, freeglut3-dev, libxcomposite-dev")
INSTALL(FILES cpack/arkostracker3.desktop DESTINATION /usr/share/applications)      # To have an icon and be search-able.

# NSIS setup. https://cmake.org/cmake/help/latest/cpack_gen/nsis.html#cpack_gen:CPack%20NSIS%20Generator
# An inner "Arkos Tracker 3" folder is created in NSIS, depending on the DESTINATION_FOLDER variable above. Couldn't remove it.
# See https://davidvelho.medium.com/packaging-with-cpack-nsis-on-windows-4a0e58026b07
set(CPACK_NSIS_WELCOME_TITLE "Welcome to Arkos Tracker 3!")
set(CPACK_NSIS_DISPLAY_NAME "Arkos Tracker")
set(CPACK_NSIS_BRANDING_TEXT " ")               # Not very useful to see.
set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/cpack/at3nsis.ico")    # Used by the installer icon. NOTE: the icon has a round background. If removed, the raw logo looks ugly.
set(CPACK_PACKAGE_EXECUTABLES "ArkosTracker3" "Arkos Tracker 3")    # For shortcut. The first param is the exe (do NOT put the extension), the second what is shown in the Start menu.
set(CPACK_NSIS_EXECUTABLES_DIRECTORY ${DESTINATION_FOLDER})         # Needed to indicate the folder inside the app where to find the exe. Default was "bin".
set(CPACK_NSIS_MODIFY_PATH "ON")                                    # Needed to ask the user whether to add a desktop icon.
set(CPACK_CREATE_DESKTOP_LINKS "ArkosTracker3")                     # The desktop icon. Refers to the CPACK_PACKAGE_EXECUTABLES exe.
set(CPACK_NSIS_INSTALLED_ICON_NAME "${DESTINATION_FOLDER}/ArkosTracker3.exe")  # Uninstall icon in Windows Uninstall page. https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html#id2


include(cpack/targets.cmake)

include(CPack)
