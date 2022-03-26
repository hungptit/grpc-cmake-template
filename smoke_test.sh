#!/bin/bash  -ex
build_mode=${1-Release}
project_dir="$PWD"
clang_compiler="clang++"
example_dir="$project_dir/examples/"
pushd "$example_dir" || exit
git clean -df
cmake -DCMAKE_CXX_COMPILER="$clang_compiler" -DCMAKE_BUILD_TYPE="$build_mode" -DSTEM="$build_mode"
make -j3
popd || exit
