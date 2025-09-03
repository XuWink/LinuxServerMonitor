#ifndef NET_INFO_MONITOR_
#define NET_INFO_MONITOR_

#include "Clock.hpp"
#include "Logger.hpp"
#include "MonitorBase.hpp"
#include "ReadFile.hpp"

#include <unordered_map>

namespace monitor {
class NetInfoMonitor : public MonitorBase {
    struct NetInfo {
        std::string                           name;
        int64_t                               rcv_bytes;
        int64_t                               rcv_packets;
        int64_t                               err_in;
        int64_t                               drop_in;
        int64_t                               snd_bytes;
        int64_t                               snd_packets;
        int64_t                               err_out;
        int64_t                               drop_out;
        std::chrono::steady_clock::time_point timepoint;
    };


  public:
    NetInfoMonitor();
    ~NetInfoMonitor();

    void UpdateOnce(monitor::proto::MonitorInfo * monitor_info) override;

  private:
    std::unordered_map<std::string, struct NetInfo> net_info_;
};

}  // namespace monitor

#endif
