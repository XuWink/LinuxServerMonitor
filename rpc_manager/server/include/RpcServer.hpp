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

  // 新加
  grpc::Status GetAllMonitorInfo(
      grpc::ServerContext* context, const google::protobuf::Empty* request,
      monitor::proto::AllMonitorInfo* response) override;

 private:
  MonitorInfo monitor_infos_;

  // 客户端IP -> CPU信息
  std::unordered_map<std::string, monitor::proto::MonitorInfo> clients_;
  mutable std::mutex clients_mutex_;  // 保护clients_的互斥锁
  std::string getClientIP(grpc::ServerContext* context) const;
};
}  // namespace monitor

#endif