#ifndef MONITOR_BASE_
#define MONITOR_BASE_

#include <string>

#include "generated/monitor.grpc.pb.h"

/// @brief 监控基类，定义抽象接口
namespace monitor {
class MonitorBase {
 private:
 public:
  MonitorBase() = default;
  virtual ~MonitorBase() = default;

  MonitorBase(const MonitorBase&) = delete;
  MonitorBase& operator=(const MonitorBase&) = delete;

  /// @brief 更新监控信息（单次）
  /// @param monitor_info 待更新的监控信息对象
  virtual void UpdateOnce(monitor::proto::MonitorInfo* monitor_info) = 0;

  virtual void Stop() = 0;
};

}  // namespace monitor

#endif