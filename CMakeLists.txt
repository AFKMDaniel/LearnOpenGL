cmake_minimum_required (VERSION 3.28)

project ("LearnOpenGL" LANGUAGES CXX C)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(lib)
add_subdirectory(src)
