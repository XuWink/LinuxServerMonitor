#include "CpuInfoMonitor.hpp"
#include "monitor.grpc.pb.h"
#include "RpcClient.hpp"

#include <atomic>
#include <cstdlib>
#include <memory>
#include <thread>

std::atomic<bool> g_running{ true };

void SignalHandler(int) {
    g_running = false;
}

void RunMonitor() {
    monitor::RpcClient rpc_client;
    const char *       user      = getenv("USER");
    const std::string  user_name = user ? user : "unknown";

    std::vector<std::shared_ptr<monitor::MonitorBase>> runners;
    runners.emplace_back(std::make_shared<monitor::CpuInfoMonitor>());

    // 注册信号处理（可选）
    signal(SIGINT, SignalHandler);
    signal(SIGTERM, SignalHandler);

    while (g_running) {
        monitor::proto::MonitorInfo monitor_info;
        monitor_info.set_name(user_name);

        try {
            for (auto & runner : runners) {
                runner->UpdateOnce(&monitor_info);
            }

            // 同步到服务器
            rpc_client.SetMonitorInfo(monitor_info);

        } catch (const std::exception & e) {
            std::cerr << "Error in monitoring loop: " << e.what() << std::endl;
        }

        if (g_running) {  // 避免最后一次不必要的等待
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}

int main() {
    std::thread monitor_thread(RunMonitor);
    monitor_thread.join();  // 等待线程退出（通过信号或异常）
    return EXIT_SUCCESS;
}
