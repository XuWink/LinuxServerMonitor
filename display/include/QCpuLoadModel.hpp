#ifndef Q_CPU_LOAD_MODEL_
#define Q_CPU_LOAD_MODEL_

#include "Logger.hpp"
#include "monitor.grpc.pb.h"
#include "QMonitorBase.hpp"

#include <QAbstractTableModel>
#include <vector>

namespace monitor {

class QCpuLoadModel : public QMonitorBase {
    Q_OBJECT

  public:
    explicit QCpuLoadModel(QObject * parent = nullptr);

    virtual ~QCpuLoadModel() {}

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
    std::vector<QVariant>              insertOneCpuLoad(const monitor::proto::CpuLoad & cpu_info);
    std::vector<std::vector<QVariant>> monitor_data_;
    QStringList                        header_;

    enum CpuLoad { LOAD1 = 0, LOAD5, LOAD15, RUNNING_TOTAL, LAST_PID, COLUMN_MAX };
};

}  // namespace monitor

#endif
