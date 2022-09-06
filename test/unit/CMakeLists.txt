# define the name of a new test target
#
set(TARGET_NAME "nano-ssl-test")

# list its source files
#
set(SOURCE_FILES "BasicTests.cpp")

# also list the targets under test (that the test target depends on)
#
set(TARGETS_UNDER_TEST "nano-ssl")

########################################################################################################################

# define and configure the test target by specifying its name,
# list of targets that it tests and list of its own source files
#
configure_test_target("${TARGET_NAME}" "${TARGETS_UNDER_TEST}" "${SOURCE_FILES}")

########################################################################################################################
