#include <gtest/gtest.h>

#include "RpcClient.hpp"

// TEST(RpcClientTest, SetMonitorInfo) {}

TEST(RpcClientTest, GetMonitorInfo) {
  monitor::RpcClient rpc_client;
  monitor::proto::MonitorInfo monitor_info;
  rpc_client.GetMonitorInfo(&monitor_info);
}