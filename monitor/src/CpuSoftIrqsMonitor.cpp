#include "CpuSoftIrqsMonitor.hpp"

namespace monitor {

CpuSoftIrqsMonitor::CpuSoftIrqsMonitor(/* args */) {}

CpuSoftIrqsMonitor::~CpuSoftIrqsMonitor() {}

void CpuSoftIrqsMonitor::UpdateOnce(monitor::proto::MonitorInfo * monitor_info) {
    Logger::getInstance().info("开始读取 /proc/softirqs ");
    readFile();

    for (auto & [cpu, info] : cpu_softirqs_) {
        auto iter = last_cpu_softirqs_.find(cpu);
        if (iter != last_cpu_softirqs_.end()) {
            auto & old = iter->second;

            double period =
                std::chrono::duration_cast<std::chrono::duration<double>>(info.timestamp - old.timestamp).count();
            if (period <= 0) {
                period = 1e-6;
            }

            auto msg = monitor_info->add_soft_irqs();
            msg->set_cpu(cpu);

            // 填充每个字段
            auto get_rate = [&](const std::string & name) -> float {
                uint64_t old_val = 0;
                auto     it      = old.counters.find(name);
                if (it != old.counters.end()) {
                    old_val = it->second;
                }
                auto     it2     = info.counters.find(name);
                uint64_t new_val = (it2 != info.counters.end()) ? it2->second : 0;
                return static_cast<float>((new_val - old_val) / period);
            };

            msg->set_hi(get_rate("HI"));
            msg->set_timer(get_rate("TIMER"));
            msg->set_net_tx(get_rate("NET_TX"));
            msg->set_net_rx(get_rate("NET_RX"));
            msg->set_block(get_rate("BLOCK"));
            msg->set_irq_poll(get_rate("IRQ_POLL"));
            msg->set_tasklet(get_rate("TASKLET"));
            msg->set_sched(get_rate("SCHED"));
            msg->set_hrtimer(get_rate("HRTIMER"));
            msg->set_rcu(get_rate("RCU"));
        }
    }

    last_cpu_softirqs_ = cpu_softirqs_;
}

void CpuSoftIrqsMonitor::readFile() {
    std::ifstream file("/proc/softirqs");
    if (!file.is_open()) {
        Logger::getInstance().error("Failed to open /proc/softirqs");
        return;
    }

    std::string              line;
    std::vector<std::string> cpu_names;

    // 第一行 CPU 列名
    if (!std::getline(file, line)) {
        return;
    }

    {
        std::istringstream iss(line);
        std::string        name;
        while (iss >> name) {
            cpu_names.push_back(name);
        }
    }

    auto now = std::chrono::steady_clock::now();
    for (auto & cpu : cpu_names) {
        cpu_softirqs_[cpu].cpu_name  = cpu;
        cpu_softirqs_[cpu].timestamp = now;
    }

    // 解析软中断类型
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string        irq_name;
        iss >> irq_name;
        if (!irq_name.empty() && irq_name.back() == ':') {
            irq_name.pop_back();
        }

        uint64_t value;
        for (auto & cpu : cpu_names) {
            if (!(iss >> value)) {
                break;
            }
            cpu_softirqs_[cpu].counters[irq_name] = value;
        }
    }
}

}  // namespace monitor
