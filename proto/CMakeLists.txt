set(EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/3p")
if(UNIX AND NOT APPLE)
  set(protobuf_DIR "${EXTERNAL_DIR}/lib64/cmake/protobuf/")
elseif(APPLE)
  set(protobuf_DIR "${EXTERNAL_DIR}/lib64/cmake/protobuf/")
elseif(MSVC)
  set(protobuf_DIR "${EXTERNAL_DIR}/cmake/")
else()
  message(FATAL_ERROR "This platform is unsupported. CMake will exit.")
endif()
set(gRPC_DIR "${EXTERNAL_DIR}/lib/cmake/grpc")

find_package(protobuf CONFIG REQUIRED NO_DEFAULT_PATH)
find_package(gRPC CONFIG REQUIRED NO_DEFAULT_PATH)
find_package(Threads)

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
get_target_property(grpc_python_plugin_location grpc::grpc_python_plugin
  LOCATION)
protobuf_generate(TARGET address LANGUAGE python)
protobuf_generate(
  TARGET address LANGUAGE grpc GENERATE_EXTENSIONS .py PLUGIN
  "protoc-gen-grpc=${grpc_python_plugin_location}")
