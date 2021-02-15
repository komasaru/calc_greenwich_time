#ifndef CALC_GREENWICH_CIP_CIO_HPP_
#define CALC_GREENWICH_CIP_CIO_HPP_

#include "fandamental_argument.hpp"

#include <iostream>

namespace calc_greenwich {

class CipCio {
  double jcn;  // JCN(T; ユリウス世紀数 for UTC)

public:
  CipCio(double jcn) : jcn(jcn) {}                 // コンストラクタ
  bool bpn2xy(double(&)[3][3], double&, double&);  // BPN -> X, Y (of CIP)
  double calc_s_06(double, double);                // CIO locator s 計算
private:
};

}  // namespace calc_greenwich

#endif

