add_library(fits
  fits/errors.cpp
  fits/errors.h
  fits/header_block.cpp
  fits/header_block.h
)
add_library(fits::fits ALIAS fits)
target_include_directories(fits PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(fits PUBLIC cxx_std_17)
target_compile_options(
  fits
  PRIVATE
    ${compiler_options}
    $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
)
target_link_libraries(fits PUBLIC $<$<CXX_COMPILER_ID:Clang>:c++>)
