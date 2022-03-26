#!/bin/bash
config=${1-"Release"}
root_dir="$PWD"

local_dir="$PWD/.local"
mkdir -p "$local_dir"

src_dir="$root_dir/_deps/grpc-src"
build_dir="$local_dir/build"
mkdir -p "$build_dir"

dst_dir="$root_dir/.local/grpc/$config"

# Get the number of cpu cores.
osType=$(uname)
case "$osType" in
  "Darwin")
    {
      number_of_cores=$(sysctl -n hw.ncpu)
    }
    ;;
  "Linux")
    {
      number_of_cores=$(grep -c ^processor /proc/cpuinfo)
    }
    ;;
  *)
    {
      echo "Unsupported OS, exiting"
      exit
    }
    ;;
esac

# Build grpc libraries
set -x
pushd "$build_dir" || exit
cmake "$src_dir" -DCMAKE_BUILD_TYPE="$config" -DCMAKE_INSTALL_PREFIX="$dst_dir" -DgRPC_PROTOBUF_PACKAGE_TYPE="module" -Dprotobuf_BUILD_LIBPROTOC=ON -DABSL_PROPAGATE_CXX_STD=ON -DBUILD_SHARED_LIBS=OFF -Dprotobuf_BUILD_SHARED_LIBS=OFF
make -j"$number_of_cores"
make install
popd || exit
