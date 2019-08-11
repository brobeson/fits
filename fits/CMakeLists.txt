add_library(fits
  header_block.cpp
  header_block.h
)
add_library(fits::fits ALIAS fits)
target_include_directories(fits PUBLIC "${CMAKE_SOURCE_DIR}")
target_compile_features(fits PUBLIC cxx_std_17)
target_compile_options(fits PRIVATE ${compiler_options})
find_package(gsl_microsoft REQUIRED)
target_link_libraries(fits PUBLIC gsl_microsoft::gsl_microsoft)
