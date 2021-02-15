#ifndef CALC_GREENWICH_FANDAMENTAL_ARGUMENT_HPP_
#define CALC_GREENWICH_FANDAMENTAL_ARGUMENT_HPP_

#include <cmath>

namespace calc_greenwich {

double calc_l_iers2003(double);   // Mean anomaly of the Moon.(Ref: iauFal03(t))
double calc_p_iers2003(double);   // Mean anomaly of the Sun.(Ref: iauFalp03(t))
double calc_f_iers2003(double);   // Mean longitude of the Moon minus that of the ascending node.(Ref: iauFaf03(t))
double calc_d_iers2003(double);   // Mean elongation of the Moon from the Sun.(Ref: iauFad03(t))
double calc_om_iers2003(double);  // Mean longitude of the ascending node of the Moon.(Ref: iauFaom03(t))
double calc_ve_iers2003(double);  // Mean longitude of Venus.(Ref: iauFave03(t))
double calc_ea_iers2003(double);  // Mean longitude of Earth.(Ref: iauFae03(t))
double calc_pa_iers2003(double);  // General precession in longitude.(Ref: iauFapa03(t))
double fmod_p(double, double);    // 正剰余計算（std::fmod が非対応のため）

}  // namespace calc_greenwich

#endif

