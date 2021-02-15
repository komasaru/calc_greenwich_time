#ifndef CALC_GREENWICH_FILE_HPP_
#define CALC_GREENWICH_FILE_HPP_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace calc_greenwich {

class File {

public:
  bool get_leap_sec_list(std::vector<std::vector<std::string>>&);  // 取得: うるう秒一覧
  bool get_dut1_list(std::vector<std::vector<std::string>>&);      // 取得: DUT1 一覧
  bool get_param_ls(std::vector<std::vector<double>>&);            // 取得: lunisolar parameters
  bool get_param_pl(std::vector<std::vector<double>>&);            // 取得: planetary parameters
};

}  // namespace calc_greenwich

#endif

