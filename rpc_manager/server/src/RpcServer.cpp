#include "RpcServer.hpp"

namespace monitor {

RpcServer::RpcServer() {}
RpcServer::~RpcServer() {}

// 客户端调用SetMonitorInfo函数更新monitor_infos_
Status RpcServer::SetMonitorInfo(ServerContext* context, const MonitorInfo& request, Empty* response) {
  monitor_infos_.Clear();
  monitor_infos_ = *request;

  return Status::OK;
}

// QT前端调用GetMonitorInfo函数展示数据
Status RpcServer::GetMonitorInfo(ServerContext* context, const Empty* request, MonitorInfo* response) {
  *response = monitor_infos_;
  
  return Status::OK;
}

}  // namespace monitor