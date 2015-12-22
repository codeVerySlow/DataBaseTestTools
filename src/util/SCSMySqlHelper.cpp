#include "include/SCSMySqlHelper.h"

bool CSCSMySqlHelper::ConnMySql(const char *host,const char *port,const char *user,const char *pwd,const char *db,const char *charset,const char *msg)
{
	if(mysql_init(&mysql)==NULL)
	{
		msg="mysql init err";
		return false;
	}

	if(mysql_real_connect(&mysql,host,user,pwd,db,port,NULL,0)==NULL)
	{
		msg="connect to database error";
		return false;
	}

	if(mysql_set_character_set(&mysql,charset) != 0)
	{
		msg = "mysql_set_character_set Error";
		return false;
	}

	return true;
}

bool CSCSMySqlHelper::Select(const char *sql,std::vector<std::vector<std::string> > *result,char *msg)
{
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;

	if(!mysql_query(&mysql,sql))
	{
		msg = "select query error";
		return false;
	}

	if((m_res = mysql_store_result(&mysql))==NULL)
	{
		msg="store result error";
		return false;
	}

	MYSQL_FIELD *fd;
	int i;

	std::vector<std::string> columns;
	for(i=0;fd=mysql_fetch_field(m_res);i++)//获取列名
	{
		std::string column(fd->name);
		columns.push_back(column);
	}

	result->push_back(columns);

	
	MYSQL_ROW sql_row;
	int j=mysql_num_fields(m_res);

	while(sql_row=mysql_fetch_row(m_res))//获取具体的数据
	{
		std::vector<std::string> datarows;
		for(i=0;i<j;i++)
		{
			std::string filed(sql_row[i]);
			datarows.push_back(filed);
		}
		result->push_back(datarows);
	}

	return true;
}

void CSCSMySqlHelper::CloseMySql()
{
	mysql_close(&mysql);
}