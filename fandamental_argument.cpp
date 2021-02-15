#include "fandamental_argument.hpp"

namespace calc_greenwich {

// 定数
static constexpr double kPi     = atan(1.0) * 4;           // PI
static constexpr double kPi2    = kPi * 2;                 // PI * 2
static constexpr double kAs2R   = kPi / (3600.0 * 180.0);  // arcseconds -> radians
static constexpr double kTurnas = 1296000.0;               // Arcseconds in a full circle

/*
 * @brief      Mean anomaly of the Moon (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     l(unit: rad)(double)
 */
double calc_l_iers2003(double t) {
  double v;

  try {
    v = (    485868.249036  +
        (1717915923.2178    +
        (        31.8792    +
        (         0.051635  +
        (        -0.00024470)
      * t) * t) * t) * t);
    v = fmod_p(v, kTurnas) * kAs2R;
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      Mean anomaly of the Sun (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     p(unit: rad)(double)
 */
double calc_p_iers2003(double t) {
  double v;

  try {
    v = (  1287104.793048  +
        (129596581.0481    +
        (      - 0.5532    +
        (        0.000136  +
        (      - 0.00001149)
      * t) * t) * t) * t);
    v = fmod_p(v, kTurnas) * kAs2R;
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      Mean longitude of the Moon minus that of the ascending node (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     f(unit: rad)(double)
 */
double calc_f_iers2003(double t) {
  double v;

  try {
    v = (     335779.526232 +
        (1739527262.8478    +
        (       -12.7512    +
        (        -0.001037  +
        (         0.00000417)
      * t) * t) * t) * t);
    v = fmod_p(v, kTurnas) * kAs2R;
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      Mean elongation of the Moon from the Sun (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     d(unit: rad)(double)
 */
double calc_d_iers2003(double t) {
  double v;

  try {
    v = (   1072260.703692  +
        (1602961601.2090    +
        (       - 6.3706    +
        (         0.006593  +
        (       - 0.00003169)
      * t) * t) * t) * t);
    v = fmod_p(v, kTurnas) * kAs2R;
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      Mean longitude of the ascending node of the Moon (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     om(unit: rad)(double)
 */
double calc_om_iers2003(double t) {
  double v;

  try {
    v = (  450160.398036  +
        (-6962890.5431    +
        (       7.4722    +
        (       0.007702  +
        (      -0.00005939)
      * t) * t) * t) * t);
    v = fmod_p(v, kTurnas) * kAs2R;
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      Venus longitudes (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     ve(unit: rad)(double)
 */
double calc_ve_iers2003(double t) {
  double v;

  try {
    v = fmod_p(3.176146697 + 1021.3285546211 * t, kPi2);
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      Earth longitudes (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     ea(unit: rad)(double)
 */
double calc_ea_iers2003(double t) {
  double v;

  try {
    v = fmod_p(1.753470314 + 628.3075849991 * t, kPi2);
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      General accumulated precession in longitude (IERS 2003)
 *
 * @param[in]  ユリウス世紀数 T(JCN)(double)
 * @return     pa(unit: rad)(double)
 */
double calc_pa_iers2003(double t) {
  double v;

  try {
    v = (0.024381750 + 0.00000538691 * t) * t;
  } catch (...) {
    throw;
  }

  return v;
}

/*
 * @brief      正剰余計算
 *             （std::fmod が正剰余に非対応のため）
 *
 * @param[in]  被除数(double)
 * @param[in]  除数(double)
 * @return     計算後の値(double)
 */
double fmod_p(double a, double n) {
  try {
    return a - std::floor(a / n) * n;
  } catch (...) {
    throw;
  }
}

}  // namespace calc_greenwich

