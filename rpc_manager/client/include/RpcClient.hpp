#include <grpcpp/grpcpp.h>

#include "StringUtil.hpp"
#include "monitor.grpc.pb.h"
#include "monitor.pb.h"

namespace monitor {

using monitor::proto::AllMonitorInfo;
using monitor::proto::GrpcManager;
using monitor::proto::MonitorInfo;

class RpcClient {
 public:
  RpcClient();
  ~RpcClient();

  // 新增带参数的构造函数
  explicit RpcClient(const std::string& server_address);

  bool SetMonitorInfo(const MonitorInfo& monitor_info);
  bool GetMonitorInfo(MonitorInfo* monitor_info);

  bool GetAllMonitorInfo(AllMonitorInfo* all_monitor_info);

 private:
  std::unique_ptr<GrpcManager::Stub> stub_ptr_;
};

}  // namespace monitor
