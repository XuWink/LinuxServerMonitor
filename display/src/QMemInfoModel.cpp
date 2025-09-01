#include "QMemInfoModel.hpp"

namespace monitor {

// QMemInfoModel::QMemInfoModel() {}

QMemInfoModel::QMemInfoModel(QObject * parent) : QMonitorBase(parent) {
    header_ << tr("used_percent");
    header_ << tr("total");
    header_ << tr("free");
    header_ << tr("avail");
    header_ << tr("buffers");
    header_ << tr("cached");
    header_ << tr("swap_cached");
    header_ << tr("active");
    header_ << tr("in_active");
    header_ << tr("active_anon");
    header_ << tr("inactive_anon");
    header_ << tr("active_file");
    header_ << tr("inactive_file");
    header_ << tr("dirty");
    header_ << tr("writeback");
    header_ << tr("anon_pages");
    header_ << tr("mapped");
    header_ << tr("kReclaimable");
    header_ << tr("sReclaimable");
    header_ << tr("sUnreclaim");
}

QMemInfoModel::~QMemInfoModel() {}

int QMemInfoModel::rowCount(const QModelIndex & parent) const {
    // return monitor_data_.size();
    Q_UNUSED(parent);
    return COLUMN_MAX;
}

int QMemInfoModel::columnCount(const QModelIndex & parent) const {
    // return COLUMN_MAX;
    Q_UNUSED(parent);
    return 1;  // 只一列
}

QVariant QMemInfoModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
        case Qt::DisplayRole:
            if (index.row() >= 0 && index.row() < static_cast<int>(mem_info_.size())) {
                return mem_info_[index.row()];
            }
            return QVariant();

        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;  // 水平垂直居中

        default:
            return QVariant();
    }
}

QVariant QMemInfoModel::headerData(int section, Qt::Orientation orientation, int role) const {
    static const QStringList rowHeaders = {
        "使用率 (%)",    "总内存 (KB)", "空闲内存 (KB)", "可用内存 (KB)",       "缓冲区 (KB)",       "缓存 (KB)",
        "Swap缓存 (KB)", "活跃 (KB)",   "非活跃 (KB)",   "活跃匿名页 (KB)",     "非活跃匿名页 (KB)", "脏页 (KB)",
        "写回 (KB)",     "匿名页 (KB)", "映射页 (KB)",   "可回收内核内存 (KB)", "可回收Slab (KB)",   "不可回收Slab (KB)"
    };

    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            return QVariant();  // 不显示横向标题
        }
        if (role == Qt::TextAlignmentRole) {
            return Qt::AlignCenter;  // 横向表头也居中（即使不可见）
        }
        return QVariant();
    }

    // 纵向标题
    if (orientation == Qt::Vertical) {
        switch (role) {
            case Qt::DisplayRole:
                if (section >= 0 && section < rowHeaders.size()) {
                    return rowHeaders.at(section);
                }
                break;

            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;  // 纵向标题居中

            case Qt::FontRole:
                {
                    QFont font;
                    font.setBold(true);    // 粗体
                    font.setPointSize(9);  // 字号
                    return font;
                }

            case Qt::ForegroundRole:
                return QBrush(Qt::darkBlue);  // 字体颜色
        }
    }

    return QMonitorBase::headerData(section, orientation, role);
}

void QMemInfoModel::updateMonitorInfo(const monitor::proto::MonitorInfo & monitor_info) {
    beginResetModel();
    monitor_data_.clear();
    monitor_data_.push_back(insertOneMemInfo(monitor_info.meminfo()));

    endResetModel();
}

std::vector<QVariant> QMemInfoModel::insertOneMemInfo(const monitor::proto::MemInfo & mem_info) {
    using Getter = std::function<qint64(const monitor::proto::MemInfo &)>;

    static const std::array<Getter, COLUMN_MAX> getters = { [&](const auto & m) { return m.used_percent(); },
                                                            [&](const auto & m) { return m.total(); },
                                                            [&](const auto & m) { return m.free(); },
                                                            [&](const auto & m) { return m.avail(); },
                                                            [&](const auto & m) { return m.buffers(); },
                                                            [&](const auto & m) { return m.cached(); },
                                                            [&](const auto & m) { return m.swap_cached(); },
                                                            [&](const auto & m) { return m.active(); },
                                                            [&](const auto & m) { return m.inactive(); },
                                                            [&](const auto & m) { return m.active_anon(); },
                                                            [&](const auto & m) { return m.inactive_anon(); },
                                                            [&](const auto & m) { return m.dirty(); },
                                                            [&](const auto & m) { return m.writeback(); },
                                                            [&](const auto & m) { return m.anon_pages(); },
                                                            [&](const auto & m) { return m.mapped(); },
                                                            [&](const auto & m) { return m.kreclaimable(); },
                                                            [&](const auto & m) { return m.sreclaimable(); },
                                                            [&](const auto & m) {
                                                                return m.sunreclaim();
                                                            } };

    std::vector<QVariant> mem_info_list;
    mem_info_list.reserve(COLUMN_MAX);

    for (int i = MemInfo::USED_PERCENT; i < COLUMN_MAX; i++) {
        if (getters[i]) {
            mem_info_list.emplace_back(getters[i](mem_info));
        }
    }

    mem_info_ = mem_info_list;  // 保存当前的内存信息
    return mem_info_list;
}

}  // namespace monitor
