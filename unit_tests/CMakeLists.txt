option(fits_enable_asan "Enable or disable building with Address Sanitizer."
       off)
find_package(Catch2 REQUIRED)

set(tests header_entry_test)
# cmake-format: off
foreach(test IN LISTS tests)
# cmake-format: on
  add_executable(${test} ${test}.cpp main.cpp)
  target_link_libraries(
    ${test}
    PRIVATE $<$<BOOL:${fits_enable_asan}>:asan> Catch2::Catch2 fits::fits
  )
  target_compile_definitions(${test} PRIVATE GSL_THROW_ON_CONTRACT_VIOLATION)
  target_compile_options(
    ${test}
    PRIVATE $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
  )
  add_test(NAME ${test} COMMAND ${test})
endforeach()
set_tests_properties(${tests} PROPERTIES LABELS unit)
