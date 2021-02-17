cmake_minimum_required(VERSION 3.13)
project(grpc-cmake-template LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add cmake-scripts
include(FetchContent)
FetchContent_Declare(
  cmake_scripts
  GIT_REPOSITORY https://github.com/StableCoder/cmake-scripts.git
  GIT_TAG main
  GIT_SHALLOW TRUE)

FetchContent_Populate(cmake_scripts)

set(CMAKE_MODULE_PATH "${FETCHCONTENT_BASE_DIR}/cmake_scripts-src/;")
include(c++-standards)
include(code-coverage)
include(sanitizers)
include(tools)
include(dependency-graph)

# Configure compiler options
set(CMAKE_CXX_STANDARD 14)

if(MSVC)
  add_compile_options(/W2 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror -static)
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

# Add include folders
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Include subfolders
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(proto)

# Formating and linting all related files
file(GLOB_RECURSE SRCS_AND_HDRS client/*.cpp client/*.h server/*.cpp)
find_program(CLANG_FORMAT NAMES clang-format)
if(${CLANG_FORMAT} STREQUAL "CLANG_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_cpp_stamp
    DEPENDS ${SRCS_AND_HDRS}
    COMMAND touch .fmt_cpp_stamp
    COMMENT "Could not find clang-format. Skip formating C++ files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .fmt_cpp_stamp
    DEPENDS ${SRCS_AND_HDRS}
    COMMAND ${CLANG_FORMAT} -i ${SRCS_AND_HDRS}
    COMMAND touch .fmt_cpp_stamp
    COMMENT "Format C++ files with clang-format."
    VERBATIM)
endif()

file(GLOB CMAKE_FILES CMakeLists.txt client/CMakeLists.txt proto/CMakeLists.txt
     server/CMakeLists.txt)
find_program(CMAKE_FORMAT NAMES cmake-format)
if(${CMAKE_FORMAT} STREQUAL "CMAKE_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND touch .fmt_cmake_stamp
    COMMENT "Could not find cmake-format. Skip formatting CMake files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .fmt_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND cmake-format -i ${CMAKE_FILES}
    COMMAND touch .fmt_cmake_stamp
    COMMENT "Format CMake files with cmake-format."
    VERBATIM)
endif()

file(GLOB SH_SRCS 3p/*.sh)
find_program(SHFMT NAMES shfmt)
if(${SHFMT} STREQUAL "SHFMT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_bash_stamp
    DEPENDS ${SH_SRCS}
    COMMAND touch .fmt_bash_stamp
    COMMENT "Could not find shfmt. Skip formatting Bash scripts."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .fmt_bash_stamp
    DEPENDS ${SH_SRCS}
    COMMAND ${SHFMT} -i 2 -ci -w ${SH_SRCS}
    COMMAND touch .fmt_bash_stamp
    COMMENT "Format Bash scripts with shfmt."
    VERBATIM)
endif()

add_custom_target(
  format
  DEPENDS .fmt_bash_stamp .fmt_cpp_stamp .fmt_cmake_stamp
  COMMENT "Format Bash, C++, and CMake files.")

find_program(SHELLCHECK NAMES shellcheck)
if(${SHELLCHECK} STREQUAL "SHELLCHECK-NOTFOUND")
  add_custom_command(
    OUTPUT .lint_shellcheck_stamp
    DEPENDS ${SH_SRCS}
    COMMAND touch .lint_shellcheck_stamp
    COMMENT "Skip linting Bash scripts."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .lint_shellcheck_stamp
    DEPENDS ${SH_SRCS}
    COMMAND shellcheck ${SH_SRCS}
    COMMAND touch .lint_shellcheck_stamp
    COMMENT "Lint Bash files with shellcheck.")
endif()

add_custom_command(
  OUTPUT .lint_cmake_stamp
  DEPENDS ${CMAKE_FILES}
  COMMAND cmake-lint ${CMAKE_FILES}
  COMMAND touch .lint_cmake_stamp
  COMMENT "Lint CMake files with cmake-lint.")

add_custom_target(
  lint ALL
  DEPENDS .lint_shellcheck_stamp
  COMMENT "Lint Bash and CMake files.")
