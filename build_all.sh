#!/bin/bash
pushd 3p || exit

# Update grpc
pushd src/grpc || exit
git submodule update
git pull
popd || exit

# Build grpc
# We need to disable ABSL installation because of this issue https://github.com/grpc/grpc/issues/24976
./build_using_cmake.sh grpc -DABSL_ENABLE_INSTALL=OFF

popd || exit
