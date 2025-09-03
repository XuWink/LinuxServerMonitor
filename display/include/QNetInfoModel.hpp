#ifndef Q_NET_INFO_MODEL_
#define Q_NET_INFO_MODEL_

#include "Logger.hpp"
#include "monitor.grpc.pb.h"
#include "QMonitorBase.hpp"

#include <vector>

namespace monitor {
class QNetInfoModel : public QMonitorBase {
    Q_OBJECT

  public:
    explicit QNetInfoModel(QObject * parent = nullptr);
    ~QNetInfoModel();

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
    enum NetModelInfo { NAME = 0, SEND_RATE, RCV_RATE, SEND_PACKETS_RATE, RCV_PACKETS_RATE, COLUMN_MAX };

    std::vector<QVariant>              insertOneNetInfo(const monitor::proto::NetInfo & net_info);
    std::vector<std::vector<QVariant>> monitor_data_;
    QStringList                        header_;
};

}  // namespace monitor

#endif
