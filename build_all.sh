#!/bin/bash
# Buil gRPC and examples automatically.

# Update the grpc submodule
git submodule update --init --recursive

# Compile and install gRPC
# We need to disable ABSL installation because of this issue https://github.com/grpc/grpc/issues/24976
pushd 3p || exit
./build_using_cmake.sh grpc -DCMAKE_BUILD_TYPE=Debug  -DABSL_ENABLE_INSTALL=OFF -DgRPC_PROTOBUF_PACKAGE_TYPE=module -DgRPC_PROTOBUF_PROVIDER=module
popd || exit

# Build all examples
rm -f CMakeCache.txt 
cmake ./
make -k
