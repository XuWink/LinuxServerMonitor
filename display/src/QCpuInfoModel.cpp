#include "QCpuInfoModel.hpp"

namespace monitor {
QCpuInfoModel::QCpuInfoModel(QObject * parent) : QMonitorBase(parent) {
    header_ << QStringLiteral("cpu名称");
    header_ << QStringLiteral("型号");
    header_ << QStringLiteral("频率");
    header_ << QStringLiteral("缓存大小");
    header_ << QStringLiteral("核心数");
}

int QCpuInfoModel::rowCount(const QModelIndex & parent) const {
    return monitor_data_.size();
}

int QCpuInfoModel::columnCount(const QModelIndex & parent) const {
    return COLUMN_MAX;
}

QVariant QCpuInfoModel::data(const QModelIndex & index, int role) const {
    // std::cout << "渲染表格数据" << std::endl;
    // 越界

    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        if (index.row() < monitor_data_.size() && index.column() <= COLUMN_MAX) {
            return monitor_data_[index.row()][index.column()];
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;  // 关键代码：设置居中
    }
    return QVariant();
}

QVariant QCpuInfoModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // std::cout << "渲染表头 " << "role = " << role << std::endl;

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return header_[section];
    }
    return QMonitorBase::headerData(section, orientation, role);
}

void QCpuInfoModel::updateMonitorInfo(const monitor::proto::MonitorInfo & monitor_info) {
    beginResetModel();
    monitor_data_.clear();
    for (const auto & cpu : monitor_info.cpu_info()) {
        monitor_data_.push_back(insertOneCpuInfo(cpu));
    }

    endResetModel();
}

std::vector<QVariant> QCpuInfoModel::insertOneCpuInfo(const monitor::proto::CpuInfo & cpu_info) {
    std::vector<QVariant> cpu_info_list;
    cpu_info_list.reserve(COLUMN_MAX);  // 预分配空间，提高性能

    // 按照枚举顺序填充数据
    cpu_info_list.push_back(QVariant(QString::fromStdString(cpu_info.name())));        // NAME
    cpu_info_list.push_back(QVariant(QString::fromStdString(cpu_info.model_name())));  // MODEL_NAME
    cpu_info_list.push_back(QVariant(cpu_info.mhz()));                                 // MHZ
    cpu_info_list.push_back(QVariant(cpu_info.cache_size_kb()));                       // CACHE_SIZE_KB
    cpu_info_list.push_back(QVariant(cpu_info.core_nums()));                           // CORE_NUMS

    return cpu_info_list;
}

}  // namespace monitor
