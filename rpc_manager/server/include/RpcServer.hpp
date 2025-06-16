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
using monitor::proto::GrpcManager::Service;

class RpcServer : public Service {
 public:
  RpcServer();
  virtual ~RpcServer();

  // 实现Service中的接口
  Status SetMonitorInfo(ServerContext* context, const MonitorInfo& request,
                        Empty* response) override;
  Status GetMonitorInfo(ServerContext* context, const Empty* request,
                        MonitorInfo* response) override;

 private:
  MonitorInfo monitor_infos_;
};
}  // namespace monitor

#endif