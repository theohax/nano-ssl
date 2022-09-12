########################################################################################################################

# define the name of a new test library
#
set(TARGET_NAME "nanossl-test-utils")

# list its source files
#
set(SOURCE_FILES "std_output_redirect.cpp"
                 "expected_failure_message.cpp")

########################################################################################################################

# define and configure the test library by specifying its name and list of source files
#
configure_test_library("${TARGET_NAME}" "${SOURCE_FILES}")

########################################################################################################################
