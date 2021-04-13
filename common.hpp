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
double rad2deg(double);                     // ラジアン -> 度 変換
std::string deg2hms(double);                // 度 -> hms 変換

}  // namespace calc_greenwich

#endif

