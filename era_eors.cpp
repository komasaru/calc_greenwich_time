#include "era_eors.hpp"

namespace calc_greenwich {

// 定数
static constexpr double kJ2K  = 2451545.0;        // Reference epoch (J2000.0), Julian Date
static constexpr double kPi   = atan(1.0) * 4.0;  // PI
static constexpr double kPi2  = kPi * 2;          // PI * 2
static constexpr double kAs2R = kPi / (3600.0 * 180.0);  // arcseconds -> radians

/*
 * @brief      コンストラクタ
 *
 * @param[in]  JD(UT1)(double)
 */
EraEors::EraEors(double jd) {
  this->jd    = jd;
  this->jd_2k = jd - kJ2K;
}

/*
 * @brief   Earth rotation angle 計算
 *          (IAU 2000 model)
 *
 * @param   <none>
 * @return  ERA(double)
 */
double EraEors::calc_era() {
  double f;  // Fractional part of T (days).
  double era;

  try {
    f = fmod(jd, 1.0);
    era = (f + 0.7790572732640 + 0.00273781191135448 * jd_2k) * kPi2;
    era = norm_angle(era);
  } catch (...) {
    throw;
  }

  return era;
}

/*
 * @brief       Equation of the origins 計算
 *              (given the classical NPB matrix and the quantity s.)
 *
 * @param[in]   CIO locator(double)
 * @param[ref]  回転行列(double[3][3])
 * @return      EO(double)
 */
double EraEors::calc_eo(double s, double(&r_mtx)[3][3]) {
  double x;
  double ax;
  double xs;
  double ys;
  double zs;
  double p;
  double q;
  double eo;

  try {
    x = r_mtx[2][0];
    ax = x / (1.0 + r_mtx[2][2]);
    xs = 1.0 - ax * x;
    ys = -ax * r_mtx[2][1];
    zs = -x;
    p = r_mtx[0][0] * xs + r_mtx[0][1] * ys + r_mtx[0][2] * zs;
    q = r_mtx[1][0] * xs + r_mtx[1][1] * ys + r_mtx[1][2] * zs;
    if (p != 0.0 || q != 0.0) {
      eo = s - atan2(q, p);
    } else {
      eo = s;
    }
  } catch (...) {
    throw;
  }

  return eo;
}

/*
 * @brief      Greenwich apparent sidereal time 計算
 *
 * @param[in]  Earth rotation angle(double)
 * @param[in]  Equation of the origin(double)
 * @return     GAST(double)
 */
double EraEors::calc_gast(double era, double eo) {
  return norm_angle(era - eo);
}

/*
 * @brief      Greenwich mean sidereal time 計算
 *
 * @param[in]  Earth rotation angle(double)
 * @param[in]  Julian century number(double)
 * @return     GMST(double)
 */
double EraEors::calc_gmst(double era, double jcn) {
  double gmst;

  try {
    gmst = era +
           (   0.014506    +
           (4612.156534    +
           (   1.3915817   +
           (  -0.00000044  +
           (  -0.000029956 +
           (  -0.0000000368)
         * jcn) * jcn) * jcn) * jcn) * jcn) * kAs2R;
    gmst = norm_angle(gmst);
  } catch (...) {
    throw;
  }

  return gmst;
}

/*
 * @brief      Equation of equinoxes 計算
 *
 * @param[in]  Greenwich apparent sidereal time(double)
 * @param[in]  Greenwich mean sidereal time(double)
 * @return     EE(double)
 */
double EraEors::calc_ee(double gast, double gmst) {
  return gast - gmst;
}

// -------------------------------------
// 以下、 private functions
// -------------------------------------

/*
 * @brief      Normalize angle into the range 0 <= a < 2pi.
 *
 * @param[in]  角度（正規化前）(double)
 * @return     角度（正規化後）(double)
 */
double EraEors::norm_angle(double ang) {
  try {
    while (ang <    0) { ang += kPi2; }
    while (ang > kPi2) { ang -= kPi2; }
  } catch (...) {
    throw;
  }

  return ang;
}

}  // namespace calc_greenwich

