option(fits_enable_asan "Enable or disable building with Address Sanitizer." off)
set(tests errors_test keyword_record_test)
foreach(test IN LISTS tests)
  add_executable(${test} ${test}.cpp fits_testing.h fits_testing.cpp)
  target_link_libraries(
    ${test}
    PRIVATE
      $<$<BOOL:${fits_enable_asan}>:asan>
      catch::catch2
      fits::fits
  )
  # target_compile_definitions(${test} PRIVATE GSL_THROW_ON_CONTRACT_VIOLATION)
  target_compile_options(
    ${test}
    PRIVATE $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
  )
  add_test(NAME ${test} COMMAND ${test})
endforeach()
set_tests_properties(${tests} PROPERTIES LABELS unit)
