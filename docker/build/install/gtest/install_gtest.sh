#!/usr/bin/env bash

set -e

cd "$(dirname "${BASH_SOURCE[0]}")"

# 定义版本和包名（可根据需要调整版本号）
VERSION="1.15.0"
PKG_NAME="googletest-${VERSION}.tar.gz"

# 解压安装包（需提前将gtest包放在同目录或通过wget下载）
tar xzf "${PKG_NAME}"

# 进入源码目录并构建
pushd "googletest-${VERSION}"
mkdir -p build && cd build

# CMake 配置（根据需求调整选项）
cmake .. \
    -DBUILD_SHARED_LIBS=ON \          # 构建共享库（可选，若需静态库设为OFF）
    -DBUILD_GMOCK=OFF \               # 不构建GMock（若需要GMock设为ON）
    -Dgtest_build_tests=OFF \         # 不构建gtest自身测试用例
    -DCMAKE_INSTALL_PREFIX=/usr/local \  # 安装路径
    -DCMAKE_BUILD_TYPE=Release         # 发布模式构建

# 编译并安装（使用nproc获取CPU核心数加速编译）
make -j$(nproc)
make install

# 更新动态链接库缓存（仅共享库需要）
ldconfig

# 返回原目录
popd

# 清理临时文件（原压缩包和解压目录）
rm -rf "${PKG_NAME}" "googletest-${VERSION}"
    