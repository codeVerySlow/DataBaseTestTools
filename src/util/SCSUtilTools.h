#include <string>
#include <vector>
#include <sstream>

namespace SCSUtilTools
{

    template<typename T>
    std::string NumberToString(T Number)
    {
        std::ostringstream ss;
        ss << Number;
        return ss.str();
    }

    template<typename T>
    T StringToNumber(const std::string &Text)
    {
        std::istringstream ss(Text);
        T result;
        return ss >> result ? result : 0;
    }
    //将string以delim为分割符进行分割
    extern std::vector<std::string> &split(const std::string &s, const std::string &delim,
                                           std::vector<std::string> &elems);
    //将string 分割
    extern std::vector<std::string> split(const std::string &s, const std::string &delim);
    //将vector 以delim为分割符进行组装成一个string
    extern std::string join(const std::vector<std::string> &vec, const std::string &delim);
    //以列名获取列索引
    extern int GetColumnIndex(const std::string &column, const std::vector<std::string> &vecTestCase);
    //获取进程id
    extern int getProcIdByName(std::string procName);
    //时间转换string
    extern std::string timeToString(const time_t &time);
    //时间间隔转换string
    extern std::string spanTimeToString(const time_t &end, const time_t &begin);
}
