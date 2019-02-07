/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  FFLog.h   
*  Created by zhufeifei(34008081@qq.com) on 2018/08/31 
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  日志系统对外接口文件
*
*/
#ifndef _FFLV2_LOG_LIB_H_
#define _FFLV2_LOG_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif 	

#define FFLOG_API_IMPORT __declspec(dllimport)
#define FFLOG_API_EXPORT __declspec(dllexport)
	//
	//  如果脚本定义了编译动态库
#if  defined(FFLogLib_EXPORTS)
#define FFLOG_API_IMPORT_EXPORT FFLOG_API_EXPORT
#else
#define FFLOG_API_IMPORT_EXPORT FFLOG_API_IMPORT
#endif

	//
	//  开始初始化，反初始化日志系统
	//
	FFLOG_API_IMPORT_EXPORT int  FFLogInitialize();
	FFLOG_API_IMPORT_EXPORT void FFLogTerminate();
	//
	//  设置日志的生成目标
	//
	FFLOG_API_IMPORT_EXPORT int  FFLogSetUrl(const char* url);
	//
	//  日志输出函数
	//
	FFLOG_API_IMPORT_EXPORT int  FFLogPrint(int level, const char *format, ...);
	FFLOG_API_IMPORT_EXPORT int  FFLogPrintTag(int level, const char *tag, const char *format, ...);
	FFLOG_API_IMPORT_EXPORT int  FFLogPrintV(int level, const char *format, va_list args);
	
#ifdef __cplusplus
}
#endif 

#endif 