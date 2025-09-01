#ifndef Q_MEM_INFO_MODEL_
#define Q_MEM_INFO_MODEL_

#include "Logger.hpp"
#include "monitor.grpc.pb.h"
#include "QMonitorBase.hpp"

#include <QBrush>
#include <QFont>
#include <QStringList>
#include <vector>

namespace monitor {
class QMemInfoModel : public QMonitorBase {
    Q_OBJECT
  public:
    explicit QMemInfoModel(QObject * parent = nullptr);
    virtual ~QMemInfoModel();

    // 返回表格的行数
    int      rowCount(const QModelIndex & parent = QModelIndex()) const override;
    // 返回表格的列数
    int      columnCount(const QModelIndex & parent = QModelIndex()) const override;
    // data 返回指定索引和角色的数据
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    // cloumn name 返回表格表头的数据
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void updateMonitorInfo(const monitor::proto::MonitorInfo & monitor_info);

  private:
    std::vector<QVariant>              insertOneMemInfo(const monitor::proto::MemInfo & mem_info);
    std::vector<std::vector<QVariant>> monitor_data_;
    QStringList                        header_;

    std::vector<QVariant> mem_info_;  // 当前的内存信息

    enum MemInfo {
        USED_PERCENT,
        TOTAL,
        FREE,
        AVAIL,
        BUFFERS,
        CACHED,
        SWAP_CACHED,
        ACTIVE,
        INACTIVE,
        ACTIVE_ANON,
        INACTIVE_ANON,
        DIRTY,
        WRITEBACK,
        ANON_PAGES,
        MAPPED,
        KRECLAIMABLE,
        SRECLAIMABLE,
        SUNRECLAIM,
        COLUMN_MAX
    };
};

}  // namespace monitor

#endif
