########################################################################################################################

function (_options_do_parse)
    if (NANOSSL_BUILD_SHARED_LIBRARIES)
        set(NANOSSL_LIBRARIES_TYPE "SHARED_LIBRARY" PARENT_SCOPE)
    else()
        set(NANOSSL_LIBRARIES_TYPE "STATIC_LIBRARY" PARENT_SCOPE)
    endif()
endfunction()

########################################################################################################################

# function that acts as the "main" function of this script; it declares the various
# options configurable via CMake, parses them and possibly sets other data based on them
#
macro (options_main)
    option(NANOSSL_BUILD_SHARED_LIBRARIES "Whether to build shared libraries or static ones" OFF)

    _options_do_parse()
endmacro()

########################################################################################################################
