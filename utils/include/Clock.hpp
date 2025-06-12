#ifndef CLOCK_H_
#define CLOCK_H_

#include <chrono>

using std::chrono::steady_clock::time_point;

namespace monitor {

class Clock {
 public:
  // 返回两个时间点的间隔
  static double SteadyTimeSecond(const time_point &start,
                                 const time_point &end) {
    return std::chrono::duration<double>(end - start).count();
  }
};

}  // namespace monitor

#endif