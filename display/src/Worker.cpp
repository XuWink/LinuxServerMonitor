#include "Worker.hpp"

#include <QThread>

namespace monitor {

MonitorWorker::MonitorWorker(QObject * parent) : QObject(parent), pollTimer_(this) {
    connect(&pollTimer_, &QTimer::timeout, this, &MonitorWorker::doPoll);
}

void MonitorWorker::startPolling() {
    if (running_) {
        return;  // 避免重复调用
    }
    running_ = true;
    doPoll();                // 立即拉一次
    pollTimer_.start(2000);  // 每 2 秒
}

void MonitorWorker::stopPolling() {
    running_ = false;
    pollTimer_.stop();
}

void MonitorWorker::doPoll() {
    if (!running_) {
        return;
    }

    monitor::proto::MonitorInfo info;
    try {
        client_.GetMonitorInfo(&info);
    } catch (const std::exception & e) {
        Logger::getInstance().error(QString("RPC failed: %1").arg(e.what()).toStdString());
        return;
    }
    // qDebug() << "Emit newDataArrived";
    emit newDataArrived(info);
}

}  // namespace monitor
