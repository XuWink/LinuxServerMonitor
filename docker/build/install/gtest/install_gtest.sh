#!/usr/bin/env bash

set -e

cd "$(dirname "${BASH_SOURCE[0]}")"

THREAD_NUM=$(nproc)

# Google Test version to install
VERSION="1.17.0"
PKG_NAME="googletest-${VERSION}.tar.gz"
RELEASE_URL="https://github.com/google/googletest/releases/download/v${VERSION}/${PKG_NAME}"

# Download and install gtest
echo "Downloading Google Test version ${VERSION}..."
wget -q "${RELEASE_URL}" -O "${PKG_NAME}" || {
    echo "Failed to download Google Test"
    exit 1
}

tar xzf "${PKG_NAME}"
pushd "googletest-${VERSION}"

mkdir build && cd build

cmake .. \
    -DCMAKE_INSTALL_PREFIX:PATH="/usr/local" \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON

make -j${THREAD_NUM}
sudo make install

popd

# Clean up
rm -rf "${PKG_NAME}" "googletest-${VERSION}"

echo "Google Test ${VERSION} installed successfully!"