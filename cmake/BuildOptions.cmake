########################################################################################################################

# function that sets the default CMake variables with general compilation features
#
function (set_general_compile_features)
    set(CMAKE_CXX_STANDARD "20" PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED "ON" PARENT_SCOPE)
    set(CMAKE_CXX_EXTENSIONS "OFF" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that sets the default CMake variables with build output directories
#
function (set_build_output_directories)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_LIB_DIRECTORY}" PARENT_SCOPE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_LIB_DIRECTORY}" PARENT_SCOPE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_BIN_DIRECTORY}" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of general compile features to be used when configuring a target
#
function (get_compile_features RESULT)
    set(${RESULT} "cxx_std_20" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of defines to be injected at compile time
#
function (get_compile_definitions RESULT)
    set(${RESULT} "" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of specific compilation options to be used when configuring a target
#
function (get_compile_options RESULT)
    set(${RESULT} "-Werror"
                  $<$<CONFIG:Debug>:-g>
                  $<$<CONFIG:Debug>:-ggdb>
                  $<$<CONFIG:Debug>:-O0>
                  $<$<CONFIG:Release>:-O2>
        PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of compilation warnings to be used when configuring a target
#
function (get_compile_warnings RESULT)
    set(${RESULT} "-Wall"
                  "-Wextra"
                  "-Wpedantic"
                  "-Wfloat-equal"
                  "-Wctor-dtor-privacy"
                  "-Winit-self"
                  "-Wmissing-declarations"
                  "-Wnoexcept"
                  "-Wnon-virtual-dtor"
                  "-Wold-style-cast"
                  "-Woverloaded-virtual"
                  "-Wredundant-decls"
                  "-Wshadow"
                  "-Wsign-promo"
                  "-Wswitch-default"
                  "-Wundef"
       PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of additional include directories to be provided when configuring a target
#
function (get_include_directories RESULT)
    set(${RESULT} "${SOURCE_DIRECTORY}" PARENT_SCOPE)
endfunction()

########################################################################################################################

# function that returns the list of linking options to be used when configuring a target
#
function (get_link_options RESULT)
    set(${RESULT} $<$<CONFIG:Release>:-flto>
        PARENT_SCOPE)
endfunction()

########################################################################################################################
