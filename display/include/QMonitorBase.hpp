#ifndef Q_MONITOR_BASE_
#define Q_MONITOR_BASE_

#include <QAbstractTableModel>
#include <QColor>
#include <QFont>
#include <QObject>

/// 接口类

namespace monitor {

class QMonitorBase : public QAbstractTableModel {
    Q_OBJECT
  private:
    QFont         headerFont;
    QColor        headerBackgroundColor;
    QColor        textColor;
    QColor        backgroundColor;
    Qt::Alignment textAlignment;
  public:
    explicit QMonitorBase(QObject * parent = nullptr) : QAbstractTableModel(parent) {
        // 初始化表头字体
        // headerFont.setFamily("WenQuanYi Micro Hei");
        // if (!headerFont.exactMatch()) {
        //     headerFont.setFamily("WenQuanYi Micro Hei");
        // }
        headerFont.setPointSize(15);
        headerFont.setWeight(QFont::Bold);

        // 初始化表头背景颜色
        headerBackgroundColor = QColor(Qt::lightGray);

        // 初始化文本颜色
        textColor = QColor(Qt::black);

        // 初始化背景颜色
        backgroundColor = QColor(Qt::white);

        // 初始化文本对齐方式
        textAlignment = Qt::AlignLeft | Qt::AlignVCenter;
    }

    virtual ~QMonitorBase() {}

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

}  // namespace monitor

#endif
