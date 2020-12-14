#!/bin/bash

# Update the grpc submodule
git submodule update --init

pushd 3p || exit

# Update grpc
pushd src/grpc || exit
git submodule update --init
popd || exit

# We need to disable ABSL installation because of this issue https://github.com/grpc/grpc/issues/24976
./build_using_cmake.sh grpc -DABSL_ENABLE_INSTALL=OFF -DgRPC_PROTOBUF_PACKAGE_TYPE=module -DgRPC_PROTOBUF_PROVIDER=module

popd || exit
