FROM ubuntu:20.04

# 配置apt，删除软件包和配置软件源
RUN apt-get clean && apt-get autoclean

COPY apt/sources.list /etc/apt/

# 设置默认的shell位置
SHELL ["/bin/bash", "-c"]

# 配置软件源并更新系统
COPY apt/sources.list /etc/apt/
RUN apt-get clean && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
        htop \
        apt-utils \
        curl \
        cmake \
        gdb \
        git \
        openssh-server \
        build-essential \
        libboost-all-dev \
        net-tools \
        vim \
        stress \
        libc-ares-dev \
        libssl-dev \
        python3-dev \
        python3-pip && \
    # 清理缓存以减小镜像体积
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# 复制并安装依赖
COPY install/ /tmp/install/

# 安装Protobuf
RUN cd /tmp/install/protobuf && \
    ./install_protobuf.sh && \
    cd / && \
    rm -rf /tmp/install/protobuf

# 安装Abseil
RUN cd /tmp/install/abseil && \
    ./install_abseil.sh && \
    cd / && \
    rm -rf /tmp/install/abseil

# 安装gRPC
RUN cd /tmp/install/grpc && \
    ./install_grpc.sh && \
    cd / && \
    rm -rf /tmp/install/grpc

# 安装CMake（如果需要覆盖系统版本）
RUN cd /tmp/install/cmake && \
    ./install_cmake.sh && \
    cd / && \
    rm -rf /tmp/install/cmake

# 安装Google Test
RUN cd /tmp/install/gtest && \
    ./install_gtest.sh && \
    cd / && \
    rm -rf /tmp/install/gtest

# 安装 install/qt /tmp/install/qt
RUN cd /tmp/install/qt && \
    ./install_qt.sh && \
    cd / && \
    rm -rf /tmp/install/qt