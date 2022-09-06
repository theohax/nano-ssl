# specify a recent CMake version
#
cmake_minimum_required(VERSION "3.21.0")

# define the project name and languages
#
project("nano-ssl" LANGUAGES CXX)

# call "main" CMake function
#
include("cmake/Main.cmake")
main()
