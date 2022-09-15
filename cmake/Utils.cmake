########################################################################################################################

# function that given a path, it evaluates whether it is a directory or a regular file;
# the check is based exclusively on the existence of file extensions (for files), so take that into account
#
function (utils_is_directory PATH RESULT)
    get_filename_component(EXTENSION "${PATH}" EXT)
    if (EXTENSION STREQUAL "")
        set("${RESULT}" "1" PARENT_SCOPE)
    else()
        set("${RESULT}" "0" PARENT_SCOPE)
    endif()
endfunction()

########################################################################################################################
