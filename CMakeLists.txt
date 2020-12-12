cmake_minimum_required(VERSION 3.13)
project(example-grpc LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use local build gRPC and protobuf libraries
set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3p")
set(protobuf_DIR "${EXTERNAL_DIR}/lib64/cmake/protobuf/")
set(gRPC_DIR "${EXTERNAL_DIR}/lib/cmake/grpc")

message("protobuf_DIR: ${protobuf_DIR}")
message("gRPC_DIR: ${gRPC_DIR}")

# Configure compiler options
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror -static)
endif()

# set(CMAKE_VERBOSE_MAKEFILE ON)

# Add include folders
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Include subfolders
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(proto)

# Formating and linting all related files
file(GLOB_RECURSE SRCS_AND_HDRS client/*.cpp client/*.h server/*.cpp server/*.h)
message(${SRCS_AND_HDRS})

# list(FILTER SRCS_AND_HDRS EXCLUDE REGEX "3p/")
find_program(CLANG_FORMAT NAMES clang-format)
add_custom_command(
  OUTPUT .fmt_cpp_stamp
  DEPENDS ${SRCS_AND_HDRS}
  COMMAND ${CLANG_FORMAT} -i ${SRCS_AND_HDRS}
  COMMAND touch .fmt_cpp_stamp
  COMMENT "Format C++ files with clang-format."
  VERBATIM)

file(GLOB CMAKE_FILES CMakeLists.txt client/CMakeLists.txt proto/CMakeLists.txt
     server/CMakeLists.txt)
find_program(CMAKE_FORMAT NAMES cmake-format)
if(${CMAKE_FORMAT} STREQUAL "CMAKE_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND touch .fmt_cmake_stamp
    COMMENT "Skip formatting CMake files."
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
    COMMENT "Skip formatting Bash scripts."
    VERBATIM)
else()
  if(UNIX AND NOT APPLE)
    add_custom_command(
      OUTPUT .fmt_bash_stamp
      DEPENDS ${SH_SRCS}
      COMMAND ${SHFMT} -i 2 -ci -w ${SH_SRCS}
      COMMAND touch .fmt_bash_stamp
      COMMENT "Format Bash scripts with shfmt."
      VERBATIM)
  else()
    add_custom_command(
      OUTPUT .fmt_bash_stamp
      DEPENDS ${SH_SRCS}
      COMMAND touch .fmt_bash_stamp
      COMMENT "Skip formatting Bash scripts."
      VERBATIM)
  endif()
endif()

add_custom_target(
  fmt
  DEPENDS .fmt_bash_stamp .fmt_cpp_stamp .fmt_cmake_stamp
  COMMENT "Format Bash, C++, and CMake files.")

add_custom_command(
  OUTPUT .lint_shellcheck_stamp
  DEPENDS ${SH_SRCS}
  COMMAND shellcheck ${SH_SRCS}
  COMMAND touch .lint_shellcheck_stamp
  COMMENT "Lint Bash files with shellcheck.")

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
