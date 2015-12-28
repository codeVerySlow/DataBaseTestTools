#include <string>
#include <vector>
#include "scsdbclient.h"
#include "scsdberror.h"

#include "SCSSCSHelper.h"

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
	nColNum = scsdb_colum_num(m_scsdb);
	return true;
}

bool CSCSSCSHelper::GetNextRow( std::vector<std::string> *dataRow )
{
	dataRow->clear();
	//���������>0��˵������ִ�е�SCSQL����н��������
	//��show��select������
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

		//ѭ��������ӡ���н��
		if (scsdb_read_row(scsdb) != __READ_ROW_END)
		{			
			for (int i = 0; i < nColNum; i++)
			{
				dataRow->push_back(scsdb_read_field(scsdb, i));
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
			dataRow->push_back(scsdb_affected_rows(scsdb));
			m_isReadAffect = true;
			return true;
		}
	}

	return false;
}

void CSCSSCSHelper::CloseSCS()
{
	//�ͷŽ����
	scsdb_release(scsdb);
	//�ر�����
	scsdb_close(scsdb);
}
