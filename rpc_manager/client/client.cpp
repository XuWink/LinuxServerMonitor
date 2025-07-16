#include <thread>
#include <vector>
#include "RpcClientManager.hpp"

int main() {
  monitor::RpcClientManager manager;

  // 定义多个 target
  std::vector<std::string> targets = {"localhost:50051", "server2:50051",
                                      "server3:50051"};

  // 并发调用不同 target 的客户端
  std::vector<std::thread> threads;
  for (const auto& target : targets) {
    threads.emplace_back([&manager, target]() {
      monitor::proto::MonitorInfo monitor_info;
      auto rpc_client = manager.GetClient(target);
      rpc_client->SetMonitorInfo(monitor_info);
    });
  }

  for (auto& t : threads) t.join();

  return 0;
}