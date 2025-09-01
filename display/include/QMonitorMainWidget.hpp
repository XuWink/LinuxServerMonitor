#ifndef Q_MONITOR_MAIN_WIDGET_
#define Q_MONITOR_MAIN_WIDGET_

#include "Logger.hpp"
#include "monitor.grpc.pb.h"
#include "QCpuInfoModel.hpp"
#include "QCpuLoadModel.hpp"
#include "QCpuSoftIrqsModel.hpp"
#include "QMemInfoModel.hpp"

#include <QStandardItemModel>
#include <QtWidgets>
#include <sstream>
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
    QWidget * initSoftIrqsMonitorWidget();
    QWidget * initMemInfoMonitorWidget();
    QWidget * initButtonMenu(const std::string & name);

    // 更新所有models的数据
    void updateData(const monitor::proto::MonitorInfo & monitor_info);

  private slots:
    void clickCpuButton();
    void clickSoftIrqButton();
    void clickMemInfoButton();

    void setupTableViewStyle(QTableView * tableView, const QFont & font);

  private:
    // 进行视图展示，展示models
    // QTableView * monitor_view_  = nullptr;
    QTableView * cpu_info_view_     = nullptr;
    QTableView * cpu_load_view_     = nullptr;
    QTableView * cpu_softirqs_view_ = nullptr;
    QTableView * mem_info_view_     = nullptr;

    // 所有数据模型
    QCpuInfoModel *     cpu_info_model_     = nullptr;
    QCpuLoadModel *     cpu_load_model_     = nullptr;
    QCpuSoftIrqsModel * cpu_softirqs_model_ = nullptr;
    QMemInfoModel *     mem_model_          = nullptr;

    // 菜单栏，进行页面跳转
    QStackedLayout * stack_content_ = nullptr;

    void setWindowSize();
};

}  // namespace monitor

#endif
