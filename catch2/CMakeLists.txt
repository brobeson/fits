add_library(catch2 INTERFACE)
target_include_directories(catch2 SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
add_library(catch::catch2 ALIAS catch2)