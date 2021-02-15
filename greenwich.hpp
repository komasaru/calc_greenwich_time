#ifndef CALC_GREENWICH_GREENWICH_HPP_
#define CALC_GREENWICH_GREENWICH_HPP_

#include "bpn.hpp"
#include "cip_cio.hpp"
#include "era_eors.hpp"
#include "time.hpp"

#include <ctime>

namespace calc_greenwich {

class Greenwich {
  std::vector<std::vector<std::string>> l_ls;    // List of Leap Second
  std::vector<std::vector<std::string>> l_dut;   // List of DUT1
  std::vector<std::vector<double>>      dat_ls;  // data of lunisolar parameters
  std::vector<std::vector<double>>      dat_pl;  // data of planetary parameters
  double jd;               // JD(ユリウス日 for UTC)
  double jcn;              // JCN(T; ユリウス世紀数 for UTC)
  double jd_ut1;           // JD(ユリウス日 for UT1)
  double jd_2k_ut1;        // JD(ユリウス日 from 2000 for UT1)
  double r_mtx[3][3];      // 回転行列（バイアス＆歳差＆章動）
  double x;                // x of CIP
  double y;                // y of CIP
  double s;                // CIO locator

public:
  Greenwich(
      struct timespec,
      std::vector<std::vector<std::string>>&,
      std::vector<std::vector<std::string>>&,
      std::vector<std::vector<double>>&,
      std::vector<std::vector<double>>&);  // コンストラクタ
  struct timespec utc;         // UTC
  struct timespec ut1;         // UT1
  struct timespec tt;          // TT
  struct timespec tdb;         // TDB
  double era;                  // Earth rotation angle
  double eo;                   // Equation of the origins, given the classical NPB
                               // matrix and the quantity s.
  double gast;                 // Greenwich apparent sidereal time
  double gmst;                 // Greenwich mean sidereal time, IAU 2006
  double ee;                   // Equation of Equinoxes

private:
  void init();                 // 初期処理
};

}  // namespace calc_greenwich

#endif

