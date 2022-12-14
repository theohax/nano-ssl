########################################################################################################################

# function that returns the list of third party libraries (dependencies) that a target needs to link against
#
function (get_libraries_to_link_against RESULT)
    set(LOCAL_RESULT "${CONAN_TARGETS}"
                     stdc++fs)

    get_test_libraries_to_link_against(TEST_LIBRARIES_RESULT)
    list(REMOVE_ITEM LOCAL_RESULT "${TEST_LIBRARIES_RESULT}")

    set(${RESULT} "${LOCAL_RESULT}" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of third party libraries that (only) test targets needs to link against
#
function (get_test_libraries_to_link_against RESULT)
    set(${RESULT} CONAN_PKG::gtest
        PARENT_SCOPE)
endfunction()

########################################################################################################################
