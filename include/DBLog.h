//**************************************************
//@File Name:  DBLogMerge.h
//@version  :  V1.0
//@Copyright: 汉云科技
//@Designer : 杨舟
//@Creater: : 杨舟
//@Begin Date: 2014.9.22
//@End Date  : 2014.9.23
//**************************************************

//@Description：
//本文件是根据以前版本 CSCSDBLog DBLogCS的合并。方便在日志类的使用
//该日志模块不支持在同一工程中使用两种日志模式
//文件中定义了初始化宏：
//仅支持多线程为 LOG_INIT_NORMAL LOG_INIT_NORMAL2 LOG_INIT_NORMAL3
//同时支持多进程与多线程的为CS模式 LOG_INIT_CS LOG_INIT_CS2 LOG_INIT_CS3
//在CS模式下采用了阻塞IO+Poll模式，理由有一下几点：
//1.log4cplus用阻塞IO实现，如若采用非阻塞IO需要修改源代码
//2.采用非阻塞IO需要实现缓冲区较为复杂，但在该日志库的使用情况是调用LOG_WARN等即为有数据可发送
//所以在Server端每次接收都会有数据。不会存在一直没有没有数据的情况

#ifndef DBLOGCS_H
#define DBLOGCS_H

#ifndef __SCSLOG__
#include <log4cplus/ndc.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/socketappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/configurator.h>
#include <log4cplus/logger.h>
#include <log4cplus/loglevel.h>
#include <log4cplus/helpers/socket.h>
#include <log4cplus/spi/loggingevent.h>

#include <iomanip>
#include <string>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include "DBLibrary.h"

#define SERVER_IP "0.0.0.0"

#define __LOG_FILE_NUM 10
#define __LOG_FILE_SIZE (32*1024*1024)


#define __SLL_DEBUG SLL_DEBUG
#define __SLL_INFO SLL_INFO
#define __SLL_WARN SLL_WARN
#define __SLL_ERROR SLL_ERROR

enum EMSCSLogLevel
{
	SLL_DEBUG,
	SLL_INFO,
	SLL_WARN,
	SLL_ERROR
};

//日志模式
enum EMSCSLogMode
{
	SLM_NORMAL,
	SLM_CS
};

enum EMAppType
{
	ROLLING_APP,
	SOCKET_APP
};

//共享内存的内容
typedef struct{
	EMSCSLogLevel emlevel;//当前日志等级
// 	pthread_mutex_t mutex;
// 	sem_t sem;
}STLoggerLevel;

class CSCSDBLog 
{

public:
	typedef std::vector<struct pollfd> PollFdList;
	typedef std::map<int, log4cplus::helpers::Socket*> SocketMap;

	/************************************************************************************
	函数名：InitLogNormal
	功能：	初始化普通模式的log4日志库
	参数：	strPath --文件路径， bUserSetLevel --运行修改日志级别 nLogFileSize -- 单文件日志大小
				nLogFileNum -- 最大保留多少日志文件， strFileName -- 文件名
	返回值：bool 成功 true 失败 false
	************************************************************************************/
	static bool InitLogNormal(const std::string& strPath, bool bUserSetLevel, int nLogFileSize = 0, \
											int nLogFileNum = 0, const std::string strFileName = "");

	/************************************************************************************
	函数名：InitLogCS
	功能：	初始化普通模式的log4日志库
	参数：	strPath --文件路径， bUserSetLevel --运行修改日志级别 nServerPort -- 端口号
				nLogFileSize --单文件日志大小 nLogFileNum -- 最大保留多少日志文件， strFileName -- 文件名
	返回值：bool 成功 true 失败 false
	************************************************************************************/
	static bool InitLogCS(const std::string strPath, bool bUserSetLevel, unsigned short nServerPort, \
									int nLogFileSize = 0, int nLogFileNum = 0, const std::string strFileName = "");

	/************************************************************************************
	函数名：DirectoryExist
	功能：	判断日志目录是否存在
	参数：	strDict --日志目录路径
	返回值：bool 成功 true 失败 false
	************************************************************************************/
	static bool DirectoryExist(const std::string& strDict);

