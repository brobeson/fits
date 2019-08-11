# This file looks for clang-tidy. If it is found, clang-tidy is configured to
# run as part of the normal build process.

message(STATUS "Configuring clang-tidy.")
find_program(
  clang_tidy
  clang-tidy
  DOC "The path to the clang-tidy application."
)
mark_as_advanced(clang_tidy)
if(NOT clang_tidy)
  message(
    WARNING
    "Clang-tidy was not found, so it will not be run with the build."
  )
  return()
endif()

set(
  CMAKE_CXX_CLANG_TIDY
  "${clang_tidy}"
  -fix
  -fix-errors
)
