FROM ubuntu:22.04

# 非交互方式模式构建（非全局，仅限当前文件中的RUN命令）
ENV TZ=Asia/Shanghai \
    DEBIAN_FRONTEND=noninteractive

COPY apt/sources.list /etc/apt/

# 使用bash作为默认shell并启用严格模式（可选增强）
SHELL ["/bin/bash", "-euo", "pipefail", "-c"]

# 更新 apt-get，并安装一些必要的、基础包
RUN apt-get update && \
    # 移除不必要的upgrade（镜像构建建议固定依赖版本）
    apt-get install -y --no-install-recommends \
        # 系统工具
        htop net-tools vim curl \
        # 开发工具链
        build-essential cmake git \
        # 网络相关
        openssh-server libc-ares-dev libssl-dev \
        # Qt依赖（根据实际项目需求调整）
        qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools \
        # Boost库（建议指定具体子库代替all-dev）
        libboost-system-dev libboost-thread-dev \
        # 运行时依赖（图形相关库）
        libx11-xcb1 libfreetype6 libdbus-1-3 \
        libfontconfig1 libxkbcommon0 libxkbcommon-x11-0 \
        # Python3开发环境（移除Python2相关包）
        python3-dev python3-pip && \
    # 清理优化
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# 安装第三方库（添加执行权限检查）
COPY install/ /tmp/install/
RUN chmod -R +x /tmp/install && \
    /tmp/install/protobuf/install_protobuf.sh && \
    /tmp/install/abseil/install_abseil.sh && \
    /tmp/install/abseil/install_grpc.sh && \
    /tmp/install/abseil/install_gtest.sh && \
    rm -rf /tmp/install

# Python环境优化（升级pip并清理缓存）
RUN python3 -m pip install --upgrade pip && \
    python3 -m pip cache purge

# SSH服务配置（添加基础启动配置）
RUN mkdir -p /var/run/sshd && \
    # 禁用DNS查找加速连接
    echo "UseDNS no" >> /etc/ssh/sshd_config && \
    # 允许root登录（根据安全需求调整）
    echo "PermitRootLogin yes" >> /etc/ssh/sshd_config

# 设置工作目录
WORKDIR /app
 
# 暴露 SSH 端口（如果需要远程连接）
EXPOSE 22

# 启动命令（建议使用数组格式）
CMD ["/usr/sbin/sshd", "-D"]