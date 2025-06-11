#!/usr/bin/env bash

# 获取项目根目录
MONITOR_HOME_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

# 设置默认 DISPLAY
display=""
if [ -z "${DISPLAY}" ];then
    display=":1"
else
    display="${DISPLAY}"
fi

# 设置 PROJECT_DIR 变量
PROJECT_DIR="${MONITOR_HOME_DIR}"

# 获取主机信息
local_host="$(hostname)"
user="${USER}"
uid="$(id -u)"
group="$(id -g -n)"
gid="$(id -g)"

# 确保 XDG_RUNTIME_DIR 存在
if [ -z "${XDG_RUNTIME_DIR}" ]; then
    XDG_RUNTIME_DIR="/run/user/${uid}"
fi

# 创建运行时目录（如果不存在）
mkdir -p "${XDG_RUNTIME_DIR}"

# 定义容器名称
CONTAINER_NAME="linux_monitor"
# 检查容器是否存在
if docker inspect --format='{{.Id}}' "${CONTAINER_NAME}" > /dev/null 2>&1; then
    echo "Stopping and removing existing container..."
    docker stop "${CONTAINER_NAME}" > /dev/null
    docker rm -v -f "${CONTAINER_NAME}" > /dev/null
fi

# 启动新容器
echo "启动新容器..."
docker run -it -d \
    --name ${CONTAINER_NAME} \
    --privileged=true \
    -p 2222:22 \
    -e DISPLAY="${display}" \
    -e DOCKER_USER="${user}" \
    -e USER="${user}" \
    -e DOCKER_USER_ID="${uid}" \
    -e DOCKER_GRP="${group}" \
    -e DOCKER_GRP_ID="${gid}" \
    -e XDG_RUNTIME_DIR="${XDG_RUNTIME_DIR}" \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v "${PROJECT_DIR}:/work" \
    -v "${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR}" \
    --net host \
    linux1:monitor1

# 检查容器是否成功启动
if [ $(docker ps -q -f name=${CONTAINER_NAME} | wc -l) -eq 1 ]; then
    echo "容器已成功启动: ${CONTAINER_NAME}"
else
    echo "容器启动失败!"
    exit 1
fi