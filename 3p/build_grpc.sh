#!/bin/bash
config=${1:"Release"}
root_dir="$PWD"
src_dir="$root_dir/_deps/grpc-src"
dst_dir="$root_dir/.local"
cmake ./ -DCMAKE_BUILD_TYPE="$config" -DCMAKE_INSTALL_PREFIX="$dst_dir"
make -j9
make install

