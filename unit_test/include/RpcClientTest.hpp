#include "RpcClient.hpp"

#include <gtest/gtest.h>

// TEST(RpcClientTest, SetMonitorInfo) {}

TEST(RpcClientTest, GetMonitorInfo) {
    monitor::RpcClient          rpc_client;
    monitor::proto::MonitorInfo monitor_info;

    // Call the method under test
    rpc_client.GetMonitorInfo(&monitor_info);

    // Verify the MonitorInfo fields are populated
    ASSERT_TRUE(monitor_info.has_cpu_info());
    ASSERT_TRUE(monitor_info.cpu_info().has_name());
    ASSERT_TRUE(monitor_info.cpu_info().has_model_name());
    ASSERT_TRUE(monitor_info.cpu_info().has_mhz());

    // Verify memory info if applicable
    if (monitor_info.has_memory_info()) {
        ASSERT_GT(monitor_info.memory_info().total_memory(), 0);
        ASSERT_GT(monitor_info.memory_info().used_memory(), 0);
    }

    // Verify disk info if applicable
    if (monitor_info.has_disk_info()) {
        ASSERT_GT(monitor_info.disk_info().total_space(), 0);
        ASSERT_GT(monitor_info.disk_info().used_space(), 0);
    }
}