	/************************************************************************************
	函数名：SetLogLevel
	功能：	设置日志等级
	参数：	emLevel --日志等级
	返回值：无
	************************************************************************************/
	static void SetLogLevel(EMSCSLogLevel emLevel);

	/************************************************************************************
	函数名：SetLogLevel
	功能：	设置输出日志等级
	参数：	logger --日志实例
	返回值：无
	************************************************************************************/
	static void SetSigAct(log4cplus::Logger &logger);

	/************************************************************************************
	函数名：SetLogNameEX
	功能：	设置单独打印日志文件
	参数：	strName --文件名
	返回值：无
	************************************************************************************/
    static void SetLogNameEX(const std::string &strName);

	/************************************************************************************
	函数名：GetLogger
	功能：	获得日志对象
	参数：	无
	返回值：log4cplus::Logger* 日志实例指针
	************************************************************************************/
	static log4cplus::Logger* GetLogger();

	/************************************************************************************
	函数名：KillServer
	功能：   在CS日志模式下杀死日志Server进程
	参数：   无
	返回值：无
	************************************************************************************/
	static void KillServer();
	
private:
	/************************************************************************************
	函数名：InitServer
	功能：  初始化日志Server进程
	参数：   strFile --文件路径， nLogFileSize --单文件大小 nLogFileNum --最大保留日志文件数量
	返回值：无
	************************************************************************************/
    static void InitServer(std::string &strFile, int nLogFileSize, int nLogFileNum);

	/************************************************************************************
	函数名：WriteFile
	功能：  Server向文件写数据
	参数：   logger --日志实例， clientSock --客户端socket
	返回值：bool true 成功 false 失败
	************************************************************************************/
    static bool WriteFile(log4cplus::Logger &logger, log4cplus::helpers::Socket &clientSock);

	/************************************************************************************
	函数名：ConvertLogPath
	功能：  转换日志路径名
	参数：   strName 日志名
	返回值：string 日志名
	************************************************************************************/
	static std::string ConvertLogPath(const std::string &strName);

	/************************************************************************************
	函数名：InitLogger
	功能：  初始化日志实例
	参数：   emType -- appender类型， strName -- appender名 strFileName 日志实例名 nLogFileSize -- 文件大小
				nLogFileNum -- 日志文件数量， pstLevel -- 日志级别
	返回值：string 日志名
	************************************************************************************/
	static log4cplus::Logger* InitLogger(EMAppType emType, const string &strName, \
													const std::string strFileName = "", const int nLogFileSize = 0, \
													const int nLogFileNum = 0, STLoggerLevel *pstLevel = NULL);

	/************************************************************************************
	函数名：BeforeFork
	功能：   在CS日志模式下fork命令下之前的操作
	参数：   无
	返回值：无
	************************************************************************************/
	static void BeforeFork();

	/************************************************************************************
	函数名：PartentsAfterFork
	功能：   在CS日志模式下fork命令下父进程之后的操作
	参数：   无
	返回值：无
	************************************************************************************/
	static void PartentsAfterFork();

	/************************************************************************************
	函数名：ChildAfterFork
	功能：   在CS日志模式下fork命令下子进程之后的操作
	参数：   无
	返回值：无
	************************************************************************************/
	static void ChildAfterFork();
private:
	static std::string ms_strPath;					//日志路径
	static STLoggerLevel *ms_pstLevel;			//日志等级
	static pid_t ms_nServPid;							//server进程ID 方便在程序结束时杀死server
	static pid_t ms_nClientPid;						//client进程ID
	static bool ms_bUserSetLevel;					//自定义等级
	static unsigned short ms_nServerPort;		//server端口
	static EMSCSLogMode ms_emLogMode;		//日志模式
	static log4cplus::Logger *ms_pClientLogger; //日志实例
	static log4cplus::SharedAppenderPtr ms_AppendPtr;
};

//参数说明：
//strPath - 保存日志的路径，提供一个目录名
//bUserSetLevel - bool类型，true表示在程序中可以动态设置输出日志级别
//							false表示不能设置输出级别

#define LOG_INIT_NORMAL(strPath, bUserSetLevel) 																							\
	CSCSDBLog::InitLogNormal(strPath, bUserSetLevel);

