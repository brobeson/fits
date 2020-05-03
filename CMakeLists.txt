cmake_minimum_required(VERSION 3.13)

project(
  fits
  DESCRIPTION "A C++ library for reading and writing FITS files."
  HOMEPAGE_URL "https://github.com/brobeson/fits"
  LANGUAGES CXX
)

include(cmake/compiler.cmake)
add_subdirectory(fits)

option(fits_enable_tests "Enable or disable building FITS tests." on)
if(fits_enable_tests)
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
    add_subdirectory(catch2)
    add_subdirectory(unit_tests)
    # add_subdirectory(compilation_tests)
  endif()
endif()
