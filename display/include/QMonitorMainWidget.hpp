#ifndef Q_MONITOR_MAIN_WIDGET_
#define Q_MONITOR_MAIN_WIDGET_

#include "monitor.grpc.pb.h"
#include "QCpuInfoModel.hpp"

#include <QStandardItemModel>
#include <QtWidgets>
#include <string>
#include <thread>

namespace monitor {

class QMonitorMainWidget : public QWidget {
    Q_OBJECT

  public:
    // explicit QMonitorMainWidget(QWidget * parent = nullptr);

    explicit QMonitorMainWidget(const std::string & name, QWidget * parent = nullptr);

    ~QMonitorMainWidget();

    // QWidget * showAllMonitorWidget(const std::string & name);

    // 各个要监控的信息
    QWidget * initCpuMonitorWidget();
    // QWidget * initCpuLoad();

    QWidget * initButtonMenu(const std::string & name);

    // 更新所有models的数据
    void updateData(const monitor::proto::MonitorInfo & monitor_info);

  private slots:
    void clickCpuButton();

  private:
    // 进行视图展示，展示models
    // QTableView * monitor_view_  = nullptr;
    QTableView * cpu_info_view_ = nullptr;

    // 菜单栏，进行页面跳转
    QStackedLayout * stack_content_ = nullptr;

    /// 所有数据模型
    QCpuInfoModel * cpu_info_model_ = nullptr;
};

}  // namespace monitor

#endif
