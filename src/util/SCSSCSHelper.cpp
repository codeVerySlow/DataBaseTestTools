#include <string>
#include <vector>
#include "scsdbclient.h"
#include "scsdberror.h"

#include "SCSSCSHelper.h"

bool CSCSSCSHelper::ConnSCS( const char *host,const int port,const char *user,const char *pwd,const char *db,const char *charset,std::string &msg )
{
	//连接SCSDB
	if(NULL == (m_scsdb = scsdb_open(host,user,pwd,db)))
	{
		msg="connect scsdb fail!";
		return false;
	}
	return true;
}

bool CSCSSCSHelper::InitSelect( const char *sql,std::string &msg )
{
	//执行SCSQL
	if(0 != scsdb_execute(m_scsdb,sql, strlen(sql)))
	{
		//执行失败打印错误信息
		msg="execute SCSQL fail!"; 			
		msg+=scsdb_error_code(m_scsdb);
		msg+=scsdb_error_string(m_scsdb);

		return false;
	}
	nColNum = scsdb_colum_num(m_scsdb);
	return true;
}

bool CSCSSCSHelper::GetNextRow( std::vector<std::string> *dataRow )
{
	dataRow->clear();
	//结果集列数>0，说明本次执行的SCSQL语句有结果集返回
	//如show、select等命令
	if (nColNum > 0)
	{
		if(!m_isReadColunm)
		{
			for (int i = 0; i < nColNum; i++)
			{
				dataRow->push_back(scsdb_column_name(m_scsdb, i));
			}
			m_isReadColunm=true;
			return true;
		}

		//循环遍历打印各行结果
		if (scsdb_read_row(scsdb) != __READ_ROW_END)
		{			
			for (int i = 0; i < nColNum; i++)
			{
				dataRow->push_back(scsdb_read_field(scsdb, i));
			}
			return true;
		}
	}
	//没有结果集返回，如insert、update、delete等
	//此时，返回数据库中受影响的行数，
	//即成功插入、更新、删除了多少行
	else
	{
		if(!m_isReadAffect)
		{
			dataRow->push_back(scsdb_affected_rows(scsdb));
			m_isReadAffect = true;
			return true;
		}
	}

	return false;
}

void CSCSSCSHelper::CloseSCS()
{
	//释放结果集
	scsdb_release(scsdb);
	//关闭连接
	scsdb_close(scsdb);
}
