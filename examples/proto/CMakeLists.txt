if(MSVC)
  add_definitions(-D_WIN32_WINNT=0x600)
endif()

if (WIN32)
  set(GRPC_INSTALL_DIR "${PROJECT_SOURCE_DIR}/../.local/grpc/${STEM}/")
elseif(APPLE)
  set(GRPC_INSTALL_DIR "${PROJECT_SOURCE_DIR}/../.local/grpc/${STEM}/")
else()
  set(GRPC_INSTALL_DIR "${PROJECT_SOURCE_DIR}/../.local/grpc/${STEM}/")
endif()
message(${GRPC_INSTALL_DIR})

find_package(Threads REQUIRED)

# Configure the search paths.
if (APPLE)
  set(ABSL_PATH "${GRPC_INSTALL_DIR}/lib/cmake")
  set(PROTOBUF_PATH "${GRPC_INSTALL_DIR}/lib/cmake")
  set(GRPC_PATH "${GRPC_INSTALL_DIR}/lib/cmake")
elseif(WIN32)
  set(ABSL_PATH "${GRPC_INSTALL_DIR}/lib/cmake")
  set(PROTOBUF_PATH "${GRPC_INSTALL_DIR}/cmake")
  set(GRPC_PATH "${GRPC_INSTALL_DIR}/lib/cmake")
else()
  set(ABSL_PATH "${GRPC_INSTALL_DIR}/lib64/cmake")
  set(PROTOBUF_PATH "${GRPC_INSTALL_DIR}/lib64/cmake")
  set(GRPC_PATH "${GRPC_INSTALL_DIR}/lib/cmake")
endif()

find_package(absl CONFIG REQUIRED NO_DEFAULT_PATH PATHS ${ABSL_PATH})
find_package(protobuf CONFIG REQUIRED NO_DEFAULT_PATH PATHS ${PROTOBUF_PATH})
find_package(gRPC CONFIG REQUIRED NO_DEFAULT_PATH PATHS ${GRPC_PATH})

# Find all proto files in the current folder.
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.proto)

# Add Library target with protobuf sources
add_library(address STATIC ${PROTO_FILES})
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
