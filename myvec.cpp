#include "myvec.h"
#include "mylib.h"

std::vector<std::string> split(std::string s, std::string delimiter)
{
    std::vector<std::string> res;
    char *cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    char* token;
    token = strtok(cstr,delimiter.c_str());
    while(token)
    {
        res.emplace_back(token);
        token=strtok(NULL,delimiter.c_str());
    }
    delete [] cstr;
    return res;
}
std::vector<int> arrstr2int(std::vector<std::string>& arr)
{
    std::vector<int> intNumbers;
    for (auto i=arr.begin(); i!=arr.end(); ++i)
    {
        int num = atoi(i->c_str());
        intNumbers.emplace_back(num);
    }
    return intNumbers;
}
std::vector<int> arrstr2int(std::vector<std::string>&& arr){return arrstr2int(arr);}
std::vector<int> operator+(const std::vector<int>& lhs,const  std::vector<int>& rhs)
{
	if(lhs.size()!=rhs.size())
	{
		print("vector size must be equal:",lhs,rhs);
		exit(-1);
	}
	std::vector<int> res(lhs);
	for(unsigned int i=0;static_cast<unsigned int>(rhs.size())-i>0;i++)
	{
		res[i]+=rhs[i];
	}
	return res;
}

std::string operator ""_s(const char *str, std::size_t len) {
    return std::string(str, len);
}