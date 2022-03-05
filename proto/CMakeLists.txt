if(MSVC)
  add_definitions(-D_WIN32_WINNT=0x600)
endif()

find_package(Threads REQUIRED)
find_package(absl CONFIG REQUIRED NO_DEFAULT_PATH PATHS
             "${PROJECT_SOURCE_DIR}/.local/lib64/cmake")
find_package(protobuf CONFIG REQUIRED NO_DEFAULT_PATH PATHS
             "${PROJECT_SOURCE_DIR}/.local/lib64/cmake")
find_package(gRPC CONFIG REQUIRED NO_DEFAULT_PATH PATHS
             "${PROJECT_SOURCE_DIR}/.local/lib/cmake")

# Find all proto files in the current folder.
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)

# Add Library target with protobuf sources
add_library(address ${PROTO_FILES})
target_link_libraries(address PUBLIC protobuf::libprotobuf gRPC::grpc
                                     gRPC::grpc++)
target_include_directories(address PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Generate protobuf and grpc files
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET address LANGUAGE cpp)
protobuf_generate(
  TARGET
  address
  LANGUAGE
  grpc
  GENERATE_EXTENSIONS
  .grpc.pb.h
  .grpc.pb.cc
  PLUGIN
  "protoc-gen-grpc=${grpc_cpp_plugin_location}")
