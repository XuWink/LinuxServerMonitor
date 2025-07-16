#ifndef Q_MONITOR_BASE_
#define Q_MONITOR_BASE_

#include <QAbstractTableModel>
#include <QObject>

namespace monitor {

class QMonitorBase : public QAbstractTableModel {
  Q_OBJECT
 private:
  /* data */
 public:
  explicit QMonitorBase(QObject *parent = nullptr)
      : QAbstractTableModel(parent) {};
  virtual ~QMonitorBase() {};
};

}  // namespace monitor

#endif