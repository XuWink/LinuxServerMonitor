#ifndef RPC_SERVER_H_
#define RPC_SERVER_H_

#include <grpcpp/support/status.h>

#include <unordered_map>

#include "monitor.grpc.pb.h"
#include "monitor.pb.h"

namespace monitor {

class RpcServer : public monitor::proto::GrpcManager::Service {
 public:
  RpcServer();
  virtual ~RpcServer();

  ::grpc::Status SetMonitorInfo(::grpc::ClientContext* context,
                                const ::monitor::proto::MonitorInfo& request,
                                ::google::protobuf::Empty* response) override;
  ::grpc::Status GetMonitorInfo(::grpc::ServerContext* context,
                                const ::google::protobuf::Empty* request,
                                ::monitor::proto::MonitorInfo* response);

 private:
  monitor::proto::MonitorInfo monitor_infos_;
};
}  // namespace monitor

#endif