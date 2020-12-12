cmake_minimum_required(VERSION 3.13)
project(example-grpc LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set up the protobuf and gRPC search paths
set(protobuf_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3p/lib64/cmake/protobuf/")
set(gRPC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3p/lib/cmake/grpc")

message("protobuf_DIR: ${protobuf_DIR}")
message("gRPC_DIR: ${gRPC_DIR}")

# Configure compiler options
set(CMAKE_CXX_STANDARD 17)

# Add include folders
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Include subfolders
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(proto)
