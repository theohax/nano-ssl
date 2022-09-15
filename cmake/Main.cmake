########################################################################################################################

# function that acts as the "main" function of this script;
# it deals with calling other necessary "main" functions from other scripts
#
macro (main)
    # make sure the host (and target) systems are known
    #
    if (NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux" OR
             CMAKE_SYSTEM_NAME STREQUAL "Darwin" OR
             CMAKE_SYSTEM_NAME STREQUAL "Windows"))
        message(FATAL_ERROR "Unknown system `${CMAKE_SYSTEM_NAME}`.")
    endif()

    # set several variables with the paths of various locations needed by the build system
    #
    set(ROOT_DIRECTORY "${CMAKE_SOURCE_DIR}")
    set(CMAKE_DIRECTORY "${ROOT_DIRECTORY}/cmake")
    set(SOURCE_DIRECTORY "${ROOT_DIRECTORY}/src")
    set(SOURCE_PUBLIC_DIRECTORY "${SOURCE_DIRECTORY}/public")
    set(TEST_DIRECTORY "${ROOT_DIRECTORY}/test")
    set(TEST_UTILS_DIRECTORY "${TEST_DIRECTORY}/utils")
    set(TEST_UNIT_DIRECTORY "${TEST_DIRECTORY}/unit")
    set(TEST_INTEGRATION_DIRECTORY "${TEST_DIRECTORY}/integration")
    set(BUILD_DIRECTORY "${CMAKE_BINARY_DIR}")
    set(BUILD_BIN_DIRECTORY "${BUILD_DIRECTORY}/bin")
    set(BUILD_GENERATED_DIRECTORY "${BUILD_DIRECTORY}/generated")
    set(BUILD_GENERATED_PUBLIC_DIRECTORY "${BUILD_GENERATED_DIRECTORY}/public")
    set(BUILD_LIB_DIRECTORY "${BUILD_DIRECTORY}/lib")

    # include other CMake scripts
    #
    include("GNUInstallDirs")
    include("${CMAKE_DIRECTORY}/BuildOptions.cmake")
    include("${CMAKE_DIRECTORY}/Conan.cmake")
    include("${CMAKE_DIRECTORY}/Dependencies.cmake")
    include("${CMAKE_DIRECTORY}/Installation.cmake")
    include("${CMAKE_DIRECTORY}/Options.cmake")
    include("${CMAKE_DIRECTORY}/TargetConfiguration.cmake")
    include("${CMAKE_DIRECTORY}/Utils.cmake")

    # call other "main" functions
    #
    conan_main()
    options_main()

    # continue processing other CMakeLists files
    #
    add_subdirectory("${SOURCE_DIRECTORY}")
    add_subdirectory("${TEST_DIRECTORY}")
endmacro()

########################################################################################################################
