cmake_minimum_required(VERSION 3.12)

if(CMAKE_BINARY_DIR MATCHES "${CMAKE_SOURCE_DIR}.*")
  message(FATAL_ERROR "In source builds are not allowed.")
endif()

project(
  fits
  VERSION 0.0
  DESCRIPTION "A library for the FITS file type."
  HOMEPAGE_URL "https://github.com/brobeson/fits"
  LANGUAGES CXX
)

include(cmake/clang-tidy.cmake)
include(cmake/compiler.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
add_subdirectory(fits)

string(
  CONCAT
    MEMORYCHECK_COMMAND_OPTIONS
    "--quiet"
    " --gen-suppressions=all"
    " --tool=memcheck"
    " --leak-check=yes"
    " --track-origins=yes"
    " --error-exitcode=1"
)
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(unit_tests)
  # add_subdirectory(compilation_tests)
endif()
