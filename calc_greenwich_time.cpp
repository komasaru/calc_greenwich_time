/***********************************************************
  グリニジ視恒星時 GAST(= Greenwich Apparent Sidereal Time)等の計算
  : IAU2006 による計算

  * IAU SOFA(International Astronomical Union, Standards of Fundamental Astronomy)
    の提供する C ソースコード "gst06.c" 等で実装されているアルゴリズムを使用する。
  * 参考サイト
    - [SOFA Library Issue 2016-05-03 for ANSI C: Complete List](http://www.iausofa.org/2016_0503_C/CompleteList.html)
    - [USNO Circular 179](http://aa.usno.navy.mil/publications/docs/Circular_179.php)
    - [IERS Conventions Center](http://62.161.69.131/iers/conv2003/conv2003_c5.html)

    DATE          AUTHOR          VERSION
    2020.11.24    mk-mode.com     1.00 新規作成

  Copyright(C) 2020 mk-mode.com All Rights Reserved.

  引数 : JST（日本標準時）
         書式: JST: 最大23桁の数字
               （先頭から、西暦年(4), 月(2), 日(2), 時(2), 分(2), 秒(2),
                           1秒未満(9)（小数点以下9桁（ナノ秒）まで））
               無指定なら現在(システム日時)を JST とみなす。
***********************************************************/
#include "common.hpp"
#include "greenwich.hpp"

#include <cstdlib>   // for EXIT_XXXX
#include <ctime>
#include <iomanip>   // for setprecision
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  namespace ns = calc_greenwich;
  std::string tm_str;    // time string
  unsigned int s_tm;     // size of time string
  int s_nsec;            // size of nsec string
  struct timespec utc;   // UTC
  struct timespec jst;   // JST
  struct tm t = {};      // for work
  double gast;           // GAST(rad.)
  double gmst;           // GMST(rad.)
  double ee;             // EE(rad.)
  double gast_deg;       // GAST(deg.)
  double gmst_deg;       // GMST(deg.)
  double ee_deg;         // EE(deg.)
  std::string gast_hms;  // GAST(hms)
  std::string gmst_hms;  // GMST(hms)
  std::string ee_hms;    // EE(hms)

  try {
    // 日付取得
    if (argc >1) {
      // コマンドライン引数より取得
      tm_str = argv[1];
      s_tm = tm_str.size();
      if (s_tm > 23) {
        std::cout << "[ERROR] Over 23-digits!" << std::endl;
        return EXIT_FAILURE;
      }
      s_nsec = s_tm - 14;
      std::istringstream is(tm_str);
      is >> std::get_time(&t, "%Y%m%d%H%M%S");
      jst.tv_sec  = mktime(&t);
      jst.tv_nsec = 0;
      if (s_tm > 14) {
        jst.tv_nsec = std::stod(
            tm_str.substr(14, s_nsec) + std::string(9 - s_nsec, '0'));
      }
    } else {
      // 現在日時の取得
      if (std::timespec_get(&jst, TIME_UTC) != 1) {
        std::cout << "[ERROR] Could not get now time!" << std::endl;
        return EXIT_FAILURE;
      }
    }

    // JST -> UTC
    utc = ns::jst2utc(jst);

    // Calculation & Display
    ns::Greenwich o_gr(utc);
    gast = o_gr.gast;
    gmst = o_gr.gmst;
    ee   = o_gr.ee;
    gast_deg = ns::rad2deg(gast);
    gmst_deg = ns::rad2deg(gmst);
    ee_deg   = ns::rad2deg(ee);
    gast_hms = ns::deg2hms(gast_deg);
    gmst_hms = ns::deg2hms(gmst_deg);
    ee_hms   = ns::deg2hms(ee_deg);
    std::cout << "      JST: " << ns::gen_time_str(jst)      << std::endl;
    std::cout << "      UTC: " << ns::gen_time_str(utc)      << std::endl;
    std::cout << "       TT: " << ns::gen_time_str(o_gr.tt)  << std::endl;
    std::cout << "      UT1: " << ns::gen_time_str(o_gr.ut1) << std::endl;
    std::cout << "      TDB: " << ns::gen_time_str(o_gr.tdb) << std::endl;
    std::cout << "     ERA = " << o_gr.era << " rad." << std::endl;
    std::cout << "      EO = " << o_gr.eo  << " rad." << std::endl;
    std::cout << "    GAST = " << gast     << " rad." << std::endl
              << "         = " << gast_deg << " deg." << std::endl
              << "         = " << gast_hms            << std::endl;
    std::cout << "    GMST = " << gmst     << " rad." << std::endl
              << "         = " << gmst_deg << " deg." << std::endl
              << "         = " << gmst_hms            << std::endl;
    std::cout << "      EE = " << ee       << " rad." << std::endl
              << "         = " << ee_deg   << " deg." << std::endl
              << "         = " << ee_hms              << std::endl;
  } catch (...) {
      std::cerr << "EXCEPTION!" << std::endl;
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

