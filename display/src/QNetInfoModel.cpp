#include "QNetInfoModel.hpp"

namespace monitor {

QNetInfoModel::QNetInfoModel(QObject * parent) : QMonitorBase(parent) {
    header_ << tr("cpu");
    header_ << tr("高优先级");
    header_ << tr("定时器");
    header_ << tr("网络发送");
    header_ << tr("网络接收");
}

QNetInfoModel::~QNetInfoModel() {}

int QNetInfoModel::rowCount(const QModelIndex & parent) const {
    return monitor_data_.size();
}

int QNetInfoModel::columnCount(const QModelIndex & parent) const {
    return COLUMN_MAX;
}

QVariant QNetInfoModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        if (index.row() < monitor_data_.size() && index.column() <= COLUMN_MAX) {
            return monitor_data_[index.row()][index.column()];
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant QNetInfoModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return header_[section];
    }
    return QMonitorBase::headerData(section, orientation, role);
}

void QNetInfoModel::updateMonitorInfo(const monitor::proto::MonitorInfo & monitor_info) {
    beginResetModel();
    monitor_data_.clear();
    for (const auto & info : monitor_info.net_info()) {
        monitor_data_.push_back(insertOneNetInfo(info));
    }

    endResetModel();
}

std::vector<QVariant> QNetInfoModel::insertOneNetInfo(const monitor::proto::NetInfo & net_info) {
    const int column_count = static_cast<int>(NetModelInfo::COLUMN_MAX) - static_cast<int>(NetModelInfo::NAME);
    std::vector<QVariant> net_info_row;
    net_info_row.reserve(column_count);  // 提前预留内存，优化性能

    for (NetModelInfo col = NetModelInfo::NAME; col < NetModelInfo::COLUMN_MAX;
         col              = static_cast<NetModelInfo>(static_cast<int>(col) + 1)) {
        switch (col) {
            case NetModelInfo::NAME:
                // 字符串字段：直接转换，空字符串对应“无名称”
                net_info_row.push_back(QString::fromStdString(net_info.name()));
                break;

            case NetModelInfo::SEND_RATE:
                // 移除has_xxx()，直接取double值（默认0.0，符合“无数据时显示0”的需求）
                net_info_row.push_back(QVariant(static_cast<double>(net_info.send_rate())));
                break;

            case NetModelInfo::RCV_RATE:
                net_info_row.push_back(QVariant(static_cast<double>(net_info.rcv_rate())));
                break;

            case NetModelInfo::SEND_PACKETS_RATE:
                net_info_row.push_back(QVariant(static_cast<double>(net_info.send_packets_rate())));
                break;

            case NetModelInfo::RCV_PACKETS_RATE:
                net_info_row.push_back(QVariant(static_cast<double>(net_info.rcv_packets_rate())));
                break;

            default:
                // 无效列填充空值，避免向量长度异常
                net_info_row.push_back(QVariant());
                Logger::getInstance().warning("Invalid NetModel column: {}", static_cast<int>(col));
                break;
        }
    }
    return net_info_row;
}
}  // namespace monitor
