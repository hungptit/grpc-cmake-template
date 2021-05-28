#!/bin/bash
config=${1:"Release"}
cmake ./ -DCMAKE_BUILD_TYPE=$config -DCMAKE_INSTALL_PREFIX=$PWD
make -j9
make install

