
#include "MemInfoMonitor.hpp"

namespace monitor {
MemInfoMonitor::MemInfoMonitor() {}

MemInfoMonitor::~MemInfoMonitor() {}

void MemInfoMonitor::UpdateOnce(monitor::proto::MonitorInfo * monitor_info) {
    // 修正拼写错误：MenInfo -> MemInfo
    struct MemInfo           mem_info{};  // 初始化结构体，避免未定义行为
    util::ReadFile           mem_file("/proc/meminfo");
    std::vector<std::string> mem_datas;

    // 定义字段名到内存信息的映射表，替代冗长的if-else
    const std::unordered_map<std::string, std::function<void(int64_t)>> field_handlers = {
        { "MemTotal:",
         [&](int64_t val) {
              mem_info.total = val;
          } },
        { "MemFree:",
         [&](int64_t val) {
              mem_info.free = val;
          } },
        { "MemAvailable:",
         [&](int64_t val) {
              mem_info.avail = val;
          } },
        { "Buffers:",
         [&](int64_t val) {
              mem_info.buffers = val;
          } },
        { "Cached:",
         [&](int64_t val) {
              mem_info.cached = val;
          } },
        { "SwapCached:",
         [&](int64_t val) {
              mem_info.swap_cached = val;
          } },
        { "Active:",
         [&](int64_t val) {
              mem_info.active = val;
          } },
        { "Inactive:",
         [&](int64_t val) {
              mem_info.in_active = val;
          } },
        { "Active(anon):",
         [&](int64_t val) {
              mem_info.active_anon = val;
          } },
        { "Inactive(anon):",
         [&](int64_t val) {
              mem_info.inactive_anon = val;
          } },
        { "Active(file):",
         [&](int64_t val) {
              mem_info.active_file = val;
          } },
        { "Inactive(file):",
         [&](int64_t val) {
              mem_info.inactive_file = val;
          } },
        { "Dirty:",
         [&](int64_t val) {
              mem_info.dirty = val;
          } },
        { "Writeback:",
         [&](int64_t val) {
              mem_info.writeback = val;
          } },
        { "AnonPages:",
         [&](int64_t val) {
              mem_info.anon_pages = val;
          } },
        { "Mapped:",
         [&](int64_t val) {
              mem_info.mapped = val;
          } },
        { "KReclaimable:",
         [&](int64_t val) {
              mem_info.kReclaimable = val;
          } },
        { "SReclaimable:",
         [&](int64_t val) {
              mem_info.sReclaimable = val;
          } },
        { "SUnreclaim:",
         [&](int64_t val) {
              mem_info.sUnreclaim = val;
          } }
    };

    // 读取并解析/proc/meminfo内容
    while (mem_file.ReadLine(mem_datas)) {
        // 校验行格式（至少包含字段名和数值）
        if (mem_datas.size() < 2) {
            mem_datas.clear();
            continue;
        }

        // 查找字段处理器并执行
        auto it = field_handlers.find(mem_datas[0]);
        if (it != field_handlers.end()) {
            try {
                // 转换数值并处理可能的异常（如非数字字符串）
                int64_t val = std::stoll(mem_datas[1]);
                it->second(val);  // 调用映射的处理函数
            } catch (const std::exception & e) {
                // 异常处理：记录日志（示例），不中断整体流程
                // LOG_WARN("Failed to parse mem field %s: %s", mem_datas[0].c_str(), e.what());
                Logger::getInstance().error("Failed to parse mem field");
            }
        }
        mem_datas.clear();
    }

    // 单位转换：KB -> GB（1GB = 1024*1024 KB）
    // auto convertKBToGB = [](int64_t kb) {
    //     constexpr int64_t KB_TO_GB = 1024 * 1024;
    //     return kb / KB_TO_GB;  // 若需更精确可使用double
    // };

    // 填充监控信息
    auto * mem_detail = monitor_info->mutable_meminfo();
    mem_detail->set_used_percent(mem_info.total > 0 ? (mem_info.total - mem_info.avail) * 100.0 / mem_info.total : 0.0);
    mem_detail->set_total(mem_info.total);
    mem_detail->set_free(mem_info.free);
    mem_detail->set_avail(mem_info.avail);
    mem_detail->set_buffers(mem_info.buffers);
    mem_detail->set_cached(mem_info.cached);
    mem_detail->set_swap_cached(mem_info.swap_cached);
    mem_detail->set_active(mem_info.active);
    mem_detail->set_inactive(mem_info.in_active);
    mem_detail->set_active_anon(mem_info.active_anon);
    mem_detail->set_inactive_anon(mem_info.inactive_anon);
    mem_detail->set_active_file(mem_info.active_file);
    mem_detail->set_inactive_file(mem_info.inactive_file);
    mem_detail->set_dirty(mem_info.dirty);
    mem_detail->set_writeback(mem_info.writeback);
    mem_detail->set_anon_pages(mem_info.anon_pages);
    mem_detail->set_mapped(mem_info.mapped);
    mem_detail->set_kreclaimable(mem_info.kReclaimable);
    mem_detail->set_sreclaimable(mem_info.sReclaimable);
    mem_detail->set_sunreclaim(mem_info.sUnreclaim);
}

}  // namespace monitor
