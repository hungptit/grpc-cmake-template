cmake_minimum_required(VERSION 3.15)
project(build-grpc LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  grpc
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG master)
set(FETCHCONTENT_QUIET OFF)
set(ABSL_ENABLE_INSTALL OFF)
set(gRPC_PROTOBUF_PACKAGE_TYPE module)
set(gRPC_PROTOBUF_PROVIDER module)
FetchContent_Populate(grpc)
# FetchContent_MakeAvailable(grpc)

