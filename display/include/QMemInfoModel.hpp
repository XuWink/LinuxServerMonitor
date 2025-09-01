#ifndef Q_MEM_INFO_MODEL_
#define Q_MEM_INFO_MODEL_

#include "QMonitorBase.hpp"

namespace monitor {
class QMemInfoModel : public QMonitorBase {
    Q_OBJECT
  public:
    explicit QMemInfoModel(QObject * parent = nullptr);
    virtual ~QMemInfoModel();


  private:
};

}  // namespace monitor

#endif