#define LOG_INIT_NORMAL2(strPath, bUserSetLevel, nLogFileSize, nLogFileNum)													\
	CSCSDBLog::InitLogNormal(strPath, bUserSetLevel, nLogFileSize, nLogFileNum);

#define LOG_INIT_NORMAL3(strPath, bUserSetLevel, nLogFileSize, nLogFileNum, strFileName)									\
	CSCSDBLog::InitLogNormal(strPath, bUserSetLevel, nLogFileSize, nLogFileNum, strFileName);


#define LOG_INIT_CS(strPath, bUserSetLevel, nServerPort) \
	CSCSDBLog::InitLogCS(strPath, bUserSetLevel, nServerPort);	

#define LOG_INIT_CS2(strPath, bUserSetLevel, nServerPort, nLogFileSize, nLogFileNum)										    \
	CSCSDBLog::InitLogCS(strPath, bUserSetLevel, nServerPort, nLogFileSize, nLogFileNum);

#define LOG_INIT_CS3(strPath, bUserSetLevel, nServerPort, nLogFileSize, nLogFileNum, strFileName)						\
	CSCSDBLog::InitLogCS(strPath, bUserSetLevel, nServerPort, nLogFileSize, nLogFileNum, strFileName);

#define LOG_DESTROY()																																\
        CSCSDBLog::KillServer();																															\
	
#define LOG_DEBUG(strMsg)																															\
	LOG4CPLUS_DEBUG(*CSCSDBLog::GetLogger(), strMsg)

#define LOG_INFO(strMsg)																																\
	LOG4CPLUS_INFO(*CSCSDBLog::GetLogger(), strMsg)

#define LOG_WARN(strMsg)																																\
	LOG4CPLUS_WARN(*CSCSDBLog::GetLogger(), strMsg)

#define LOG_ERROR(strMsg)																				                                            \
	LOG4CPLUS_ERROR(*CSCSDBLog::GetLogger(), strMsg)

#define SET_LOGLEVEL(emLevel)																														\
	CSCSDBLog::SetLogLevel(emLevel);																												\

    //设置线程输出标志
#define LOG_THREAD_TAG(strMsg) 																													\
    {																																							\
        log4cplus::NDC &ndc = log4cplus::getNDC();																							\
		ndc.push(strMsg);																																	\
    }

    //删除当前线程输出标志
#define LOG_DEL_THREAD_TAG()																													\
    {																																							\
        log4cplus::NDC &ndc = log4cplus::getNDC();																							\
        ndc.pop();																																			\
    }

    //在需要单独打印日志的构造函数里面调用
    //name 是希望显示日志的名字头部
    //日志会保存在总日志的同一个目录下
    //编译时DEBUG模式，会输出debug级日志，否则是warn级别的日志
#define LOG_NAME_EX(strName)																														\
    {																																							\
	CSCSDBLog::SetLogNameEX(strName);																											\
    }

    //同一个模块内，与之前LOG_NAME_EX设置的NAME同名,这样才会把日志写到同一个文件
    //注意，调用 SET_LOGLEVEL 不会对 LOG_xxx_EX 的输出等级有影响
#define LOG_DEBUG_EX(strName, strMsg)																												\
    {																																							\
	log4cplus::Logger logger = log4cplus::Logger::getInstance(strName);															\
	LOG4CPLUS_DEBUG(logger, strMsg);																											\
    }
#define LOG_INFO_EX(strName, strMsg)																													\
    {																																							\
	log4cplus::Logger logger = log4cplus::Logger::getInstance(strName);															\
	LOG4CPLUS_INFO(logger, strMsg);																											\
    }

#define LOG_WARN_EX(strName, strMsg)																												\
    {																																							\
	log4cplus::Logger logger = log4cplus::Logger::getInstance(strName);															\
	LOG4CPLUS_WARN(logger, strMsg);																											\
    }

#define LOG_ERROR_EX(strName, strMsg)																												\
    {																																							\
	log4cplus::Logger logger = log4cplus::Logger::getInstance(strName);															\
	LOG4CPLUS_ERROR(logger, strMsg);																											\
    }
	
void OutLog(EMSCSLogLevel emLevel, const char* pcFormat, ...);

//支持模块化日志输出的OutLog
//参数	strName	是模块的名字
void OutLog(const char *pcName, EMSCSLogLevel emLevel, const char* pcFormat, ...);

