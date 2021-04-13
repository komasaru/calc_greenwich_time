#include "common.hpp"

namespace calc_greenwich {

// -------------------------------------
//   Constants
// -------------------------------------
static constexpr double kPi    = atan(1.0) * 4;  // PI
static constexpr double kPi180 = kPi / 180.0;    // PI / 180

// -------------------------------------
//   Functions
// -------------------------------------
/*
 * @brief      ラジアン -> 度 変換
 *
 * @param[in]  ラジアン (double)
 * @return     度 (double)
 */
double rad2deg(double rad) {
  double deg;

  try {
    deg = rad / kPi180;
  } catch (...) {
    throw;
  }

  return deg;
}

/*
 * @brief      度 -> hms 変換
 *
 * @param[in]  度 (double)
 * @return     時間(hms)文字列 (string)
 */
std::string deg2hms(double deg) {
  std::stringstream ss;
  std::string sign("");
  unsigned int h;
  double _m;
  unsigned int m;
  double s;
  std::string hms;

  try {
    h = (deg / 15.0);
    _m = (deg - h * 15.0) * 4.0;
    m = _m;
    s = (_m - m) * 60.0;
    if (s < 0.0) {
      s *= -1.0;
      sign = "-";
    }
    ss << std::setw(1) << sign
       << std::setfill('0')
       << std::setw(2) << h << " h "
       << std::setw(2) << m << " m "
       << std::fixed << std::setprecision(3)
       << std::setw(6) << s << " s";
    hms = ss.str();
  } catch (...) {
    throw;
  }

  return hms;
}

}  // namespace calc_greenwich

