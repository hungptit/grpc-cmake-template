#!/bin/bash
config=${1:"Release"}
root_dir="$PWD"
local_dir="$PWD/.local"
src_dir="$root_dir/_deps/grpc-src"
build_dir="$local_dir/build"
dst_dir="$root_dir/.local"

# Build grpc libraries
mkdir -p "$build_dir"
pushd "$build_dir" || exit
cmake "$src_dir" -DCMAKE_BUILD_TYPE="$config" -DCMAKE_INSTALL_PREFIX="$dst_dir"  gRPC_PROTOBUF_PACKAGE_TYPE="Module"  protobuf_BUILD_LIBPROTOC=ON
make -j9
make install
popd || exit
