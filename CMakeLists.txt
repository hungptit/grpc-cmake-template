cmake_minimum_required(VERSION 3.18)
project(grpc-cmake-template LANGUAGES CXX)

# Get gRPC libraries
include(FetchContent)
FetchContent_Declare(
  grpc
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG master)
FetchContent_Populate(grpc)

# Add include folders
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Include subfolders
file(GLOB CMAKE_FILES CMakeLists.txt)
find_program(CMAKE_FORMAT NAMES cmake-format)
if(${CMAKE_FORMAT} STREQUAL "CMAKE_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND echo "Could not find cmake-format. Skip formatting CMake files."
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

file(GLOB SH_SRCS scripts/*.sh *.sh)
find_program(SHFMT NAMES shfmt)
if(${SHFMT} STREQUAL "SHFMT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_bash_stamp
    DEPENDS ${SH_SRCS}
    COMMAND echo "Could not find shfmt. Skip formatting Bash scripts."
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
  DEPENDS .fmt_bash_stamp .fmt_cmake_stamp
  COMMENT "Format Bash and CMake files.")

# Lint Bash scripts
find_program(SHELLCHECK NAMES shellcheck)
if(${SHELLCHECK} STREQUAL "SHELLCHECK-NOTFOUND")
  add_custom_command(
    OUTPUT .lint_shellcheck_stamp
    DEPENDS ${SH_SRCS}
    COMMAND echo "Skip linting Bash scripts."
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

# Lint all CMake files
find_program(CMAKE_LINT NAMES cmake-format)
if(${CMAKE_LINT} STREQUAL "CMAKE_LINT-NOTFOUND")
  add_custom_command(
    OUTPUT .lint_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND echo "Could not find cmake-lint. Skip linting CMake files."
    COMMENT "Could not find cmake-lint. Skip linting CMake files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .lint_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND cmake-lint ${CMAKE_FILES}
    COMMAND touch .lint_cmake_stamp
    COMMENT "Lint CMake files with cmake-format."
    VERBATIM)
endif()

add_custom_target(
  lint ALL
  DEPENDS .lint_shellcheck_stamp .lint_cmake_stamp
  COMMENT "Lint Bash and CMake files.")
