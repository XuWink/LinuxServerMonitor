#ifndef RPC_SERVER_H_
#define RPC_SERVER_H_

#include <grpcpp/support/status.h>

#include <unordered_map>

#include "monitor.grpc.pb.h"
#include "monitor.pb.h"

namespace monitor {

using google::protobuf::Empty;
using grpc::ServerContext;
using grpc::Status;
using monitor::proto::MonitorInfo;

class RpcServer : public monitor::proto::GrpcManager::Service {
  // using Empty = google::protobuf::Empty;
  // using ServerContext = grpc::ServerContext;
  // using Status = grpc::Status;
  // using MonitorInfo = ::proto::MonitorInfo;
  // using Service = ::proto::GrpcManager::Service;

 public:
  RpcServer();
  virtual ~RpcServer();

  // 实现Service中的接口
  grpc::Status SetMonitorInfo(grpc::ServerContext* context,
                              const monitor::proto::MonitorInfo* request,
                              google::protobuf::Empty* response) override;
  grpc::Status GetMonitorInfo(grpc::ServerContext* context,
                              const google::protobuf::Empty* request,
                              monitor::proto::MonitorInfo* response) override;

 private:
  MonitorInfo monitor_infos_;
};
}  // namespace monitor

#endif