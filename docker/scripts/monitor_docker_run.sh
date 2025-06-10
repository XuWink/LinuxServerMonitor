#!/usr/bin/env bash

# /home/xxx/LinuxServerMonitor/   -v   /work
# 向上两级
PROJECT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

display=""
if [ -z ${DISPLAY} ];then
    display=":1"
else
    display="${DISPLAY}"
fi

# get host info
local_host="$(hostname)"
user="${USER}"
uid="$(id -u)"
group="$(id -g -n)"
gid="$(id -g)"

# 检查 XDG_RUNTIME_DIR 是否设置
if [ -z "${XDG_RUNTIME_DIR}" ]; then
    echo "Error: XDG_RUNTIME_DIR is not set."
    exit 1
fi

# 定义容器名称
CONTAINER_NAME="linux_monitor"
# 检查容器是否存在
if docker inspect --format='{{.Id}}' "${CONTAINER_NAME}" > /dev/null 2>&1; then
    echo "Stopping and removing existing container..."
    docker stop "${CONTAINER_NAME}" > /dev/null
    docker rm -v -f "${CONTAINER_NAME}" > /dev/null
fi

# 启动新容器
echo "Starting new container..."
docker run -it -d \
--name "${CONTAINER_NAME}" \
--privileged=true \
-p 2222:22 \ 
-e DISPLAY=${display} \
-e DOCKER_USER="${user}" \
-e USER="${user}" \
-e DOCKER_USER_ID="${uid}" \
-e DOCKER_GRP="${group}" \
-e DOCKER_GRP_ID="${gid}" \
-e XDG_RUNTIME_DIR=${XDG_RUNTIME_DIR} \
-v /tmp/.X11-unix:/tmp/.X11-unix \
-v ${PROJECT_DIR}:/work \
-v ${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR} \
--net host \
linux:monitor

echo "Container started: linux_monitor"