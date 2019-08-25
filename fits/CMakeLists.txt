add_library(fits
  header.cpp
  header.h
)
add_library(fits::fits ALIAS fits)
target_include_directories(fits PUBLIC "${CMAKE_SOURCE_DIR}")
target_compile_features(fits PUBLIC cxx_std_17)
target_compile_options(fits
  PRIVATE
    ${compiler_options}
    $<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>
)
find_package(gsl_microsoft REQUIRED)
target_link_libraries(fits
  PUBLIC
    $<$<CXX_COMPILER_ID:Clang>:c++>
    gsl_microsoft::gsl_microsoft
)
