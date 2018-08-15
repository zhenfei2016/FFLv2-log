#include <FFL.h>
#include <logsender/FFL_LogSender.hpp>
#include "logLib.h"

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

DECLSPEC  FFLog FFLogCreateInstance() {
	return gInstance.startup();
}
DECLSPEC  void  FFLogDestroyInstance(FFLog log) {
	gInstance.shutdown(log);
}
DECLSPEC  void  FFLogSetUrl(int type, const char* url) {
	gInstance.mLogSender.setTargetUrl((FFL::LogSenderType)type, url);
}
DECLSPEC  void  FFLogSetLevel(int level) {
	if (level >= FFL_LOG_LEVEL_CRIT && level < FFL_LOG_LEVEL_ALL) {
		FFL_LogSetLevel((FFL_LogLevel)level);
	}
}
DECLSPEC  void  FFLogPrint( int level, const char* format, ...) {
	if (level >= 0 && level < FFL_LogGetLevel()) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(level,format, args);
		va_end(args);		
	}
}
DECLSPEC void  FFLogPrintCri(const char* format, ...) {
	  va_list args;
	  va_start(args, format);
	  FFL_LogPrintV(FFLOG_LEVEL_CRIT, format, args);
	  va_end(args);	
}

DECLSPEC void  FFLogPrintErr(const char* format, ...) {
	if (FFL_LogGetLevel() > FFLOG_LEVEL_ERROR) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_ERROR, format, args);
		va_end(args);
	}
}

DECLSPEC void  FFLogPrintWar(const char* format, ...) {
	if (FFL_LogGetLevel() > FFLOG_LEVEL_WARNING) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_WARNING, format, args);
		va_end(args);
	}
}

DECLSPEC void  FFLogPrintInf(const char* format, ...) {
	if (FFL_LogGetLevel() > FFLOG_LEVEL_INFO) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_INFO, format, args);
		va_end(args);
	}
}


DECLSPEC void  FFLogPrintDbg(const char* format, ...) {
	if (FFL_LogGetLevel() > FFLOG_LEVEL_DEBUG) {
		va_list args;
		va_start(args, format);
		FFL_LogPrintV(FFLOG_LEVEL_DEBUG, format, args);
		va_end(args);
	}
}

