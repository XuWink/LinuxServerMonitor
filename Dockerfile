FROM ubuntu:22.04

# 设置环境变量
ENV DEBIAN_FRONTEND=noninteractive

# 更新软件源并升级系统
COPY docker/build/apt/sources.list /etc/apt/

# 安装系统工具和开发库（合并RUN指令以减少镜像层）
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
        # 基础工具
        htop apt-utils curl cmake git openssh-server \
        # 编译工具链
        build-essential \
        # Qt 开发工具
        qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools \
        # 开发库
        libboost-all-dev libc-ares-dev libssl-dev \
        # 网络工具
        net-tools iproute2 \
        # 系统工具
        vim stress \
        # X11 和 GUI 相关库
        libx11-xcb1 libfreetype6 libdbus-1-3 libfontconfig1 \
        libxkbcommon0 libxkbcommon-x11-0 \
        # Python 3 开发工具
        python3-dev python3-pip && \
    # 清理缓存以减小镜像体积
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# 安装 Protobuf、Abseil 和 gRPC、gtest
# 假设这些安装脚本已经针对 Ubuntu 22.04 进行了适配
COPY docker/build/install/protobuf /tmp/install/protobuf
COPY docker/build/install/abseil /tmp/install/abseil
COPY docker/build/install/grpc /tmp/install/grpc
COPY docker/build/install/gtest /tmp/install/gtest

RUN cd /tmp/install/grpc && ./install_grpc.sh && \
    cd /tmp/install/protobuf && ./install_protobuf.sh && \
    cd /tmp/install/abseil && ./install_abseil.sh && \
    cd /tmp/install/gtest && ./install_gtest.sh && \
    # 清理安装文件
    rm -rf /tmp/install/protobuf /tmp/install/abseil /tmp/install/grpc /tmp/install/gtest && \
    rm -rf /tmp/*

# 设置时区（Ubuntu 22.04 需要额外步骤）
RUN ln -fs /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && \
    dpkg-reconfigure -f noninteractive tzdata

# # 可选：设置工作目录
# WORKDIR /workspace

# # 可选：设置默认命令
CMD ["/bin/bash"]

# docker build -t linux:monitor .