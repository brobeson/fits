if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.1)
    message(
      FATAL_ERROR
        "GCC version ${CMAKE_CXX_COMPILER_VERSION} is not supported. The minimum"
        " officially supported version of GCC is 8.3."
    )
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
    message(
      FATAL_ERROR
        "Clang version ${CMAKE_CXX_COMPILER_VERSION} is not supported. The"
        " minimum officially supported version of Clang is 7.1."
    )
  endif()
else()
  # TODO Add support for MSVC. See https://github.com/brobeson/ess/issues/15
  message(
    FATAL_ERROR
      "${CMAKE_CXX_COMPILER_ID} is not supported. At this time, only GCC and"
      " Clang are supported."
  )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(
    compiler_options
    -pedantic-errors
    -Walloca
    -Wcast-qual
    -Wconversion
    -Wdate-time
    -Wduplicated-branches
    -Wduplicated-cond
    -Weffc++
    -Werror
    -Wfloat-equal
    -Wformat=2
    -Winvalid-pch
    -Wlogical-op
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wnoexcept
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpedantic
    -Wplacement-new=2
    -Wredundant-decls
    -Wregister
    -Wshadow
    -Wsign-conversion
    -Wsign-promo
    -Wsubobject-linkage
    -Wswitch-default
    -Wswitch-enum
    -Wtrampolines
    -Wundef
    -Wunused
    -Wunused-macros
    -Wuseless-cast
    -Wzero-as-null-pointer-constant
    -Wall
    -Wextra
    "$<$<CONFIG:Debug>:-fstack-protector-strong>"
    "$<$<CONFIG:Debug>:-Wstack-protector>"
    "$<$<CONFIG:Debug>:-ggdb>"
  )
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0)
    list(
      APPEND
        compiler_options
        -fdiagnostics-show-template-tree
        -Wcast-align=strict
        -Wextra-semi
    )
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(
    compiler_options
    -fdiagnostics-show-template-tree
    -pedantic-errors
    -Weverything
    -Werror
    -Wno-c++98-c++11-c++14-compat
    -Wno-c++98-compat
    -Wno-c++11-compat
    -Wno-c++14-compat
    -Wno-documentation
    -Wno-documentation-unknown-command
    -Wno-padded
    -Wno-weak-vtables
    "$<$<CONFIG:Debug>:-fstack-protector-strong>"
    "$<$<CONFIG:Debug>:-Wstack-protector>"
    "$<$<CONFIG:Debug>:-ggdb>"
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(compiler_options /analyze /Wall /WX)
else()
  message(
    WARNING
      " Default compiler options are not enabled for your compiler.\n"
      " Detected CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}\n"
  )
endif()
