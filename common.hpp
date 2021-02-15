#ifndef CALC_GREENWICH_COMMON_HPP_
#define CALC_GREENWICH_COMMON_HPP_

#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

namespace calc_greenwich {

// -------------------------------------
//   Functions
// -------------------------------------
struct timespec jst2utc(struct timespec);   // JST -> UTC 変換
std::string gen_time_str(struct timespec);  // 日時文字列生成
double rad2deg(double);                     // ラジアン -> 度 変換
std::string deg2hms(double);                // 度 -> hms 変換

}  // namespace calc_greenwich

#endif

