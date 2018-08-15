#ifndef _FFL_LOG_LIB_H_
#define _FFL_LOG_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif 

	typedef void* FFLog;
	extern DECLSPEC FFLog FFLogCreateInstance();
	extern DECLSPEC void  FFLogDestroyInstance(FFLog log);

	//
	//  对应FFL_logSender中的相关值
	//
	enum {
		FFLOG_ST_NONE = 0,
		//
		//  一个tcp连接，连接一个服务器  ip:port
		//
		FFLOG_ST_TCP_CONNECT = 1,
		//
		//  已经创建的文件
		//
		FFLOG_ST_EXIST_FILE = 2,
		//
		//  新创建一个文件
		//
		FFLOG_ST_NEW_FILE = 3,
	};
	//
	//  设置日志的生成目标
	//
	extern DECLSPEC void  FFLogSetUrl(int type, const char* url);

	//
	//  对应FFLv2中的相应值
	//
	enum {
		FFLOG_LEVEL_CRIT = 0,
		FFLOG_LEVEL_ERROR,
		FFLOG_LEVEL_WARNING,
		FFLOG_LEVEL_INFO,
		FFLOG_LEVEL_DEBUG,
		FFLOG_LEVEL_ALL
	};
	//
	//  设置日志级别
	//
	extern DECLSPEC void  FFLogSetLevel(int level);
	//
	//  打印日志
	//
	extern DECLSPEC void  FFLogPrint(int level, const char* format, ...);
	extern DECLSPEC void  FFLogPrintCri(const char* format, ...);
	extern DECLSPEC void  FFLogPrintErr(const char* format, ...);
	extern DECLSPEC void  FFLogPrintWar(const char* format, ...);
	extern DECLSPEC void  FFLogPrintInf(const char* format, ...);
	extern DECLSPEC void  FFLogPrintDbg(const char* format, ...);
	#define FFLOG_CRIT        FFLogPrintCri
	#define FFLOG_ERROR       FFLogPrintErr
	#define FFLOG_WARNING     FFLogPrintWar
	#define FFLOG_INFO        FFLogPrintInf
	#define FFLOG_DEBUG       FFLogPrintDbg

#ifdef __cplusplus
}
#endif 

#endif 