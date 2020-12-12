find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Threads)

# Protobuf/Grpc source files
set(PROTO_FILES
    protos/address.proto
    protos/addressbook.proto
)

# Add Library target with protobuf sources
add_library(address ${PROTO_FILES})
target_link_libraries(address
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)
target_include_directories(address PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Generate protobuf and grpc files
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET address LANGUAGE cpp)
protobuf_generate(TARGET address LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")
