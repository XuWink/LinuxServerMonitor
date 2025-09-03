#ifndef WORKER_
#define WORKER_
#include "QMonitorMainWidget.hpp"
#include "RpcClient.hpp"

#include <QObject>
#include <QTimer>

namespace monitor {

class MonitorWorker : public QObject {
    Q_OBJECT
  public:
    explicit MonitorWorker(QObject * parent = nullptr);
    ~MonitorWorker();

  public slots:
    void startPolling();
    void stopPolling();

  signals:
    void newDataArrived(const monitor::proto::MonitorInfo & info);

  private:
    void doPoll();  // 真正干活的函数

    monitor::RpcClient client_;
    QTimer             pollTimer_;  // 放在 worker 线程里
    std::atomic_bool   running_{ false };
};

}  // namespace monitor

#endif