//以下宏用于计时

#ifdef DEBUG
#define TIME_DECLARE()																																\
	struct timeval stStartTime;																															\
	struct timeval stEndTime;																															\
	long lTimeUse;

#define TIME_START()																																	\
	gettimeofday(&stStartTime, NULL);

#define TIME_END(cArrMsg)																															\
	gettimeofday(&stEndTime, NULL);																												\
	lTimeUse = 1000000 * (stEndTime.tv_sec - stStartTime.tv_sec) + stEndTime.tv_usec - stStartTime.tv_usec;					\
	OutLog(SLL_DEBUG, "%s used (%.5f) sec", cArrMsg, lTimeUse / 1000000.0);

#else
#define TIME_DECLARE() ;
#define TIME_START() ;
#define TIME_END(cArrMsg) ;
#endif

//跟踪函数调试，输出文件名、函数名
#ifdef DEBUG
#define SCS_TRACE_ENTER()																														\
	OutLog(SLL_DEBUG, "enter %s-[%s]", __FILE__, __FUNCTION__);

#define SCS_TRACE_LEAVE()																															\
	OutLog(SLL_DEBUG, "leave %s-[%s]", __FILE__, __FUNCTION__);

#else
#define SCS_TRACE_ENTER() ;
#define SCS_TRACE_LEAVE() ;
#endif

#else



#include <scslog/scslogger.h>
#include <scslog/scsloggingmacros.h>
#include <scslog/scsappendfile.h>
#include <scslog/scslevel.h>
#include <iomanip>
#include <string>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#define __LOG_FILE_NUM 10
#define __LOG_FILE_SIZE (32*1024*1024)
//using namespace scs;
#define __SLL_DEBUG SLL_DEBUG
#define __SLL_INFO SLL_INFO
#define __SLL_WARN SLL_WARN
#define __SLL_ERROR SLL_ERROR
enum EMSCSLogLevel
{
    SLL_DEBUG,
    SLL_INFO,
    SLL_WARN,
    SLL_ERROR
};

class CSCSDBLog
{
public:
    static int InitLog(const std::string strPath, bool bUserSetLevel,
        bool bFileLock = true,
        int nLogFileSize = 0, int nLogFileNum = 0,
        const std::string strFileName = "");
    static void SetLogLevel(EMSCSLogLevel emLevel);
    static scs::CSCSLogger* GetLogger();
    static void SetLogNameEX(const std::string &strName);
    static scs::CSCSLogger* InitLogger(const std::string &strName, \
        const std::string strFileName = "", const int nLogFileSize = 0, \
        const int nLogFileNum = 0);
private:
    static std::string ConvertLogPath(const std::string &strName);
    static bool DirectoryExist(const std::string& strDict);
    static void ChildAfterFork();
    static std::string ms_strPath;
    static EMSCSLogLevel *ms_pemLevel;
    static bool ms_bUserSetLevel;
    static pthread_mutex_t ms_Mutex;
    static scs::CSCSLogger *ms_pLogger;
    static bool ms_bFileLock;
};

#define LOG_INIT(strPath, bUserSetLevel)\
    CSCSDBLog::InitLog(strPath, bUserSetLevel);

#define LOG_INIT_MULT_THREAD(strPath, bUserSetLevel)\
    CSCSDBLog::InitLog(strPath, bUserSetLevel, false);
//
// #define LOG_INIT2(strPath, bUserSetLevel, nLogFileSize, nLogFileNum)\
//     CSCSDBLog::InitLog(strPath, bUserSetLevel, nLogFileSize, nLogFileNum);
//
// #define LOG_INIT3(strPath, bUserSetLevel, nLogFileSize, nLogFileNum, strFileName)\
//     CSCSDBLog::InitLog(strPath, bUserSetLevel, nLogFileSize, nLogFileNum, strFileName);
// #define SET_LOGLEVEL(emLevel)\
//     CSCSDBLog::SetLogLevel(emLevel)
//
#define LOG_DEBUG(strMsg)   \
    SCSLOG_DEBUG(CSCSDBLog::GetLogger(), strMsg)

