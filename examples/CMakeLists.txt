cmake_minimum_required(VERSION 3.18)
project(grpc-cmake-template LANGUAGES CXX)

# Enable ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_ALL_WARNINGS ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(POSITION_INDEPENDENT_CODE OFF)

# Add include folders
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Include subfolders
add_subdirectory(proto)
add_subdirectory(client)
add_subdirectory(server)

# Formating and linting all related files
file(GLOB_RECURSE SRCS_AND_HDRS client/*.cpp client/*.h server/*.cpp)
find_program(CLANG_FORMAT NAMES clang-format)
if(${CLANG_FORMAT} STREQUAL "CLANG_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_cpp_stamp
    DEPENDS ${SRCS_AND_HDRS}
    COMMAND echo "Could not find clang-format. Skip formating C++ file"
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

add_custom_target(
  format
  DEPENDS .fmt_cpp_stamp .fmt_cmake_stamp
  COMMENT "Format C++ and CMake files.")
