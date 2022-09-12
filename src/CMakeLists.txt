########################################################################################################################

# define the name of a new target
#
set(TARGET_NAME "nanossl")

# list its source files
#
set(SOURCE_FILES "MissingSourceTodo.cpp")

########################################################################################################################

# define and configure the target by specifying its name, type and list of source files
#
configure_target("${TARGET_NAME}" "SHARED_LIBRARY" "${SOURCE_FILES}")

########################################################################################################################
