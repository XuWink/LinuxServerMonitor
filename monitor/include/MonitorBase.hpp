#ifndef MONITOR_BASE_
#define MONITOR_BASE_

#include <string>

#include "monitor.grpc.pb.h"
#include "monitor.pb.h"

namespace monitor
{
    class MonitorBase
    {
    private:
    public:
        MonitorBase() = default;
        virtual ~MonitorBase() = default;

        virtual void UpdateOnce(monitor::proto::MonitorInfo &monitor_info) = 0;

        MonitorBase(const MonitorBase&) = delete;
        MonitorBase& operator=(const MonitorBase&) = delete;

    };
    
}

#endif