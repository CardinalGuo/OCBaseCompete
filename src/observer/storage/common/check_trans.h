/*


 */


#ifndef __OBSERVER_SQL_STORAGE_COMMOM_CHECKTRANS_H__
#define __OBSERVER_SQL_STORAGE_COMMOM_CHECKTRANS_H__ 1

#pragma once

#include <string>
#include <vector>
#include <regex>
#include "common/log/log.h"
namespace check_trans {
    
static std::vector<std::string> split(const std::string& str, const std::string& delim) {  
    std::vector<std::string> res;  
    if("" == str) return res;  
    //先将要切割的字符串从string类型转换为char*类型  
    char * strs = new char[str.length() + 1] ; //不要忘了  
    strcpy(strs, str.c_str());   
 
    char * d = new char[delim.length() + 1];  
    strcpy(d, delim.c_str());  
 
    char *p = strtok(strs, d);  
    while(p) {  
        std::string s = p; //分割得到的字符串转换为string类型  
        res.push_back(s); //存入结果数组  
        p = strtok(NULL, d);  
    }  
 
    return res;  
};

static bool check_dateValue_valid(int year,int month ,int day){
  bool is_valid = true;
  switch (month)
  {
  case 2:
    if (year % 4 == 0)
      {
        is_valid &= (day <= 29);
      }else{
        is_valid &= (day <= 28);
      }
    break;
  case 4:
  case 6:
  case 9:
  case 11:
    is_valid &= (day <= 30);
    break;
  default:
    break;
  }
  return is_valid;
};

static bool check_dateString_valid(std::string date){
    std::smatch match;
    std::regex rule_date("([0-9]{4})-([0]?[1-9]|[1][0-2])-([0]?[1-9]|[1|2][0-9]|[3][0|1])");
    bool flag = regex_match(date,match,rule_date);
    return flag;     
};

static std::vector<int> split_date_toNum(const char* date_str){
    std::string date = date_str;
    std::vector<std::string> ymd = split(date,"-");
    int year = std::stoi(ymd[0]), month = std::stoi(ymd[1]), day = std::stoi(ymd[2]);
    std::vector<int> yms_num;
    // stoi字节据
    yms_num.push_back(year);
    yms_num.push_back(month);
    yms_num.push_back(day);
    return yms_num;
};

static int compare_date(const char *left_value ,const char *right_value){
    std::vector<int> ymd_left = split_date_toNum(left_value), ymd_right = split_date_toNum(right_value);
    int ysub = ymd_left[0] - ymd_right[0];
    int msub = ymd_left[1] - ymd_right[1];
    int dsub = ymd_left[2] - ymd_right[2];
    return ((ysub == 0 ) ? ((msub == 0 ) ? dsub : msub) : ysub);
};

static bool check_date(const char* date_str){
    std::string date = date_str;
    if(!check_dateString_valid(date)) return false;
    std::vector<int> ymd_num = split_date_toNum(date_str);
    if(!check_dateValue_valid(ymd_num[0],ymd_num[1],ymd_num[2])) return false;
    return true;
};

static int date_to_num(const void *data){
  const char *date_str = (char *)data;
  std::vector<int> ymd_num = split_date_toNum(date_str);
  return ymd_num[0] * 10000 + ymd_num[1]*100 + ymd_num[2];
};
}



#endif 