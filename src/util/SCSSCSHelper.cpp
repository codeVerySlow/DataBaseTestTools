#include <string>
#include <vector>
#include <string.h>
#include "scsdbclient.h"
#include "scsdberror.h"

#include "SCSSCSHelper.h"
#include "SCSUtilTools.h"

bool CSCSSCSHelper::ConnSCS( const char *host,const int port,const char *user,const char *pwd,const char *db,const char *charset,std::string &msg )
{
	//����SCSDB
	if(NULL == (m_scsdb = scsdb_open(host,user,pwd,db)))
	{
		msg="connect scsdb fail!";
		return false;
	}
	return true;
}

bool CSCSSCSHelper::InitSelect( const char *sql,std::string &msg )
{
	//ִ��SCSQL
	if(0 != scsdb_execute(m_scsdb,sql, strlen(sql)))
	{
		//ִ��ʧ�ܴ�ӡ������Ϣ
		msg="execute SCSQL fail!"; 			
		msg+=scsdb_error_code(m_scsdb);
		msg+=scsdb_error_string(m_scsdb);

		return false;
	}
	m_nColNum = scsdb_colum_num(m_scsdb);
	return true;
}

bool CSCSSCSHelper::GetNextRow( std::vector<std::string> *dataRow )
{
	dataRow->clear();
	//���������>0��˵������ִ�е�SCSQL����н��������
	//��show��select������
	if (m_nColNum > 0)
	{
		if(!m_isReadColunm)
		{
			for (int i = 0; i < m_nColNum; i++)
			{
				dataRow->push_back(scsdb_column_name(m_scsdb, i));
			}
			m_isReadColunm=true;
			return true;
		}

		//ѭ��������ӡ���н��
		if (scsdb_read_row(m_scsdb) != __READ_ROW_END)
		{			
			for (int i = 0; i < m_nColNum; i++)
			{
				const char *row=scsdb_read_field(m_scsdb, i);
				dataRow->push_back(row==NULL?"NULL":row);
			}
			return true;
		}
	}
	//û�н�������أ���insert��update��delete��
	//��ʱ���������ݿ�����Ӱ���������
	//���ɹ����롢���¡�ɾ���˶�����
	else
	{
		if(!m_isReadAffect)
		{
			dataRow->push_back(SCSUtilTools::NumberToString<long long>(scsdb_affected_rows(m_scsdb)));
			m_isReadAffect = true;
			return true;
		}
	}
	//�ͷŽ����
	scsdb_release(m_scsdb);
	return false;
}

void CSCSSCSHelper::CloseSCS()
{

	//�ر�����
	scsdb_close(m_scsdb);
}

bool CSCSSCSHelper::IsConnect() {
	return m_scsdb!=NULL;
}
