#include "RpcServer.hpp"

namespace monitor {

RpcServer::RpcServer() {}
RpcServer::~RpcServer() {}

// 客户端调用SetMonitorInfo函数更新monitor_infos_
Status RpcServer::SetMonitorInfo(ServerContext* context,
                                 const MonitorInfo* request, Empty* response) {
  monitor_infos_.Clear();
  monitor_infos_ = *request;

  std::string client_ip = getClientIP(context);

  // 2. 关联客户端IP与CPU信息（线程安全）
  {
    std::lock_guard<std::mutex> lock(clients_mutex_);
    clients_[client_ip] = *request;  // 深拷贝MonitorInfo
  }

  return Status::OK;
}

Status RpcServer::GetMonitorInfo(ServerContext* context, const Empty* request,
                                 MonitorInfo* response) {
  *response = monitor_infos_;

  return Status::OK;
}

std::string RpcServer::getClientIP(ServerContext* context) const {
  // 获取Peer信息（格式通常为 "ipv4:192.168.1.1:54321" 或 "ipv6:[::1]:54321"）
  std::string peer = context->peer();

  // 解析IP地址部分
  size_t pos = peer.find(':');
  if (pos != std::string::npos) {
    std::string protocol = peer.substr(0, pos);
    if (protocol == "ipv4") {
      // 提取ipv4地址（格式："ipv4:192.168.1.1:54321"）
      size_t start = pos + 1;
      size_t end = peer.rfind(':');
      if (end != std::string::npos && end > start) {
        return peer.substr(start, end - start);
      }
    } else if (protocol == "ipv6") {
      // 提取ipv6地址（格式："ipv6:[::1]:54321"）
      size_t start = pos + 2;  // 跳过"[", 如 "[::1]"
      size_t end = peer.rfind(']');
      if (end != std::string::npos && end > start) {
        return peer.substr(start, end - start);
      }
    }
  }

  return peer;  // 无法解析时返回原始Peer信息
}

Status RpcServer::GetAllMonitorInfo(ServerContext* context,
                                    const Empty* request,
                                    monitor::proto::AllMonitorInfo* response) {
  std::lock_guard<std::mutex> lock(clients_mutex_);

  // 遍历并添加所有客户端的CPU信息
  for (const auto& pair : clients_) {
    auto monitor_info = response->add_monitor_infos();
    monitor_info->set_name(pair.first);

    // 遍历 pair.second 中的所有 CpuInfo，复制到目标 repeated 字段
    for (const auto& cpu : pair.second.cpu_info()) {
      monitor_info->mutable_cpu_info()->Add()->CopyFrom(cpu);
    }
  }

  return Status::OK;
}

}  // namespace monitor