#ifndef CLOCK_H_
#define CLOCK_H_

#include <chrono>


namespace util {

class Clock {
 public:

  using TimePoint = std::chrono::steady_clock::time_point;
  
  // 返回两个时间点的间隔
  static double SteadyTimeSecond(const TimePoint &start,
                                 const TimePoint &end) {
    return std::chrono::duration<double>(end - start).count();
  }
};

}  // namespace util

#endif