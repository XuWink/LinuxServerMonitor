FROM  ubuntu:18.04

# 设置环境变量
ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Shanghai

# 更新软件源并升级系统
COPY apt/sources.list /etc/apt/
RUN apt-get update && \
    apt-get upgrade -y && \
    # 安装基础工具
    apt-get install -y --no-install-recommends \
        htop \                     # 进程监控工具
        apt-utils \                # APT 工具包
        curl \                     # 数据传输工具
        cmake \                    # 跨平台构建工具
        git \                      # 版本控制系统
        openssh-server \           # SSH 服务器
        mkdir -p /var/run/sshd && \
        echo 'root:xuwenke' | chpasswd && \  # 设置 root 密码（生产环境请使用密钥认证）
        sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

        build-essential \          # 编译工具链（gcc, g++, make 等）
        # Qt 开发工具
        qtbase5-dev \              # Qt 基础库开发文件
        qtchooser \                # Qt 版本选择工具
        qt5-qmake \                # Qt 项目构建工具
        qtbase5-dev-tools \        # Qt 基础开发工具
        # 开发库
        libboost-all-dev \         # Boost C++ 库（全部组件）
        libc-ares-dev \            # c-ares 异步 DNS 解析库
        libssl-dev \               # OpenSSL 开发文件
        # 网络工具
        net-tools \                # 网络工具集（ifconfig, netstat 等）
        # 系统工具
        vim \                      # 文本编辑器
        stress \                   # 系统压力测试工具
        # X11 和 GUI 相关库
        libx11-xcb1 \              # X11 客户端库
        libfreetype6 \             # FreeType 字体渲染库
        libdbus-1-3 \              # D-Bus 系统消息总线库
        libfontconfig1 \           # 字体配置库
        libxkbcommon0 \            # XKB 键盘映射库
        libxkbcommon-x11-0 \       # X11 键盘映射支持
        # Python 3 开发工具
        python3-dev \              # Python 3 开发文件
        python3-pip \              # Python 3 包管理工具
    # 清理缓存以减小镜像体积
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# 安装 Protobuf、Abseil 和 gRPC
COPY install/protobuf /tmp/install/protobuf
COPY install/abseil /tmp/install/abseil
COPY install/grpc /tmp/install/grpc
RUN cd /tmp/install/protobuf && ./install_protobuf.sh && \
    cd /tmp/install/abseil && ./install_abseil.sh && \
    cd /tmp/install/grpc && ./install_grpc.sh && \
    rm -rf /tmp/install/protobuf /tmp/install/abseil /tmp/install/grpc && \
    rm -rf /tmp/*

EXPOSE 22  # 暴露 SSH 端口

