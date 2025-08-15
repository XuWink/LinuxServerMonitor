#ifndef CPU_LOAD_MONITOR_
#define CPU_LOAD_MONITOR_

#include "Logger.hpp"
#include "MonitorBase.hpp"
#include "StringUtil.hpp"

namespace monitor {
class CpuLoadMonitor : public MonitorBase {
    struct CpuLoad {
        /* data */
        double      load1;
        double      load2;
        double      load3;
        std::string running_total;
        uint32_t    last_pid;
    };


  private:
    /* data */
  public:
    CpuLoadMonitor();
    ~CpuLoadMonitor() override;

    void UpdateOnce(monitor::proto::MonitorInfo * monitor_info) override;
};

}  // namespace monitor

#endif
