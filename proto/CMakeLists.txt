set(CMAKE_VERBOSE_MAKEFILE ON)
find_package(Threads)

# gRPC
FetchContent_Declare(
  grpc
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG v1.35.0)
set(FETCHCONTENT_QUIET OFF)

set(ABSL_ENABLE_INSTALL OFF)
set(gRPC_PROTOBUF_PACKAGE_TYPE module)
set(gRPC_PROTOBUF_PROVIDER module)
FetchContent_MakeAvailable(grpc)

set(PROTO_FILES address.proto addressbook.proto healthcheck.proto
  helloworld.proto keyvaluestore.proto)

# Add Library target with protobuf sources
add_library(address ${PROTO_FILES})
target_link_libraries(address PUBLIC protobuf::libprotobuf grpc++)
target_include_directories(address PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Generate protobuf and grpc C++ files
get_target_property(grpc_cpp_plugin_location grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET address LANGUAGE cpp)
protobuf_generate(TARGET
  address LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN
  "protoc-gen-grpc=${grpc_cpp_plugin_location}")

# Generate protobuf and grpc Python files
get_target_property(grpc_python_plugin_location gRPC::grpc_python_plugin
  LOCATION)
protobuf_generate(TARGET address LANGUAGE python)
protobuf_generate(
  TARGET address LANGUAGE grpc GENERATE_EXTENSIONS .py PLUGIN
  "protoc-gen-grpc=${grpc_python_plugin_location}")
