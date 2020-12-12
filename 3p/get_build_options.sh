#!/bin/bash
set -euo pipefail # Use Bash strict mode

ROOT_DIR="$PWD"
SRC_DIR=$ROOT_DIR/src
TMP_DIR=/tmp/build/
PREFIX=$ROOT_DIR
mkdir -p $TMP_DIR

osType=$(uname)
case "$osType" in
  "Darwin")
    {
      NCPUS=$(sysctl -n hw.ncpu)
      BUILD_OPTS=-j$((NCPUS + 1))
    }
    ;;
  "Linux")
    {
      NCPUS=$(grep -c ^processor /proc/cpuinfo)
      BUILD_OPTS=-j$((NCPUS + 1))
    }
    ;;
  *)
    {
      echo "Unsupported OS, exiting"
      exit
    }
    ;;
esac

# Setup git
GIT=$PREFIX/bin/git
if [ ! -f "$GIT" ]; then
  # Use system CMake if we could not find the customized CMake.
  GIT=git
fi

# Setup CMake
CMAKE=$PREFIX/bin/cmake
if [ ! -f "$CMAKE" ]; then
  # Use system CMake if we could not find the customized CMake.
  CMAKE=cmake
fi

# Display build configurations
printf "========= Build configuration =========\n"
printf "ROOT_DIR: %s\n" "$ROOT_DIR"
printf "SRC_DIR: %s\n" "$SRC_DIR"
printf "ROOT_DIR: %s\n" "$ROOT_DIR"
printf "TMP_DIR: %s\n" "$TMP_DIR"
printf "BUILD_OPTS: %s\n" "$BUILD_OPTS"
printf "CMAKE: %s\n" "$CMAKE"
printf "GIT: %s\n" "$GIT"
printf "CMAKE: %s\n" "$CMAKE"
printf "=======================================\n"
