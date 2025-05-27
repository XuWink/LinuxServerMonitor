#!/usr/bin/env bash

# 删除容器 删除镜像
docker stop my-dev-container
docker rm my-dev-container
docker rmi my-dev-env