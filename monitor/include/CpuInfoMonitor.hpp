#ifndef CPU_INFO_MONITOR_
#define CPU_INFO_MONITOR_

#include "MonitorBase.hpp"

namespace monitor {

class CpuInfoMonitor : public MonitorBase {
  // 与cpu_info.proto保持一致
  struct CpuInfo {
    std::string name;        // cpu名称
    std::string model_name;  // 型号名称
    float mhz;               // 频率，mhz大小
    float cache_size_kb;     // 缓存cache大小
    float core_nums;         // 核心core数量
 }

public: 
    explicit CpuInfoMonitor();
    void UpdateOnce(monitor::proto::MonitorInfo *monitor_info);
    void Stop() override;
};

}  // namespace monitor

#endif