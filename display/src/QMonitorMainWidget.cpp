#include "QMonitorMainWidget.hpp"

namespace monitor {

// QMonitorMainWidget::QMonitorMainWidget(QWidget * parent) {}

QMonitorMainWidget::QMonitorMainWidget(const std::string & name, QWidget * parent) : QWidget(parent) {
    stack_content_ = new QStackedLayout;

    // 添加监控页面
    stack_content_->addWidget(initCpuMonitorWidget());
    // stack_content_->addWidget(initSoftIrqWidget());

    // 组装主界面
    auto * mainLayout = new QGridLayout(this);
    mainLayout->addWidget(initButtonMenu(name), 0, 0);
    mainLayout->addLayout(stack_content_, 1, 0);
}

QMonitorMainWidget::~QMonitorMainWidget() {}

// QWidget * QMonitorMainWidget::showAllMonitorWidget(const std::string & name) {
//     QWidget * widget = new QWidget();
//     stack_content_   = new QStackedLayout();
//     // 初始化各个信息
//     stack_content_->addWidget(initCpuWidget());

//     auto * mainLayout = new QGridLayout(this);
//     // 初始化菜单按钮
//     mainLayout->addWidget(initButtonMenu(name), 1, 0);
//     // 按钮点击进行内容展示
//     mainLayout->addWidget(stack_content_, 2, 0);
//     widget->setLayout(layout);
//     return widget;
// }

QWidget * QMonitorMainWidget::initCpuMonitorWidget() {
    // 顶层容器指定为父对象，qt自动析构
    QWidget * page = new QWidget(this);

    // 统一字体
    QFont labelFont("Microsoft YaHei", 10, QFont::Bold);

    // CPU INFO
    QLabel * cpu_info_label = new QLabel(tr("CPU 信息："), page);
    cpu_info_label->setFont(labelFont);

    cpu_info_view_  = new QTableView(page);
    cpu_info_model_ = new QCpuInfoModel(this);
    cpu_info_view_->setModel(cpu_info_model_);

    cpu_info_view_->setAlternatingRowColors(true);                                   // 斑马线效果
    cpu_info_view_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // 所有列宽拉伸
    cpu_info_view_->setSelectionBehavior(QAbstractItemView::SelectRows);             // 点击选择整行
    // cpu_info_view->setFont();

    QGridLayout * layout = new QGridLayout(page);

    int row = 0;
    layout->addWidget(cpu_info_label, row, 0);
    layout->addWidget(cpu_info_view_, row + 1, 0, 1, 2);

    // 设置布局间距（可选）
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setVerticalSpacing(8);

    // row += 2;
    // layout->addWidget(cpuLoadLabel, row, 0);
    // layout->addWidget(cpu_load_monitor_view_, row + 1, 0, , 2, 2);

    return page;
}

QWidget * QMonitorMainWidget::initButtonMenu(const std::string & name) {
    // 1. 预定义按钮列表，后期只需要在这一个地方增删
    struct ButtonInfo {
        QString suffix;                      // 按钮后缀
        void (QMonitorMainWidget::*slot)();  // 成员函数指针
    };

    const QList<ButtonInfo> infos = {
        { "cpu", &QMonitorMainWidget::clickCpuButton },
        // {"soft_irq", SLOT(clickSoftIrqButton())},
        // {"net", SLOT(clickNetButton())}
    };

    // 2. 用栈对象保存字体，无需手动delete
    static QFont font("Microsoft YaHei", 15, QFont::Medium);

    auto * layout = new QHBoxLayout;
    for (const auto & info : infos) {
        auto * btn = new QPushButton(QString::fromStdString(name) + "_" + info.suffix, this);
        btn->setFont(font);
        btn->setObjectName(info.suffix);
        connect(btn, &QPushButton::clicked, this, info.slot);
        layout->addWidget(btn);
    }

    auto * widget = new QWidget(this);  //指定父对象，qt自动析构
    widget->setLayout(layout);
    return widget;
}

// 更新数据
void QMonitorMainWidget::updateData(const monitor::proto::MonitorInfo & monitor_info) {
    // for (const auto & cpu : monitor_info.cpu_info()) {
    //     std::cout << "cpu名称\t: " << cpu.name() << std::endl;
    //     std::cout << "cpu型号\t: " << cpu.model_name() << std::endl;
    //     std::cout << "cpu频率\t: " << cpu.mhz() << std::endl;
    //     std::cout << "cpu缓存\t: " << cpu.cache_size_kb() << std::endl;
    //     std::cout << "cpu核心\t: " << cpu.core_nums() << std::endl;
    //     std::cout << std::endl;
    // }

    cpu_info_model_->updateMonitorInfo(monitor_info);
}

// 槽函数
void QMonitorMainWidget::clickCpuButton() {
    stack_content_->setCurrentIndex(0);
}

}  // namespace monitor
