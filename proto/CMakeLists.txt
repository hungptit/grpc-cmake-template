# Proto file
get_filename_component(hw_proto "helloworld.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "helloworld.pb.cc")
set(hw_proto_hdrs "helloworld.pb.h")
set(hw_grpc_srcs "helloworld.grpc.pb.cc")
set(hw_grpc_hdrs "helloworld.grpc.pb.h")

set(PROTOC "protoc")
set(_GRPC_CPP_PLUGIN_EXECUTABLE )

find_program(GRPC_CPP_PLUGIN name  grpc_cpp_plugin PATHS "../_deps/grpc-build/")
find_program(PROTOC name protoc PATHS "../_deps/grpc-build/third_party/protobuf")

message("${GRPC_CPP_PLUGIN}")

add_custom_command(
  OUTPUT .proto_stamp
  COMMAND ${PROTOC}
  ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}"
  --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}"
  -I "${hw_proto_path}"
  --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}"
  "${hw_proto}"
  DEPENDS "${hw_proto}")

add_custom_target(
  proto
  DEPENDS .proto_stamp
  COMMENT "Format C++ and CMake files.")
