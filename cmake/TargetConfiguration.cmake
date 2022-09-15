########################################################################################################################

# private function that checks that a list of source files is well formed
#
function (_private_check_target_source_files TARGET_NAME SOURCE_FILES)
    if (NOT SOURCE_FILES)
        message(FATAL_ERROR "Target `${TARGET_NAME}` cannot be configured without any source files.")
    endif()

    list(LENGTH SOURCE_FILES SOURCE_FILES_COUNT)
    if (SOURCE_FILES_COUNT LESS 1)
        message(FATAL_ERROR "Target `${TARGET_NAME}` cannot be configured without any source files.")
    endif()
endfunction()

########################################################################################################################

# private function that checks that a target actually exists (has previously been configured)
#
function (_private_check_target_exists TARGET_NAME)
    if (NOT TARGET "${TARGET_NAME}")
        message(FATAL_ERROR "Unable to find target `${TARGET_NAME}`. Has it been configured?")
    endif()
endfunction()

########################################################################################################################

# private function that given a target name applies the
# corresponding compilation and linking flags in order to build it
#
function (_private_apply_build_options_to_target TARGET_NAME)
    get_compile_features(COMPILE_FEATURES_RESULT)
    target_compile_features("${TARGET_NAME}" PRIVATE "${COMPILE_FEATURES_RESULT}")
    set_general_compile_features()
    set_build_output_directories()

    get_compile_definitions(COMPILE_DEFINITIONS_RESULT)
    target_compile_definitions("${TARGET_NAME}" PRIVATE "${COMPILE_DEFINITIONS_RESULT}")

    get_compile_options(COMPILE_OPTIONS_RESULT)
    get_compile_warnings(COMPILE_WARNINGS_RESULT)
    target_compile_options("${TARGET_NAME}" PRIVATE "${COMPILE_OPTIONS_RESULT}" "${COMPILE_WARNINGS_RESULT}")

    get_include_directories(INCLUDE_DIRECTORIES_RESULT)
    target_include_directories("${TARGET_NAME}" PRIVATE "${INCLUDE_DIRECTORIES_RESULT}")

    get_link_options(LINK_OPTIONS_RESULT)
    target_link_options("${TARGET_NAME}" PRIVATE "${LINK_OPTIONS_RESULT}")

    get_libraries_to_link_against(LIBRARIES_RESULT)
    target_link_libraries("${TARGET_NAME}" PRIVATE "${LIBRARIES_RESULT}")
endfunction()

########################################################################################################################

# function that defines a new target
# (given its name, type [STATIC_LIBRARY, SHARED_LIBRARY] and list of source files)
# and configures it with all the necessary flags for building
#
function (configure_target TARGET_NAME TARGET_TYPE SOURCE_FILES)
    _private_check_target_source_files(${TARGET_NAME} "${SOURCE_FILES}")

    if (TARGET_TYPE STREQUAL "SHARED_LIBRARY")
        set(LIBRARY_TARGET_TYPE "SHARED")
    elseif (TARGET_TYPE STREQUAL "STATIC_LIBRARY")
        set(LIBRARY_TARGET_TYPE "STATIC")
    else()
        message(FATAL_ERROR "Target `${TARGET_NAME}` does not have a known "
                            "type (SHARED_LIBRARY, STATIC_LIBRARY)")
    endif()

    add_library("${TARGET_NAME}" "${LIBRARY_TARGET_TYPE}" "${SOURCE_FILES}")
    _private_apply_build_options_to_target("${TARGET_NAME}")
endfunction()

########################################################################################################################

# function that defines a test library to be linked with by test targets
#
function (configure_test_library TARGET_NAME SOURCE_FILES)
    _private_check_target_source_files("${TARGET_NAME}" "${SOURCE_FILES}")

    add_library("${TARGET_NAME}" OBJECT "${SOURCE_FILES}")

    _private_apply_build_options_to_target("${TARGET_NAME}")

    get_test_include_directories(TEST_INCLUDE_DIRECTORIES_RESULT)
    target_include_directories("${TARGET_NAME}" PRIVATE "${TEST_INCLUDE_DIRECTORIES_RESULT}")

    get_property(TEST_LIBRARIES_RESULT GLOBAL PROPERTY GLOBAL_PROPERTY_TEST_LIBRARIES)
    list(APPEND TEST_LIBRARIES_RESULT "${TARGET_NAME}")
    set_property(GLOBAL PROPERTY GLOBAL_PROPERTY_TEST_LIBRARIES "${TEST_LIBRARIES_RESULT}")
endfunction()

########################################################################################################################

# function that defines a new test target (given its name,
# a list of other targets that it tests and therefore depends on and the
# list of its own source files) and configures it with all the necessary flags for building
#
function (configure_test_target TARGET_NAME TARGETS_UNDER_TEST SOURCE_FILES)
    _private_check_target_source_files("${TARGET_NAME}" "${SOURCE_FILES}")

    enable_testing()

    add_executable("${TARGET_NAME}" "${SOURCE_FILES}")
    add_test(NAME "${TARGET_NAME}" COMMAND "${TARGET_NAME}")

    _private_apply_build_options_to_target("${TARGET_NAME}")

    get_test_libraries_to_link_against(TEST_LIBRARIES_RESULT)
    target_link_libraries("${TARGET_NAME}" PRIVATE "${TEST_LIBRARIES_RESULT}")

    get_test_include_directories(TEST_INCLUDE_DIRECTORIES_RESULT)
    target_include_directories("${TARGET_NAME}" PRIVATE "${TEST_INCLUDE_DIRECTORIES_RESULT}")

    foreach (DEPENDENCY_TARGET "${TARGETS_UNDER_TEST}")
        if (NOT TARGET "${DEPENDENCY_TARGET}")
            message(FATAL_ERROR "Cannot find target under test "
                                "`${DEPENDENCY_TARGET}` needed by test target `${TARGET_NAME}`.")
        endif()

        target_sources("${TARGET_NAME}" PRIVATE "$<TARGET_OBJECTS:${DEPENDENCY_TARGET}>")
    endforeach()
endfunction()

########################################################################################################################
