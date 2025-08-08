#ifndef Q_CPU_INFO_MODEL_
#define Q_CPU_INFO_MODEL_

#include "monitor.grpc.pb.h"
#include "QMonitorBase.hpp"

#include <QAbstractTableModel>
#include <vector>

namespace monitor {

class QCpuInfoModel : public QMonitorBase {
    Q_OBJECT

  public:
    explicit QCpuInfoModel(QObject * parent = nullptr);

    virtual ~QCpuInfoModel() {}

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
    std::vector<QVariant>              insertOneCpuInfo(const monitor::proto::CpuInfo & cpu_info);
    std::vector<std::vector<QVariant>> monitor_data_;
    QStringList                        header_;

    enum CpuInfo { NAME = 0, MODEL_NAME, MHZ, CACHE_SIZE_KB, CORE_NUMS, COLUMN_MAX };

    // int COLUMN_MAX_ = 5;
};

}  // namespace monitor

#endif
