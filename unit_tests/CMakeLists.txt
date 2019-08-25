# This variable controls the method of dynamic analysis to use with the unit
# tests. CMake doesn't have a built in method of ensuring a variable value is
# within an allowed set of values. So it has to be manually done here. For
# simplicity, the value is always forced to lower case.
set(
  dynamic_analysis
  "none"
  CACHE
  STRING
  "The type of dynamic analysis to build into the project."
)
set_property(
  CACHE
  dynamic_analysis
  PROPERTY
    STRINGS "none;asan;valgrind"
)
string(TOLOWER ${dynamic_analysis} analysis)
get_property(strings CACHE dynamic_analysis PROPERTY STRINGS)
if(NOT analysis IN_LIST strings)
  message(SEND_ERROR "${analysis} is not a valid value for dynamic_analysis.")
else()
  set(
    dynamic_analysis
    ${analysis}
    CACHE
    STRING
    "The type of dynamic analysis to build into the project."
  )
endif()

find_package(Catch2 REQUIRED)

set(tests
  header_entry_test
)
foreach(test IN LISTS tests)
  add_executable(${test} ${test}.cpp main.cpp)
  target_link_libraries(
    ${test}
    PRIVATE
      $<$<STREQUAL:"${dynamic_analysis}","asan">:asan>
      Catch2::Catch2
      fits::fits
  )
  target_compile_definitions(${test} PRIVATE GSL_THROW_ON_CONTRACT_VIOLATION)
  target_compile_options(${test}
    PRIVATE
      $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
  )
  add_test(NAME ${test} COMMAND ${test})
endforeach()
set_tests_properties(${tests} PROPERTIES LABELS unit)
