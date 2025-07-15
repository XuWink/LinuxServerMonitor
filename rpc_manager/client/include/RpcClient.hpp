
#include <grpcpp/grpcpp.h>

#include "monitor.grpc.pb.h"
#include "monitor.pb.h"

namespace monitor {

using monitor::proto::GrpcManager;
using monitor::proto::MonitorInfo;

class RpcClient {
 public:
  RpcClient();
  ~RpcClient();

  void SetMonitorInfo(const MonitorInfo& monito_info);
  void GetMonitorInfo(MonitorInfo* monito_info);

 private:
  std::unique_ptr<GrpcManager::Stub> stub_ptr_;
};

}  // namespace monitor
