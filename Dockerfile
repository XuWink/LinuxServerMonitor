# basic image
FROM  ubuntu:18.04

# no interaction
ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Shanghai

  
#clean
RUN apt-get clean && \
    apt-get autoclean

COPY apt/sources.list /etc/apt/

# basic ubuntu software package
RUN apt-get update  && apt-get upgrade -y  && \
    apt-get install -y \
    htop \
    apt-utils \
    curl \
    cmake \
    git \
    openssh-server \
    build-essential \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qtbase5-dev-tools \
    libboost-all-dev \
    net-tools \
    vim \
    stress 


# grpc googletest
RUN apt-get install -y libc-ares-dev  libssl-dev gcc g++ make libgtest-dev
# qt GUI lib   xhost
RUN apt-get install -y  \
    libx11-xcb1 \
    libfreetype6 \
    libdbus-1-3 \
    libfontconfig1 \
    libxkbcommon0   \
    libxkbcommon-x11-0

# python for cuteci
RUN apt-get install -y python-dev \
    python3-dev \
    python-pip \
    python-all-dev 


# COPY from  host to  container  && RUN
COPY install/protobuf /tmp/install/protobuf
RUN /tmp/install/protobuf/install_protobuf.sh

COPY install/abseil /tmp/install/abseil
RUN /tmp/install/abseil/install_abseil.sh

COPY install/grpc /tmp/install/grpc
RUN /tmp/install/grpc/install_grpc.sh

# COPY install/gtest /tmp/install/gtest
# RUN /tmp/install/grpc/install_gtest.sh