#define LOG_INFO(strMsg)    \
    SCSLOG_INFO(CSCSDBLog::GetLogger(), strMsg)

#define LOG_WARN(strMsg)    \
    SCSLOG_WARN(CSCSDBLog::GetLogger(), strMsg)

#define LOG_ERROR(strMsg)   \
    SCSLOG_ERROR(CSCSDBLog::GetLogger(), strMsg)

#define SET_LOGLEVEL(emLevel)\
    CSCSDBLog::SetLogLevel(emLevel);

//设置线程输出标志
#define LOG_THREAD_TAG(strMsg) \
{\
    CSCSDBLog::GetLogger()->SetThreadName(strMsg); \
}

#define LOG_DEL_THREAD_TAG()\
{\
    CSCSDBLog::GetLogger()->CancelThreadName(); \
}

//在需要单独打印日志的构造函数里面调用
//name 是希望显示日志的名字头部
//日志会保存在总日志的同一个目录下
//编译时DEBUG模式，会输出debug级日志，否则是warn级别的日志
#define LOG_NAME_EX(strName)\
{\
	CSCSDBLog::SetLogNameEX(strName); \
}

//同一个模块内，与之前LOG_NAME_EX设置的NAME同名,这样才会把日志写到同一个文件
//注意，调用 SET_LOGLEVEL 不会对 LOG_xxx_EX 的输出等级有影响
//在使用EX宏输出日志时要确保日志实例存在
#define LOG_THREAD_TAG_EX(strName, strMsg)\
{\
	scs::CSCSLogger *logger = scs::CSCSLogger::Instance(strName);\
	logger->SetThreadName(strMsg);\
}
#define LOG_DEL_THREAD_TAG_EX(strName)\
{\
	scs::CSCSLogger *logger = scs::CSCSLogger::Instance(strName); \
	logger->CancelThreadName(); \
}
#define LOG_DEBUG_EX(strName, strMsg)\
{\
    scs::CSCSLogger *logger = scs::CSCSLogger::Instance(strName); \
    SCSLOG_DEBUG(logger, strMsg); \
}

#define LOG_INFO_EX(strName, strMsg)\
{\
    scs::CSCSLogger *logger = scs::CSCSLogger::Instance(strName); \
    SCSLOG_INFO(logger, strMsg); \
}

#define LOG_WARN_EX(strName, strMsg)\
{\
    scs::CSCSLogger *logger = scs::CSCSLogger::Instance(strName); \
    SCSLOG_WARN(logger, strMsg); \
}

#define LOG_ERROR_EX(strName, strMsg)\
{\
    scs::CSCSLogger *logger = scs::CSCSLogger::Instance(strName); \
    SCSLOG_WARN(logger, strMsg); \
}
void OutLog(EMSCSLogLevel emLevel, const char* pcFormat, ...);

//支持模块化日志输出的OutLog
//参数	strName	是模块的名字
void OutLog(const char *pcName, EMSCSLogLevel emLevel, const char* pcFormat, ...);

#ifdef DEBUG
#define TIME_DECLARE()	\
struct timeval stStartTime;	\
struct timeval stEndTime; \
    long lTimeUse;

#define TIME_START()\
    gettimeofday(&stStartTime, NULL);

#define TIME_END(cArrMsg)	\
    gettimeofday(&stEndTime, NULL);	\
    lTimeUse = 1000000 * (stEndTime.tv_sec - stStartTime.tv_sec) + stEndTime.tv_usec - stStartTime.tv_usec;	\
    OutLog(SLL_DEBUG, "%s used (%.5f) sec", cArrMsg, lTimeUse / 1000000.0);

#else
#define TIME_DECLARE() ;
#define TIME_START() ;
#define TIME_END(cArrMsg) ;
#endif
//跟踪函数调试，输出文件名、函数名
#ifdef DEBUG
#define SCS_TRACE_ENTER()\
    OutLog(SLL_DEBUG, "enter %s-[%s]", __FILE__, __FUNCTION__);

#define SCS_TRACE_LEAVE()\
    OutLog(SLL_DEBUG, "leave %s-[%s]", __FILE__, __FUNCTION__);

#else
#define SCS_TRACE_ENTER() ;
#define SCS_TRACE_LEAVE() ;
#endif
#endif
#endif
