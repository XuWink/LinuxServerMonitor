#include <thread>
#include <gtest/gtest.h>
#include "Clock.hpp"

TEST(ClockTest, SteadyTimeSecond) {
  // 获取开始时间点
  auto start = std::chrono::steady_clock::now();

  // 模拟耗时操作（例如休眠1000毫秒）
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  // 获取结束时间点
  auto end = std::chrono::steady_clock::now();

  // 计算时间差（单位：秒）
  double diff_seconds = Clock::SteadyTimeSecond(start, end);

  // 验证时间差是否在合理范围内（允许±10毫秒误差）
  EXPECT_NEAR(diff_seconds, 0.1, 0.01);  // 0.1秒 ± 0.01秒
}