/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  FFLv2Log.cpp
*  Created by zhufeifei(34008081@qq.com) on 2018/08/31
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  规范日志系统接口
*/
#include <FFL.h>
#include "logsender/LogSender.hpp"

#define FFLOG_API_IMPLEMENT
#include "../FFLv2Log.h"

class LogInstance {
public:
	LogInstance() {
		mRefCount = 0;
	}
	void* startup() {
		FFL_hookLogSystem(mLogSender);
		mLogSender.startup();
		mRefCount++;
		return 0;
	}

	void shutdown(void* ) {
		if (--mRefCount == 0) {
			mLogSender.shutdown();
			FFL_unhookLogSystem();
		}
	}

	int mRefCount;
	FFL::LogSender mLogSender;
};
LogInstance gInstance;

//
//   开始安装日志系统，返回0表示成功
//
extern "C"	DECLSPEC  int FFLogSetup() {
	gInstance.startup();
	return 0;
}
//
//   结束日志系统
//
extern "C"	DECLSPEC  void FFLogTerminate() {
	gInstance.shutdown(0);
}
extern "C" DECLSPEC void  FFLogSetUrl(int type, const char* url) {
	gInstance.mLogSender.setTargetUrl((FFL::LogSenderType)type, url);
}
extern "C" DECLSPEC void  FFLogSetLevel(int level) {
	if (level >= FFL_LOG_LEVEL_CRIT && level <= FFL_LOG_LEVEL_ALL) {
		FFL_LogSetLevel((FFL_LogLevel)level);
	}
}
//
//  配置日志系统
//
extern "C"	DECLSPEC  void FFLogConfig(FFLogProperty* property) {
	if (property != NULL) {
		FFLogSetLevel((int)(property->level));
		FFLogSetUrl((int)(property->targetType), property->targetUrl);
	}
}
extern "C" DECLSPEC  void  FFLogPrint( int level, const char* format, ...) {
	if (level >= 0 && level < FFL_LogGetLevel()) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(level,format, args);
		va_end(args);		
	}
}
extern "C" DECLSPEC void  FFLogPrintCri(const char* format, ...) {
	  va_list args;
	  va_start(args, format);
	  FFL_LogPrintV(FFLOG_LEVEL_CRIT, format, args);
	  va_end(args);	
}

extern "C" DECLSPEC void  FFLogPrintErr(const char* format, ...) {
	if (FFL_LogGetLevel() > FFL_LOG_LEVEL_ERROR) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_ERROR, format, args);
		va_end(args);
	}
}

extern "C" DECLSPEC void  FFLogPrintWar(const char* format, ...) {
	if (FFL_LogGetLevel() > FFL_LOG_LEVEL_WARNING) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_WARNING, format, args);
		va_end(args);
	}
}

extern "C" DECLSPEC void  FFLogPrintInf(const char* format, ...) {
	if (FFL_LogGetLevel() > FFL_LOG_LEVEL_INFO) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_INFO, format, args);
		va_end(args);
	}
}


extern "C" DECLSPEC void  FFLogPrintDbg(const char* format, ...) {
	if (FFL_LogGetLevel() > FFL_LOG_LEVEL_DEBUG) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_DEBUG, format, args);
		va_end(args);
	}
}

