#include "QMonitorBase.hpp"

namespace monitor {

// 表头列表
QVariant QMonitorBase::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::FontRole) {
        // 设置表头字体
        return QVariant::fromValue(headerFont);
    }
    if (role == Qt::BackgroundRole) {
        // 设置表头背景颜色
        return QVariant::fromValue(headerBackgroundColor);
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

// 表格数据
QVariant QMonitorBase::data(const QModelIndex & index, int role) const {
    if (role == Qt::TextAlignmentRole) {
        // 设置文本对齐方式
        return QVariant(textAlignment);
    }
    if (role == Qt::ForegroundRole) {
        // 设置文本颜色
        return QVariant::fromValue(textColor);
    }
    if (role == Qt::BackgroundRole) {
        // 设置背景颜色
        return QVariant::fromValue(backgroundColor);
    }
    return QVariant();
}

}  // namespace monitor
