#include "QMonitorMainWidget.hpp"

namespace monitor {

QMonitorMainWidget::QMonitorMainWidget(const std::string & name, QWidget * parent) : QWidget(parent) {
    stack_content_ = new QStackedLayout;

    // 添加监控页面
    stack_content_->addWidget(initCpuMonitorWidget());
    stack_content_->addWidget(initSoftIrqsMonitorWidget());
    stack_content_->addWidget(initMemInfoMonitorWidget());
    stack_content_->addWidget(initNetInfoMonitorWidget());

    // 组装主界面
    auto * mainLayout = new QGridLayout(this);
    mainLayout->addWidget(initButtonMenu(name), 0, 0);
    mainLayout->addLayout(stack_content_, 1, 0);

    setWindowSize();
}

QMonitorMainWidget::~QMonitorMainWidget() {}

QWidget * QMonitorMainWidget::initCpuMonitorWidget() {
    // 创建顶层容器，指定父对象以便 Qt 自动析构
    QWidget * page = new QWidget(this);
    page->setObjectName("cpuMonitorPage");
    page->setStyleSheet("#cpuMonitorPage { background-color: #f5f5f5; border-radius: 4px; }");

    // 统一字体设置
    QFont labelFont("Microsoft YaHei", 10, QFont::Bold);
    QFont tableFont("Microsoft YaHei", 9);

    // ==================== CPU 信息区域 ====================
    QLabel * cpuInfoLabel = new QLabel(tr("CPU 信息："), page);
    cpuInfoLabel->setFont(labelFont);
    cpuInfoLabel->setStyleSheet("color: #333333; padding: 4px 0;");

    cpu_info_view_  = new QTableView(page);
    cpu_info_model_ = new QCpuInfoModel(this);
    cpu_info_view_->setModel(cpu_info_model_);

    // 表格样式设置
    setupTableViewStyle(cpu_info_view_, tableFont);

    // ==================== CPU 负载区域 ====================
    QLabel * cpuLoadLabel = new QLabel(tr("CPU 负载："), page);
    cpuLoadLabel->setFont(labelFont);
    cpuLoadLabel->setStyleSheet("color: #333333; padding: 4px 0;");

    cpu_load_view_  = new QTableView(page);
    cpu_load_model_ = new QCpuLoadModel(this);
    cpu_load_view_->setModel(cpu_load_model_);

    // 表格样式设置（复用通用配置）
    setupTableViewStyle(cpu_load_view_, tableFont);
    cpu_load_view_->verticalHeader()->setVisible(false);  // 只有一行，隐藏行号

    // ==================== 布局设置 ====================
    QGridLayout * layout = new QGridLayout(page);
    int           row    = 0;

    layout->addWidget(cpuInfoLabel, row, 0);
    layout->addWidget(cpu_info_view_, row + 1, 0, 1, 2);
    row += 2;

    layout->addWidget(cpuLoadLabel, row, 0);
    layout->addWidget(cpu_load_view_, row + 1, 0, 1, 2);
    row += 2;

    // 布局边距和间距设置
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setVerticalSpacing(8);
    layout->setHorizontalSpacing(5);

    return page;
}

QWidget * QMonitorMainWidget::initSoftIrqsMonitorWidget() {
    // 创建顶层容器，指定父对象（当前窗口），确保Qt自动析构
    QWidget * widget = new QWidget(this);
    widget->setObjectName("softIrqsMonitorPage");
    widget->setStyleSheet("#softIrqsMonitorPage { background-color: #f5f5f5; border-radius: 4px; }");

    // 统一字体设置（与CPU监控页保持一致）
    QFont labelFont("Microsoft YaHei", 10, QFont::Bold);
    QFont tableFont("Microsoft YaHei", 9);

    // ==================== 中断信息区域 ====================
    QLabel * softirqsLabel = new QLabel(tr("系统软中断信息："), widget);
    softirqsLabel->setFont(labelFont);
    softirqsLabel->setStyleSheet("color: #333333; padding: 4px 0;");

    // 表格视图与模型（使用成员变量存储，确保生命周期正确）
    cpu_softirqs_view_  = new QTableView(widget);
    // 模型指定父对象为当前窗口，避免内存泄漏
    cpu_softirqs_model_ = new QCpuSoftIrqsModel(this);

    // 排序代理模型（修复原代码中类型错误，正确关联源模型）
    QSortFilterProxyModel * sortProxy = new QSortFilterProxyModel(this);
    sortProxy->setSourceModel(cpu_softirqs_model_);  // 关联自定义模型
    cpu_softirqs_view_->setModel(sortProxy);         // 视图使用代理模型实现排序

    // 启用排序功能（需配合代理模型）
    cpu_softirqs_view_->setSortingEnabled(true);

    // 复用表格样式设置（与CPU监控页保持一致）
    setupTableViewStyle(cpu_softirqs_view_, tableFont);

    // ==================== 布局设置 ====================
    QGridLayout * layout = new QGridLayout(widget);
    int           row    = 0;  // 用行号变量管理布局，避免硬编码

    layout->addWidget(softirqsLabel, row, 0);
    layout->addWidget(cpu_softirqs_view_, row + 1, 0, 1, 2);  // 占2列，与CPU监控页布局对齐
    row += 2;

    // 布局边距和间距（与CPU监控页保持一致，统一视觉风格）
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setVerticalSpacing(8);
    layout->setHorizontalSpacing(5);

    return widget;
}

QWidget * QMonitorMainWidget::initMemInfoMonitorWidget() {
    QWidget * widget = new QWidget(this);
    widget->setObjectName("memInfoMonitorPage");
    widget->setStyleSheet("#memInfoMonitorPage { background-color: #f5f5f5; border-radius: 4px; }");

    // 统一字体设置，便于后续维护
    QFont labelFont("WenQuanYi Micro Hei", 10, QFont::Bold);  // 使用文泉驿字体确保中文显示
    QFont tableFont("WenQuanYi Micro Hei", 9);

    // 内存信息标题标签（修正变量名与用途一致）
    QLabel * memLabel = new QLabel(tr("内存信息："), widget);
    memLabel->setFont(labelFont);
    memLabel->setStyleSheet("color: #333333; padding: 4px 0;");

    // 初始化表格视图和模型
    mem_info_view_ = new QTableView(widget);
    mem_model_     = new QMemInfoModel(this);
    mem_info_view_->setModel(mem_model_);

    // 优化表格显示效果
    mem_info_view_->horizontalHeader()->setVisible(false);
    mem_info_view_->horizontalHeader()->setStretchLastSection(true);  // 最后一列自适应
    mem_info_view_->setAlternatingRowColors(true);                    // 交替行颜色，提升可读性
    mem_info_view_->setStyleSheet("QTableView { border: 1px solid #ddd; border-radius: 2px; }");

    // 布局管理（修正变量引用不一致问题）
    QGridLayout * layout = new QGridLayout(widget);
    layout->setContentsMargins(10, 10, 10, 10);  // 设置边距
    layout->setSpacing(8);                       // 设置控件间距
    layout->addWidget(memLabel, 0, 0);           // 从第0行开始布局，更符合常规习惯
    layout->addWidget(mem_info_view_, 1, 0);     // 表格控件占满一行

    widget->setLayout(layout);
    return widget;
}

// todo
QWidget * QMonitorMainWidget::initNetInfoMonitorWidget() {
    QWidget * widget = new QWidget(this);
    widget->setObjectName("netInfoMonitorWidgetPage");

    QLabel * netLabel = new QLabel(tr("网络信息："), widget);
    netLabel->setStyleSheet("color: #333333; padding: 4px 0;");

    net_info_view_  = new QTableView(widget);
    net_info_model_ = new QNetInfoModel(net_info_view_);  // 将模型父对象设为视图，便于自动释放
    net_info_view_->setModel(net_info_model_);
    QFont tableFont("WenQuanYi Micro Hei", 9);
    setupTableViewStyle(net_info_view_, tableFont);

    QGridLayout * layout = new QGridLayout(widget);
    layout->setContentsMargins(10, 10, 10, 10);  // 设置边距
    layout->setSpacing(8);                       // 设置控件间距
    layout->addWidget(netLabel, 1, 0);           // 从第0行开始布局，更符合常规习惯
    layout->addWidget(net_info_view_, 2, 0);     // 表格控件占满一行

    return widget;
}

// 表格样式设置的通用函数
void QMonitorMainWidget::setupTableViewStyle(QTableView * tableView, const QFont & font) {
    if (!tableView) {
        return;
    }

    tableView->setFont(font);
    tableView->setAlternatingRowColors(true);
    tableView->setStyleSheet(
        "QTableView { background-color: #ffffff; border: 1px solid #dddddd; "
        "border-radius: 3px; gridline-color: #eeeeee; }"
        "QTableView::alternatingRowColors { background-color: #f9f9f9; }"
        "QHeaderView::section { background-color: #f0f0f0; border: 1px solid #dddddd; "
        "padding: 4px; font-weight: bold; }");

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 禁止编辑
    tableView->setFocusPolicy(Qt::NoFocus);                         // 去掉选中时的焦点框
    tableView->verticalHeader()->setDefaultSectionSize(25);         // 设置行高
}

QWidget * QMonitorMainWidget::initButtonMenu(const std::string & name) {
    // 1. 预定义按钮列表，后期只需要在这一个地方增删
    struct ButtonInfo {
        QString suffix;                      // 按钮后缀
        void (QMonitorMainWidget::*slot)();  // 成员函数指针
    };

    const QList<ButtonInfo> infos = {
        { "cpu",      &QMonitorMainWidget::clickCpuButton     },
        { "软中断",   &QMonitorMainWidget::clickSoftIrqButton },
        { "内存信息", &QMonitorMainWidget::clickMemInfoButton },
        { "网络信息", &QMonitorMainWidget::clickNetInfoButton }
    };

    // 2. 用栈对象保存字体，无需手动delete
    static QFont font("Microsoft YaHei", 15, QFont::Medium);

    auto * layout = new QHBoxLayout;
    for (const auto & info : infos) {
        auto * btn = new QPushButton(info.suffix, this);
        // auto * btn = new QPushButton(QString::fromStdString(name) + "_" + info.suffix, this);
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
    cpu_info_model_->updateMonitorInfo(monitor_info);
    cpu_load_model_->updateMonitorInfo(monitor_info);
    cpu_softirqs_model_->updateMonitorInfo(monitor_info);
    mem_model_->updateMonitorInfo(monitor_info);
    net_info_model_->updateMonitorInfo(monitor_info);
}

// 槽函数
void QMonitorMainWidget::clickCpuButton() {
    stack_content_->setCurrentIndex(0);
}

void QMonitorMainWidget::clickSoftIrqButton() {
    stack_content_->setCurrentIndex(1);
}

void QMonitorMainWidget::clickMemInfoButton() {
    stack_content_->setCurrentIndex(2);
}

void QMonitorMainWidget::clickNetInfoButton() {
    stack_content_->setCurrentIndex(3);
}

void QMonitorMainWidget::setWindowSize() {
    // 设置最小尺寸（宽不小于 400，高不小于 300）
    setMinimumSize(400, 300);

    // 设置最大尺寸（宽不大于 1200，高不大于 900）
    setMaximumSize(1200, 900);

    // 初始大小设为 800x600（在最小和最大之间）
    resize(1600, 600);
}

}  // namespace monitor
