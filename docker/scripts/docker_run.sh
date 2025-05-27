#!/usr/bin/env bash

docker run -d \
  --name my-dev-container \
  -p 2222:22 \
  -v $(pwd):/app \
  my-dev-env