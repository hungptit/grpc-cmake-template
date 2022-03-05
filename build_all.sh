#!/bin/bash
config=${1:-"Release"}
echo "Build config: $config"

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

# Download required projects
cmake . -DCMAKE_BUILD_TYPE="$config" -DCMAKE_CXX_COMPILER=clang++ >/dev/null

# Build gRPC
./scripts/build_grpc.sh >/dev/null

# Configure the project
cmake . -DCMAKE_BUILD_TYPE="$config" -DCMAKE_CXX_COMPILER=clang++

# Build all examples
make "-j$number_of_cores" >/dev/null
