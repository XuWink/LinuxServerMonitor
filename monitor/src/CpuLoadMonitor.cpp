#include "CpuLoadMonitor.hpp"

namespace monitor {

CpuLoadMonitor::CpuLoadMonitor() {}

CpuLoadMonitor::~CpuLoadMonitor() {}

/// @brief 监测 /proc/loadavg
/// @param monitor_info
void CpuLoadMonitor::UpdateOnce(monitor::proto::MonitorInfo * monitor_info) {
    std::ifstream cpuload_file("/proc/loadavg");
    if (!cpuload_file.is_open()) {
        Logger::getInstance().error("open the file /proc/loadavg fail.");
        return;  // 文件打开失败
    }

    std::string file_content((std::istreambuf_iterator<char>(cpuload_file)),  // 开始迭代器
                             std::istreambuf_iterator<char>()                 // 结束迭代器
    );

    std::vector<std::string> result;
    util::StringUtil::split(file_content, std::string(" "), result);

    if (result.size() < 5) {
        Logger::getInstance().error("invalid /proc/loadavg format.");
        return;
    }

    CpuLoad cpu_load;
    cpu_load.load1         = std::stod(result[0]);
    cpu_load.load2         = std::stod(result[1]);
    cpu_load.load3         = std::stod(result[2]);
    cpu_load.running_total = result[3];  // 保留 "1/302" 原样
    cpu_load.last_pid      = static_cast<uint32_t>(std::stoul(result[4]));

    // 这里可以把 cpu_load 写入 proto
    auto * loadavg_proto = monitor_info->mutable_cpu_load();
    loadavg_proto->set_load1(cpu_load.load1);
    loadavg_proto->set_load5(cpu_load.load2);
    loadavg_proto->set_load15(cpu_load.load3);
    loadavg_proto->set_running_total(cpu_load.running_total);
    loadavg_proto->set_last_pid(cpu_load.last_pid);
}

}  // namespace monitor
