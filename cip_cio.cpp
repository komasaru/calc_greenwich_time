#include "cip_cio.hpp"

namespace calc_greenwich {

// 定数
static constexpr double kPi   = atan(1.0) * 4;           // PI
static constexpr double kAs2R = kPi / (3600.0 * 180.0);  // arcseconds -> radians
// Polynomial coefficients
static constexpr double kSp[6] = {
  94.00e-6, 3808.65e-6, -122.68e-6, -72574.11e-6, 27.98e-6, 15.62e-6
};
// Terms of order t^0
static constexpr double kS0[33][10] = {
  {0,  0,  0,  0,  1,  0,  0,  0, -2640.73e-6,  0.39e-6},
  {0,  0,  0,  0,  2,  0,  0,  0,   -63.53e-6,  0.02e-6},
  {0,  0,  2, -2,  3,  0,  0,  0,   -11.75e-6, -0.01e-6},
  {0,  0,  2, -2,  1,  0,  0,  0,   -11.21e-6, -0.01e-6},
  {0,  0,  2, -2,  2,  0,  0,  0,     4.57e-6,  0.00e-6},
  {0,  0,  2,  0,  3,  0,  0,  0,    -2.02e-6,  0.00e-6},
  {0,  0,  2,  0,  1,  0,  0,  0,    -1.98e-6,  0.00e-6},
  {0,  0,  0,  0,  3,  0,  0,  0,     1.72e-6,  0.00e-6},
  {0,  1,  0,  0,  1,  0,  0,  0,     1.41e-6,  0.01e-6},
  {0,  1,  0,  0, -1,  0,  0,  0,     1.26e-6,  0.01e-6},
  {1,  0,  0,  0, -1,  0,  0,  0,     0.63e-6,  0.00e-6},
  {1,  0,  0,  0,  1,  0,  0,  0,     0.63e-6,  0.00e-6},
  {0,  1,  2, -2,  3,  0,  0,  0,    -0.46e-6,  0.00e-6},
  {0,  1,  2, -2,  1,  0,  0,  0,    -0.45e-6,  0.00e-6},
  {0,  0,  4, -4,  4,  0,  0,  0,    -0.36e-6,  0.00e-6},
  {0,  0,  1, -1,  1, -8, 12,  0,     0.24e-6,  0.12e-6},
  {0,  0,  2,  0,  0,  0,  0,  0,    -0.32e-6,  0.00e-6},
  {0,  0,  2,  0,  2,  0,  0,  0,    -0.28e-6,  0.00e-6},
  {1,  0,  2,  0,  3,  0,  0,  0,    -0.27e-6,  0.00e-6},
  {1,  0,  2,  0,  1,  0,  0,  0,    -0.26e-6,  0.00e-6},
  {0,  0,  2, -2,  0,  0,  0,  0,     0.21e-6,  0.00e-6},
  {0,  1, -2,  2, -3,  0,  0,  0,    -0.19e-6,  0.00e-6},
  {0,  1, -2,  2, -1,  0,  0,  0,    -0.18e-6,  0.00e-6},
  {0,  0,  0,  0,  0,  8,-13, -1,     0.10e-6, -0.05e-6},
  {0,  0,  0,  2,  0,  0,  0,  0,    -0.15e-6,  0.00e-6},
  {2,  0, -2,  0, -1,  0,  0,  0,     0.14e-6,  0.00e-6},
  {0,  1,  2, -2,  2,  0,  0,  0,     0.14e-6,  0.00e-6},
  {1,  0,  0, -2,  1,  0,  0,  0,    -0.14e-6,  0.00e-6},
  {1,  0,  0, -2, -1,  0,  0,  0,    -0.14e-6,  0.00e-6},
  {0,  0,  4, -2,  4,  0,  0,  0,    -0.13e-6,  0.00e-6},
  {0,  0,  2, -2,  4,  0,  0,  0,     0.11e-6,  0.00e-6},
  {1,  0, -2,  0, -3,  0,  0,  0,    -0.11e-6,  0.00e-6},
  {1,  0, -2,  0, -1,  0,  0,  0,    -0.11e-6,  0.00e-6}
};
// Terms of order t^1
static constexpr double kS1[3][10] = {
  {0,  0,  0,  0,  2,  0,  0,  0, -0.07e-6,  3.57e-6},
  {0,  0,  0,  0,  1,  0,  0,  0,  1.73e-6, -0.03e-6},
  {0,  0,  2, -2,  3,  0,  0,  0,  0.00e-6,  0.48e-6}
};
// Terms of order t^2
static constexpr double kS2[25][10] = {
  {0,  0,  0,  0,  1,  0,  0,  0, 743.52e-6, -0.17e-6},
  {0,  0,  2, -2,  2,  0,  0,  0,  56.91e-6,  0.06e-6},
  {0,  0,  2,  0,  2,  0,  0,  0,   9.84e-6, -0.01e-6},
  {0,  0,  0,  0,  2,  0,  0,  0,  -8.85e-6,  0.01e-6},
  {0,  1,  0,  0,  0,  0,  0,  0,  -6.38e-6, -0.05e-6},
  {1,  0,  0,  0,  0,  0,  0,  0,  -3.07e-6,  0.00e-6},
  {0,  1,  2, -2,  2,  0,  0,  0,   2.23e-6,  0.00e-6},
  {0,  0,  2,  0,  1,  0,  0,  0,   1.67e-6,  0.00e-6},
  {1,  0,  2,  0,  2,  0,  0,  0,   1.30e-6,  0.00e-6},
  {0,  1, -2,  2, -2,  0,  0,  0,   0.93e-6,  0.00e-6},
  {1,  0,  0, -2,  0,  0,  0,  0,   0.68e-6,  0.00e-6},
  {0,  0,  2, -2,  1,  0,  0,  0,  -0.55e-6,  0.00e-6},
  {1,  0, -2,  0, -2,  0,  0,  0,   0.53e-6,  0.00e-6},
  {0,  0,  0,  2,  0,  0,  0,  0,  -0.27e-6,  0.00e-6},
  {1,  0,  0,  0,  1,  0,  0,  0,  -0.27e-6,  0.00e-6},
  {1,  0, -2, -2, -2,  0,  0,  0,  -0.26e-6,  0.00e-6},
  {1,  0,  0,  0, -1,  0,  0,  0,  -0.25e-6,  0.00e-6},
  {1,  0,  2,  0,  1,  0,  0,  0,   0.22e-6,  0.00e-6},
  {2,  0,  0, -2,  0,  0,  0,  0,  -0.21e-6,  0.00e-6},
  {2,  0, -2,  0, -1,  0,  0,  0,   0.20e-6,  0.00e-6},
  {0,  0,  2,  2,  2,  0,  0,  0,   0.17e-6,  0.00e-6},
  {2,  0,  2,  0,  2,  0,  0,  0,   0.13e-6,  0.00e-6},
  {2,  0,  0,  0,  0,  0,  0,  0,  -0.13e-6,  0.00e-6},
  {1,  0,  2, -2,  2,  0,  0,  0,  -0.12e-6,  0.00e-6},
  {0,  0,  2,  0,  0,  0,  0,  0,  -0.11e-6,  0.00e-6}
};
// Terms of order t^3
static constexpr double kS3[4][10] = {
  {0,  0,  0,  0,  1,  0,  0,  0,  0.30e-6, -23.42e-6},
  {0,  0,  2, -2,  2,  0,  0,  0, -0.03e-6,  -1.46e-6},
  {0,  0,  2,  0,  2,  0,  0,  0, -0.01e-6,  -0.25e-6},
  {0,  0,  0,  0,  2,  0,  0,  0,  0.00e-6,   0.23e-6}
};
// Terms of order t^4
static constexpr double kS4[1][10] = {
  {0,  0,  0,  0,  1,  0,  0,  0, -0.26e-6, -0.01e-6}
};

/*
 * @brief       Extract from the bias-precession-nutation matrix the X,Y coordinates
 *              of the Celestial Intermediate Pole.
 *
 * @param[ref]  回転行列(double[3][3])
 * @param[ref]  x of CIP(double)
 * @param[ref]  y of CIP(double)
 * @return      true|false
 */
bool CipCio::bpn2xy(double(&r)[3][3], double& x, double& y) {
  try {
    x = r[2][0];
    y = r[2][1];
  } catch (...) {
    return false;
  }

  return true;
}

/*
 * @brief      The CIO locator s, positioning the Celestial Intermediate Origin on
 *             the equator of the Celestial Intermediate Pole, given the CIP's X,Y
 *             coordinates.  Compatible with IAU 2006/2000A precession-nutation.
 *
 * @param[in]  X coordinate of CIP(double)
 * @param[in]  Y coordinate of CIP(double)
 * @return     CIO locator s(unit: rad)(double)
 */
double CipCio::calc_s_06(double x, double y) {
  double fas[8];  // fundamental arguments
  double ws[6];   // for work
  double a;       // for work
  int i;          // loop index
  int j;          // loop index
  double s;       // CIO locator

  try {
    fas[0] = calc_l_iers2003(jcn);
    fas[1] = calc_p_iers2003(jcn);
    fas[2] = calc_f_iers2003(jcn);
    fas[3] = calc_d_iers2003(jcn);
    fas[4] = calc_om_iers2003(jcn);
    fas[5] = calc_ve_iers2003(jcn);
    fas[6] = calc_ea_iers2003(jcn);
    fas[7] = calc_pa_iers2003(jcn);
    for (i = 0; i < 6; ++i) ws[i] = kSp[i];
    // Evaluate s
    for (i = 32; i >= 0; --i) {
      a = 0.0;
      for (j = 0; j < 8; ++j) a += kS0[i][j] * fas[j];
      ws[0] += kS0[i][8] * sin(a) + kS0[i][9] * cos(a);
    }
    for (i = 2; i >= 0; --i) {
      a = 0.0;
      for (j = 0; j < 8; ++j) a += kS1[i][j] * fas[j];
      ws[1] += kS1[i][8] * sin(a) + kS1[i][9] * cos(a);
    }
    for (i = 24; i >= 0; --i) {
      a = 0.0;
      for (j = 0; j < 8; ++j) a += kS2[i][j] * fas[j];
      ws[2] += kS2[i][8] * sin(a) + kS2[i][9] * cos(a);
    }
    for (i = 3; i >= 0; --i) {
      a = 0.0;
      for (j = 0; j < 8; ++j) a += kS3[i][j] * fas[j];
      ws[3] += kS3[i][8] * sin(a) + kS3[i][9] * cos(a);
    }
    for (i = 0; i >= 0; --i) {
      a = 0.0;
      for (j = 0; j < 8; ++j) a += kS4[i][j] * fas[j];
      ws[4] += kS4[i][8] * sin(a) + kS4[i][9] * cos(a);
    }
    s = (ws[0] + (ws[1] + (ws[2] + (ws[3] + (ws[4] + ws[5]
      * jcn) * jcn) * jcn) * jcn) * jcn) * kAs2R - x * y / 2.0;
  } catch (...) {
    throw;
  }

  return s;
}

// -------------------------------------
// 以下、 private functions
// -------------------------------------

}  // namespace calc_greenwich

