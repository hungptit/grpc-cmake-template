#!/bin/bash -ex
# Download required projects
cmake . >/dev/null

# Format and lint source files
make format
make lint

# Build gRPC
local_dir="$PWD/.local"
rm -rf "$local_dir"

./scripts/build_grpc.sh Release >/dev/null
./scripts/build_grpc.sh Debug >/dev/null
