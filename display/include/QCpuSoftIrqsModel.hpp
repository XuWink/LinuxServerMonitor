#ifndef Q_CPU_SOFT_IRQS_MODEL_
#define Q_CPU_SOFT_IRQS_MODEL_

#include "Logger.hpp"
#include "monitor.grpc.pb.h"
#include "QMonitorBase.hpp"

namespace monitor {

class QCpuSoftIrqsModel : public QMonitorBase {
    Q_OBJECT
  public:
    explicit QCpuSoftIrqsModel(QObject * parent = nullptr);
    ~QCpuSoftIrqsModel();

    // 返回表格的行数
    int      rowCount(const QModelIndex & parent = QModelIndex()) const override;
    // 返回表格的列数
    int      columnCount(const QModelIndex & parent = QModelIndex()) const override;
    // data 返回指定索引和角色的数据
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    // cloumn name 返回表格表头的数据
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void updateMonitorInfo(const monitor::proto::MonitorInfo & monitor_info);

  signals:


  private:
    std::vector<QVariant>              insertOneCpuSoftIrqs(const monitor::proto::SoftIrqs & cpu_SoftIrqs);
    std::vector<std::vector<QVariant>> monitor_data_;
    QStringList                        header_;

    enum CpuSoftIrqs {
        CPU_NAME = 0,
        HI,
        TIMER,
        NET_TX,
        NET_RX,
        BLOCK,
        IRQ_POLL,
        TASKLET,
        SCHED,
        HRTIMER,
        RCU,
        COLUMN_MAX
    };
};

}  // namespace monitor

#endif
