cmake_minimum_required(VERSION 3.13)

project(
  fits
  DESCRIPTION "A library for the FITS file type."
  HOMEPAGE_URL "https://github.com/brobeson/fits"
  LANGUAGES CXX
)

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
