#include "QMonitorMainWidget.hpp"
#include "Worker.hpp"

#include <QApplication>
#include <QMetaType>
#include <thread>

// 注册类型，程序启动时执行一次
Q_DECLARE_METATYPE(monitor::proto::MonitorInfo)

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);

    // 设置全局字体
    QFont grobalFont("Microsoft YaHei", 10);
    if (!grobalFont.exactMatch()) {
        grobalFont.setFamily("WenQuanYi Micro Hei");
    }
    qApp->setFont(grobalFont);

    qRegisterMetaType<monitor::proto::MonitorInfo>();  // 关键

    /* 1. 提前取一次 MonitorInfo，拿到 name */
    monitor::RpcClient          rpc_client;
    monitor::proto::MonitorInfo monitor_info;
    if (!rpc_client.GetMonitorInfo(&monitor_info)) {  // 根据你实际接口返回 bool 或抛异常
        qCritical() << "GetMonitorInfo failed!";
        return -1;
    }
    const std::string name = monitor_info.name();  // 这里就拿到 name 了
    std::cout << "主机名：" << name << std::endl;

    // 1. GUI
    monitor::QMonitorMainWidget monitor_widget(name);
    monitor_widget.show();

    // 2. 创建工作对象 + 线程
    QThread                workerThread;
    monitor::MonitorWorker worker;  // 继承 QObject，内部持 RpcClient
    worker.moveToThread(&workerThread);

    // 3. 关联：worker 拉取到数据 → 通知 GUI 刷新
    bool ok = QObject::connect(&worker,
                               &monitor::MonitorWorker::newDataArrived,
                               &monitor_widget,
                               &monitor::QMonitorMainWidget::updateData,
                               Qt::QueuedConnection);
    // qDebug() << "Connect success? : " << ok;

    // 4. 启动 & 计时器
    QObject::connect(&workerThread, &QThread::started, &worker, &monitor::MonitorWorker::startPolling);

    // 5. 优雅退出
    QObject::connect(&app, &QApplication::aboutToQuit, [&] {
        worker.stopPolling();
        workerThread.quit();
        workerThread.wait();
    });

    workerThread.start();

    return app.exec();
}
