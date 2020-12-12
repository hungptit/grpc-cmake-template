#!/bin/bash
set -euo pipefail # Use Bash strict mode

PKGNAME=$1
CMAKE_OPTIONS=${*:2}

# shellcheck disable=SC1090
source "${PWD}/get_build_options.sh"

APKG_SRC=$SRC_DIR/$PKGNAME
APKG_BUILD_FOLDER=$TMP_DIR/$PKGNAME
APKG_PREFIX=$PREFIX

echo "Src folder: " "$APKG_SRC"
echo "Build folder: " "$APKG_BUILD_FOLDER"
echo "Prefix folder: " "$APKG_PREFIX"

# Build a given package
# shellcheck disable=SC2115
rm -rf "$APKG_BUILD_FOLDER"

# shellcheck disable=SC2115
mkdir -p "$APKG_BUILD_FOLDER"

pushd "$APKG_BUILD_FOLDER"
set -x

# shellcheck disable=SC2086
$CMAKE "$APKG_SRC" -DCMAKE_INSTALL_PREFIX="$APKG_PREFIX" $CMAKE_OPTIONS

make "$BUILD_OPTS"
make install
set +x
# Return to the original folder.
popd

# Cleanup build folder
# shellcheck disable=SC2115
rm -rf "$APKG_BUILD_FOLDER"
