#include "greenwich.hpp"

namespace calc_greenwich {

// 定数
static constexpr double kJ2K = 2451545.0;  // Reference epoch (J2000.0), Julian Date
static constexpr double kJc  = 36525.0;    // Days per Julian century

/*
 * @brief       コンストラクタ
 *
 * @param[in]   UTC (struct timespec)
 * @param[ref]  うるう秒一覧 (vector<vector<string>>)
 * @param[ref]  DUT1 一覧 (vector<vector<string>>)
 * @param[ref]  lunisolar parameter 一覧 (vector<vector<double>>)
 * @param[ref]  planetary parameter 一覧 (vector<vector<double>>)
 */
Greenwich::Greenwich(
    struct timespec utc,
    std::vector<std::vector<std::string>>& l_ls,
    std::vector<std::vector<std::string>>& l_dut,
    std::vector<std::vector<double>>& dat_ls,
    std::vector<std::vector<double>>& dat_pl) {
  try {
    this->utc    = utc;
    this->l_ls   = l_ls;
    this->l_dut  = l_dut;
    this->dat_ls = dat_ls;
    this->dat_pl = dat_pl;
    init();         // その他の初期処理
  } catch (...) {
    throw;
  }
}

// -------------------------------------
// 以下、 private functions
// -------------------------------------

/*
 * @brief   初期処理
 *
 * @param   <none>
 * @return  <none>
 */
void Greenwich::init() {
  try {
    Time o_tm(utc, l_ls, l_dut);      // Object of UTC
    ut1 = o_tm.calc_ut1();            // UT1（世界時１）
    tt  = o_tm.calc_tt();             // TT（地球時）
    tdb = o_tm.calc_tdb();            // TDB（太陽系力学時）
    jd     = o_tm.calc_jd();          // JD（ユリウス日）
    jcn    = o_tm.calc_t();           // JCN（T; ユリウス世紀数）
    Time o_tm_ut1(ut1, l_ls, l_dut);  // Object of UT1
    jd_ut1 = o_tm_ut1.calc_jd();      // JD（ユリウス日 for UT1）
    jd_2k_ut1 = jd_ut1 - kJ2K;        // JD2000（ユリウス日 from 2000 for UT1）
    Time o_tm_tdb(tdb, l_ls, l_dut);  // Object of TDB
    Bpn o_bpn(o_tm_tdb.calc_t(), dat_ls, dat_pl);  // Object of BPN
    if (!o_bpn.gen_r_bias_prec_nut(r_mtx)) throw;  // 回転行列
    CipCio o_cc(jcn);                 // Object of CipCio
    if (!o_cc.bpn2xy(r_mtx, x, y)) throw;  // x, y coordinates of the CIP
    s = o_cc.calc_s_06(x, y);         // CIO locator
    EraEors o_ee(jd_ut1);             // Object of EraEors
    era = o_ee.calc_era();            // Earth rotation angle
    eo  = o_ee.calc_eo(s, r_mtx);     // Equation of the origins
    gast = o_ee.calc_gast(era, eo);   // Greenwich apparent sidereal time
    gmst = o_ee.calc_gmst(era, jcn);  // Greenwich mean sidereal time
    ee   = o_ee.calc_ee(gast, gmst);  // Equation of equinoxes
  } catch (...) {
    throw;
  }
}

}  // namespace calc_greenwich

