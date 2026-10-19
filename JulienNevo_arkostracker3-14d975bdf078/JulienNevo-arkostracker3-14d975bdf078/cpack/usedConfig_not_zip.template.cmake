# Copy this file to overwrite "usedConfig.cmake". The CI will do that.
# *** IMPORTANT ***: use this template AFTER the ZIP one, as a dummy var is added below, so a reconfiguration can be triggered.

if (WIN32)
    set(CPACK_GENERATOR NSIS)
    # Where to install.
    # If not set, the whole "ArkosTracker 3.x.x" will be used as an output folder, which is not very friendly.
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "ArkosTracker3")
elseif (APPLE)
    # According to SO link above, DnD package is only for one exe, which does not suit us, as there are also tools.
    # Bundle and PackageMaker are superseded by ProductBuild.
    set(CPACK_GENERATOR productbuild)
elseif (UNIX)
    # DEB ok but in the applications, only in "add on".
    set(CPACK_GENERATOR RPM;DEB)
    # Setting the at3 folder here allows us not to modify DESTINATION_FOLDER.
    # Default is "/usr", which may be too generic. "/usr/local" is fine, but "/opt" seems to be the best practice.
    set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/arkostracker3")
endif ()

set(DESTINATION_FOLDER "./")                # No need to have a folder inside the already existing app folder in Program Files.

# Cmake will detect a change ONLY if something is NEW. A change of var does not value for a re-evaluation.
set(DUMMY_VAR dummy)