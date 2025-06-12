#include "RpcServer.hpp"

namespace monitor {

RpcServer::RpcServer() {}
RpcServer::~RpcServer() {}

::grpc::Starus RpcServer::SetMonitorInfo(
    ::grpc::ServerContext* context,
    const ::monitor::proto::MonitorInfo& request,
    ::google::protobuf::Empty* response) {
  monitor_infos_.Clear();
  monitor_infos_ = *request;

  return ::grpc::Status::OK;
}

}  // namespace monitor