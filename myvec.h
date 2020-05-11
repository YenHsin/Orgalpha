#ifndef MYVEC_H_INCLUDED
#define MYVEC_H_INCLUDED


#include<string>
#include<cstring>
#include<vector>


std::vector<std::string> split(std::string s, std::string delimiter);
std::vector<int> arrstr2int(std::vector<std::string>& arr);
std::vector<int> arrstr2int(std::vector<std::string>&& arr);
std::vector<int> operator+ (const std::vector<int>& lhs,const std::vector<int>& rhs);
std::string operator ""_s(const char *str, std::size_t len);









#endif
