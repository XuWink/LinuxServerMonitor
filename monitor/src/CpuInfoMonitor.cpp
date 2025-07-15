#include "CpuInfoMonitor.hpp"

namespace monitor {

/// @brief 更新数据到服务器
/// @param monitor_info
void CpuInfoMonitor::UpdateOnce(monitor::proto::MonitorInfo* monitor_info) {
  // 1. 读取整个文件内容
  std::ifstream cpuinfo_file("/proc/cpuinfo");
  if (!cpuinfo_file.is_open()) {
    return;  // 文件打开失败
  }

  // 一次性读取整个文件内容到字符串
  std::string file_content(
      (std::istreambuf_iterator<char>(cpuinfo_file)),  // 开始迭代器
      std::istreambuf_iterator<char>()                 // 结束迭代器
  );

  // 2. 按空行分割段落（每个段落对应一个 CPU）
  std::vector<std::string> cpu_sections;
  std::istringstream file_stream(file_content);
  std::string line;
  std::string current_section;

  while (std::getline(file_stream, line)) {
    if (line.empty()) {
      // 遇到空行，保存当前段落
      if (!current_section.empty()) {
        cpu_sections.push_back(current_section);
        current_section.clear();
      }
    } else {
      // 添加行到当前段落，保留换行符
      current_section += line + "\n";
    }
  }

  // 添加最后一个段落（如果文件末尾没有空行）
  if (!current_section.empty()) {
    cpu_sections.push_back(current_section);
  }

  // 3. 逐段解析并填充 Protobuf
  for (const auto& cpu_section : cpu_sections) {
    CpuInfo cpu_info = ParseCpuSection(cpu_section);
    auto cpu_info_msg = monitor_info->add_cpu_info();
    cpu_info_msg->set_name(cpu_info.name);
    cpu_info_msg->set_model_name(cpu_info.model_name);
    cpu_info_msg->set_mhz(cpu_info.mhz);
    cpu_info_msg->set_cache_size_kb(cpu_info.cache_size_kb);
    cpu_info_msg->set_core_nums(cpu_info.core_nums);
  }
}

/// @brief 读取 Linux 的 /proc/cpuinfo，参考 assets/cpuinfo 文件
/// @param monitor_info
monitor::CpuInfoMonitor::CpuInfo CpuInfoMonitor::ParseCpuSection(
    const std::string& section) {
  CpuInfo cpu_info;
  std::istringstream section_stream(section);
  std::string line;

  while (std::getline(section_stream, line)) {
    // 按 ':' 分割键值对
    auto tokens = util::StringUtil::split(line, ':');
    if (tokens.size() < 2) continue;

    std::string key = tokens[0];
    util::StringUtil::TrimString(key);
    std::string value = tokens[1];
    util::StringUtil::TrimString(value);

    // 根据字段名填充结构体
    if (key == "processor") {
      cpu_info.name = "cpu" + value;
    } else if (key == "model name") {
      cpu_info.model_name = value;
    } else if (key == "cpu MHz") {
      try {
        cpu_info.mhz = std::stof(value);
      } catch (...) {
        cpu_info.mhz = 0.0f;  // 默认值
      }
    } else if (key == "cache size") {
      // 处理单位（如 "8192 KB"）通过 std::remove_if + erase
      // 删除所有字母字符，保留数字和小数点
      std::string numeric_value = value;
      numeric_value.erase(
          std::remove_if(numeric_value.begin(), numeric_value.end(), ::isalpha),
          numeric_value.end());
      try {
        cpu_info.cache_size_kb = std::stof(numeric_value);
      } catch (...) {
        cpu_info.cache_size_kb = 0.0f;
      }
    } else if (key == "cpu cores") {
      try {
        cpu_info.core_nums = std::stoi(value);
      } catch (...) {
        cpu_info.core_nums = 0;
      }
    }
  }

  return cpu_info;
}

}  // namespace monitor
