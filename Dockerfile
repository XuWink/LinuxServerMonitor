# Basic image
FROM ubuntu:22.04

# Environment configuration
ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Shanghai

# Configure apt sources
COPY docker/tools/apt/sources.list /etc/apt/

# Install all packages in a single RUN layer to minimize image size
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
    # Basic tools
    htop \
    apt-utils \
    curl \
    cmake \
    git \
    gdb \
    openssh-server \
    build-essential \
    net-tools \
    vim \
    stress \
    software-properties-common \
    # Qt development
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qtbase5-dev-tools \
    libboost-all-dev \
    # gRPC and dependencies
    libc-ares-dev \
    libssl-dev \
    # 字体
    fonts-wqy-microhei \
    gcc \
    g++ \
    make \
    libgtest-dev \
    libbenchmark-dev \
    # libprotobuf-dev \
    # protobuf-compiler \
    # libgrpc++-dev \
    # grpc-dev \
    # libgrpc-dev \
    # libgrpc++1 \
    # Qt GUI dependencies
    libx11-xcb1 \
    libfreetype6 \
    libdbus-1-3 \
    libfontconfig1 \
    libxkbcommon0 \
    libxkbcommon-x11-0 \
    # Python development
    python3-dev \
    python3-pip \
    python3-all-dev && \
    # Clean up
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY docker/tools/install/protobuf /tmp/install/protobuf
RUN chmod +x /tmp/install/protobuf/install_protobuf.sh && \
    /tmp/install/protobuf/install_protobuf.sh
    
COPY docker/tools/install/abseil /tmp/install/abseil
RUN chmod +x /tmp/install/abseil/install_abseil.sh && \
    /tmp/install/abseil/install_abseil.sh
    
COPY docker/tools/install/grpc /tmp/install/grpc
RUN chmod +x /tmp/install/grpc/install_grpc.sh && \
    /tmp/install/grpc/install_grpc.sh
