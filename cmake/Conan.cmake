########################################################################################################################

# function that acts as the "main" function of this script;
# it calls the Conan setup routines initializing all third party dependencies variables
#
macro (conan_main)
    find_program(CONAN conan)
    if (NOT CONAN)
        message(FATAL_ERROR "Cannot find conan. Is it installed?")
    endif()

    set(CONAN_BUILD_INFO_SCRIPT "${BUILD_DIRECTORY}/conanbuildinfo.cmake")
    if (NOT EXISTS "${CONAN_BUILD_INFO_SCRIPT}")
        execute_process(COMMAND "${CONAN}" install .
                                           --build=missing
                                           "--install-folder=${BUILD_DIRECTORY}"
                        WORKING_DIRECTORY "${ROOT_DIRECTORY}"
                        RESULT_VARIABLE RESULT)
        if (NOT RESULT STREQUAL "0")
            message(FATAL_ERROR "Unable to fetch dependencies: `conan install` failed. See errors above.")
        endif()
    endif()

    include("${CONAN_BUILD_INFO_SCRIPT}")
    conan_basic_setup(TARGETS)
endmacro()

########################################################################################################################
