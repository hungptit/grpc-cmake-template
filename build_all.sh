#!/bin/bash
# Buil gRPC and examples automatically.

# Update the grpc submodule
git submodule update --init --recursive

pushd 3p || exit

# Compile and install gRPC
# We need to disable ABSL installation because of this issue https://github.com/grpc/grpc/issues/24976
./build_using_cmake.sh grpc -DABSL_ENABLE_INSTALL=OFF -DgRPC_PROTOBUF_PACKAGE_TYPE=module -DgRPC_PROTOBUF_PROVIDER=module

# Build and install quill
./build_using_cmake.sh quill -DQUILL_FMT_EXTERNAL=OFF

popd || exit

# Build all examples
cmake ./
make -k
