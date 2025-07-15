#ifndef CPU_INFO_MONITOR_
#define CPU_INFO_MONITOR_

#include <unordered_map>
#include <vector>

#include "Logger.hpp"
#include "MonitorBase.hpp"
// #include "ReadFile.hpp"
#include "StringUtil.hpp"

namespace monitor {

class CpuInfoMonitor : public MonitorBase {
  // 与cpu_info.proto保持一致
  struct CpuInfo {
    std::string name;            // cpu名称
    std::string model_name;      // 型号名称
    float mhz = 0.0f;            // 频率，mhz大小
    float cache_size_kb = 0.0f;  // 缓存cache大小
    int core_nums = 0;           // 核心core数量
  };

 public:
  CpuInfoMonitor() = default
  ~CpuInfoMonitor() override = default;

  void UpdateOnce(monitor::proto::MonitorInfo* monitor_info) override;

 private:
  /// @brief 从系统读取 CPU 信息
  void ParseCpuSection(const std::string& section);
};

}  // namespace monitor

#endif