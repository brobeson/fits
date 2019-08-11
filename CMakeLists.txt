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

option(
  quality_checks
  "Disabling this disables quality checks such as clang-tidy and Cppcheck."
  on
)
if(quality_checks)
  include(cmake/clang-tidy.cmake)
endif()
include(cmake/compiler.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
add_subdirectory(fits)

if(quality_checks)
  # Note, that the memory check variables must be set up before CTest is
  # included. Thus, they are here and not in the unit_tests directory.
  string(CONCAT
    MEMORYCHECK_COMMAND_OPTIONS
    "--quiet"
    " --gen-suppressions=all"
    " --tool=memcheck"
    " --leak-check=yes"
    " --track-origins=yes"
    " --error-exitcode=1"
  )
  include(CTest)
  add_subdirectory(unit_tests)
  #add_subdirectory(compilation_tests)
endif()
