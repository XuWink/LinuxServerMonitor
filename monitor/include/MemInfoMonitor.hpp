
#ifndef MEM_INFO_MONITOR_
#define MEM_INFO_MONITOR_

#include "Logger.hpp"
#include "MonitorBase.hpp"
#include "ReadFile.hpp"
#include "StringUtil.hpp"

#include <unordered_map>

namespace monitor {
class MemInfoMonitor : public MonitorBase {
    struct MemInfo {
        int64_t total;
        int64_t free;
        int64_t avail;
        int64_t buffers;
        int64_t cached;
        int64_t swap_cached;
        int64_t active;
        int64_t in_active;
        int64_t active_anon;
        int64_t inactive_anon;
        int64_t active_file;
        int64_t inactive_file;
        int64_t dirty;
        int64_t writeback;
        int64_t anon_pages;
        int64_t mapped;
        int64_t kReclaimable;
        int64_t sReclaimable;
        int64_t sUnreclaim;
    };

  public:
    MemInfoMonitor();
    ~MemInfoMonitor();

    void UpdateOnce(monitor::proto::MonitorInfo * monitor_info) override;

  private:
};

}  // namespace monitor

#endif
