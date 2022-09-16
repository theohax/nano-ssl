########################################################################################################################

# function that returns the list of third party libraries (dependencies) that a target needs to link against
#
function (get_libraries_to_link_against RESULT)
    set(LOCAL_RESULT "${CONAN_TARGETS}")

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        list(APPEND LOCAL_RESULT "stdc++fs")
    endif()

    get_test_libraries_to_link_against(TEST_LIBRARIES_RESULT)
    list(REMOVE_ITEM LOCAL_RESULT "${TEST_LIBRARIES_RESULT}")

    set(${RESULT} "${LOCAL_RESULT}" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of third party libraries that (only) test targets needs to link against
#
function (get_test_libraries_to_link_against RESULT)
    set(LOCAL_RESULT CONAN_PKG::gtest)

    get_property(CUSTOM_TEST_LIBRARIES_RESULT GLOBAL PROPERTY GLOBAL_PROPERTY_TEST_LIBRARIES)
    foreach (TEST_LIBRARY IN LISTS CUSTOM_TEST_LIBRARIES_RESULT)
        list(APPEND LOCAL_RESULT "$<TARGET_OBJECTS:${TEST_LIBRARY}>")
    endforeach()

    set(${RESULT} "${LOCAL_RESULT}" PARENT_SCOPE)
endfunction()

########################################################################################################################
