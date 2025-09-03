#include "NetInfoMonitor.hpp"

namespace monitor {

NetInfoMonitor::NetInfoMonitor()  = default;
NetInfoMonitor::~NetInfoMonitor() = default;

void NetInfoMonitor::UpdateOnce(monitor::proto::MonitorInfo * monitor_info) {
    util::ReadFile           net_file(std::string("/proc/net/dev"));
    std::vector<std::string> net_datas;

    while (net_file.ReadLine(net_datas)) {
        std::string name = net_datas[0];
        if (name.find(':') && net_datas.size() >= 10) {
            try {
                struct NetInfo info;
                name.pop_back();
                info.name        = name;
                info.rcv_bytes   = std::stoll(net_datas[1]);
                info.rcv_packets = std::stoll(net_datas[2]);
                info.err_in      = std::stoll(net_datas[3]);
                info.drop_in     = std::stoll(net_datas[4]);
                info.snd_bytes   = std::stoll(net_datas[9]);
                info.snd_packets = std::stoll(net_datas[10]);
                info.err_out     = std::stoll(net_datas[11]);
                info.drop_out    = std::stoll(net_datas[12]);
                info.timepoint   = std::chrono::steady_clock::now();

                auto iter = net_info_.find(name);
                if (iter != net_info_.end()) {
                    struct NetInfo old_info = std::move(iter->second);
                    double         period   = util::Clock::SteadyTimeSecond(info.timepoint, old_info.timepoint);

                    auto one_msg = monitor_info->add_net_info();
                    one_msg->set_name(info.name);
                    one_msg->set_send_rate((info.snd_bytes - old_info.snd_bytes) / 1024.0 / period);
                    one_msg->set_rcv_rate((info.rcv_bytes - old_info.rcv_bytes) / 1024.0 / period);
                    one_msg->set_send_packets_rate((info.snd_packets - old_info.snd_packets) / period);
                    one_msg->set_rcv_packets_rate((info.rcv_packets - old_info.rcv_packets) / period);
                }
                net_info_[name] = info;
            } catch (const std::exception & e) {
                Logger::getInstance().error("Failed to parse net info for {}: {}", name, e.what());
            }
        }
        net_datas.clear();
    }
}

}  // namespace monitor
