#!/usr/bin/env bash

CONTAINER_NAME="linux_monitor"

# start GUI
xhost +local:root 1>/dev/null 2>&1
docker exec \
    -u root \
    -it ${CONTAINER_NAME} \
    /bin/bash

# close GUI
xhost -local:root 1>/dev/null 2>&1