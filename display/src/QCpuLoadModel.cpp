#include "QCpuLoadModel.hpp"

namespace monitor {

QCpuLoadModel::QCpuLoadModel(QObject * parent) {
    header_ << tr("负载1（1min）");
    header_ << tr("负载2（5min）");
    header_ << tr("负载3（15min）");
    header_ << tr("线程数（运行中/总数）");
    header_ << tr("最近运行的线程ID");
}

int QCpuLoadModel::rowCount(const QModelIndex & parent) const {
    return monitor_data_.size();
}

int QCpuLoadModel::columnCount(const QModelIndex & parent) const {
    return COLUMN_MAX;
}

QVariant QCpuLoadModel::data(const QModelIndex & index, int role) const {
    if (index.column() < 0 || index.column() >= COLUMN_MAX) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        if (index.row() < monitor_data_.size() && index.column() < COLUMN_MAX) {
            return monitor_data_[index.row()][index.column()];
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;  // 关键代码：设置居中
    }
    return QVariant();
}

QVariant QCpuLoadModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return header_[section];
    }

    return QMonitorBase::headerData(section, orientation, role);
}

void QCpuLoadModel::updateMonitorInfo(const monitor::proto::MonitorInfo & monitor_info) {
    beginResetModel();
    monitor_data_.clear();

    monitor_data_.push_back(insertOneCpuLoad(monitor_info.cpu_load()));

    endResetModel();
}

std::vector<QVariant> QCpuLoadModel::insertOneCpuLoad(const monitor::proto::CpuLoad & cpu_load) {
    std::stringstream ss;
    ss << "CPU LOAD of QCpuLoadModel.cpp: "
       << "load1: " << cpu_load.load1() << ", "
       << "load5: " << cpu_load.load5() << ", "
       << "load15: " << cpu_load.load15() << ", "
       << "running_total: " << cpu_load.running_total() << ", "
       << "last_pid: " << cpu_load.last_pid();
    Logger::getInstance().info(ss.str());

    std::vector<QVariant> cpu_load_list;
    cpu_load_list.emplace_back(cpu_load.load1());
    cpu_load_list.emplace_back(cpu_load.load5());
    cpu_load_list.emplace_back(cpu_load.load15());
    cpu_load_list.emplace_back(QString::fromStdString(cpu_load.running_total()));
    cpu_load_list.emplace_back(static_cast<uint>(cpu_load.last_pid()));
    return cpu_load_list;
}
}  // namespace monitor
