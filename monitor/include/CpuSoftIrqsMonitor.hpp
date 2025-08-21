#ifndef CPU_SOFT_IRQS_MONITOR_
#define CPU_SOFT_IRQS_MONITOR_

#include "Logger.hpp"
#include "MonitorBase.hpp"
#include "ReadFile.hpp"

#include <chrono>
#include <fstream>
#include <unordered_map>

namespace monitor {

class CpuSoftIrqsMonitor : public MonitorBase {
    struct CpuSoftIrqs {
        std::string                               cpu_name;   // CPU0, CPU1 ...
        std::unordered_map<std::string, uint64_t> counters;   // {"HI" -> 0, "TIMER" -> 59265, ...}
        std::chrono::steady_clock::time_point     timestamp;  // 采样时间
    };

  public:
    CpuSoftIrqsMonitor();
    ~CpuSoftIrqsMonitor();

    void UpdateOnce(monitor::proto::MonitorInfo * monitor_info) override;

    const std::unordered_map<std::string, CpuSoftIrqs> & GetData() const { return cpu_softirqs_; }

  private:
    std::unordered_map<std::string, CpuSoftIrqs> cpu_softirqs_;
    std::unordered_map<std::string, CpuSoftIrqs> last_cpu_softirqs_;  // 上一次采样
    void                                         readFile();
};

}  // namespace monitor

#endif
