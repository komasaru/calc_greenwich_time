#ifndef CALC_GREENWICH_POSITION_HPP_
#define CALC_GREENWICH_POSITION_HPP_

namespace calc_greenwich {

// 直交座標・極座標兼用
struct Position {
  double x;  // x, lambda, lambda, alpha
  double y;  // y, phi,    beta,   delta
  double z;  // z, radius
};

}  // namespace calc_greenwich

#endif

