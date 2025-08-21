#include "QCpuSoftIrqsModel.hpp"

namespace monitor {
QCpuSoftIrqsModel::QCpuSoftIrqsModel(QObject * parent) : QMonitorBase(parent) {
    header_ << tr("cpu");
    header_ << tr("高优先级");
    header_ << tr("定时器");
    header_ << tr("网络发送");
    header_ << tr("网络接收");
    header_ << tr("块设备");
    header_ << tr("中断轮询");
    header_ << tr("tasklet");
    header_ << tr("调度器");
    header_ << tr("高精度定时器");
    header_ << tr("Read-Copy-Update");
    /*
        cpu：CPU 核心编号
        hi：高优先级软中断
        timer：定时器软中断
        net_tx：网络发送软中断
        net_rx：网络接收软中断
        block：块设备软中断
        irq_poll：中断轮询软中断
        tasklet：tasklet 软中断
        sched：调度器软中断
        hrtimer：高精度定时器软中断
        rcu：RCU（Read-Copy-Update）软中断
    */
}

QCpuSoftIrqsModel::~QCpuSoftIrqsModel() {}

int QCpuSoftIrqsModel::rowCount(const QModelIndex & parent) const {
    return monitor_data_.size();
}

int QCpuSoftIrqsModel::columnCount(const QModelIndex & parent) const {
    return COLUMN_MAX;
}

QVariant QCpuSoftIrqsModel::data(const QModelIndex & index, int role) const {
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

QVariant QCpuSoftIrqsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return header_[section];
    }
    return QMonitorBase::headerData(section, orientation, role);
}

void QCpuSoftIrqsModel::updateMonitorInfo(const monitor::proto::MonitorInfo & monitor_info) {
    beginResetModel();
    monitor_data_.clear();
    for (const auto & soft_irq : monitor_info.soft_irqs()) {
        monitor_data_.push_back(insertOneCpuSoftIrqs(soft_irq));
    }

    endResetModel();
}

std::vector<QVariant> QCpuSoftIrqsModel::insertOneCpuSoftIrqs(const monitor::proto::SoftIrqs & softIrqs) {
    std::stringstream ss;
    ss << "softIrqs: "
       << "cpu: " << softIrqs.cpu() << ", "
       << "timer: " << softIrqs.timer();
    Logger::getInstance().info(ss.str());

    using Getter                                        = std::function<QVariant(const monitor::proto::SoftIrqs &)>;
    static const std::array<Getter, COLUMN_MAX> getters = {
        // CPU_NAME
        [](const auto & s) { return QString::fromStdString(s.cpu()); },
        [](const auto & s) { return s.hi(); },
        [](const auto & s) { return s.timer(); },
        [](const auto & s) { return s.net_tx(); },
        [](const auto & s) { return s.net_rx(); },
        [](const auto & s) { return s.block(); },
        [](const auto & s) { return s.irq_poll(); },
        [](const auto & s) { return s.tasklet(); },
        [](const auto & s) { return s.sched(); },
        [](const auto & s) { return s.hrtimer(); },
        [](const auto & s) {
            return s.rcu();
        }
    };

    std::vector<QVariant> softIrqList;
    softIrqList.reserve(COLUMN_MAX);

    std::transform(getters.begin(), getters.end(), std::back_inserter(softIrqList), [&](const Getter & getter) {
        return getter(softIrqs);
    });

    return softIrqList;
}

}  // namespace monitor
