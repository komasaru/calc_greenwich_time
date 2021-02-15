#ifndef CALC_GREENWICH_ERA_EORS_HPP_
#define CALC_GREENWICH_ERA_EORS_HPP_

#include <cmath>
#include <iostream>

namespace calc_greenwich {

class EraEors{
  double jd;                  // JD(UT1)
  double jd_2k;               // JD2000(UT1)
  double norm_angle(double);  // 角度の正規化

public:
  EraEors(double);                          // コンストラクタ
  double calc_era();                        // 計算: Earth rotation angle
  double calc_eo(double, double(&)[3][3]);  // 計算: Equation of the origins
  double calc_gast(double, double);         // 計算: Greenwich apparent sidereal time
  double calc_gmst(double, double);         // 計算: Greenwich mean sidereal time
  double calc_ee(double, double);           // 計算: Equation of equinoxes
};

}  // namespace calc_greenwich

#endif

