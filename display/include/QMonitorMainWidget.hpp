#include "QCpuInfoModel.hpp"

#include <QStandardItemModel>
#include <QtWidgets>
#include <string>
#include <thread>

namespace monitor {

class QMonitorMainWidget : public QWidget {
    Q_OBJECT

  public:
    explicit QMonitorMainWidget(QWidget * parent = nullptr);

    ~QMonitorMainWidget() {}

    QWidget * showAllMonitorWidget(const std::string & name);
    QWidget * initCpuInfoWidget();

    void updateData(const monitor::proto::MonitorInfo & monitor_info);

  private slots:
    void clickCpuButton();

  private:
    QTableView * cpu_info_view_ = nullptr;

    QStackedLayout * stack_menu_ = nullptr;

    /// 所有数据模型
    QCpuInfoModel * cpu_info_model_ = nullptr;
};

}  // namespace monitor
