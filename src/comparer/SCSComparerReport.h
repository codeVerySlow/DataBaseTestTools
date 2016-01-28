#ifndef _COMPARER_SCSCOMPARERREPORT_H_
#define _COMPARER_SCSCOMPARERREPORT_H_

#include <map>
#include <boost/shared_ptr.hpp>
#include "SCSReport.h"

class CSCSPreparedSQLSet;


enum EMDisMatchType
{
    DISMATCHTYPE_COLUM,
    DISMATCHTYPE_ROW,
    DISMATCHTYPE_ROWCOUNT,
    DISMATCHTYPE_SQLERR
};

struct STTestCaseReport
{
    int nCaseID;
    std::string strModel;
    std::string strDesCaseSql;
    std::string strSrcCaseSql;
    std::vector<std::string> desColumn;
    std::vector<std::string> srcColumn;
    std::vector<std::string> desRow;
    std::vector<std::string> srcRow;
    EMDisMatchType m_emDisMatchType;
    std::string strErrMsg;
};


class CSCSComparerReport : public CSCSReport
{
public:
    mutable std::map<std::string,int> m_success;
    mutable std::map<std::string,int> m_fail;
    std::vector<STTestCaseReport> m_vecFailTestCase;

    //功能：添加对比失败用例报告
    //返回值：void
    //参数：report失败用例报告 set测试用例
    void AddTestCaseFailReport(boost::shared_ptr<STTestCaseReport> report, const CSCSPreparedSQLSet &set);
    //功能：添加执行失败用例报告
    //返回值：void
    //参数：set 测试用例 msg 错误信息
    void AddTestCaseExecuteErrReport(const CSCSPreparedSQLSet &set,const std::string &msg);
    //功能：测试用例成功个数计数 每调用一次成功个数加1
    //返回值：void
    //参数：model 用例模块
    void CountSuccess(const std::string &model);
    //功能：测试用例失败个数计数 每调用一次失败个数加1
    //返回值：void
    //参数：model 用例模块
    void CountFail(const std::string &model);
    //功能：获取用例成功个数
    //返回值：成功个数
    //参数：model 用例模块
    int GetSuccess(const std::string &module) const;
    //功能：获取用例失败个数
    //返回值：失败个数
    //参数：model 用例模块
    int GetFail(const std::string &module) const;
    //功能：获取用例成功总个数
    //返回值：成功总个数
    //参数：void
    int GetSuccessTotal() const ;
    //功能：获取用例失败总个数
    //返回值：失败总个数
    //参数：void
    int GetFailTotal() const ;
};


#endif
