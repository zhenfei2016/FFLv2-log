/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  FFLv2Log.h   
*  Created by zhufeifei(34008081@qq.com) on 2018/08/31 
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  日志系统对外接口文件
*  
*  example:
*  FFLogConfig();
*  FFLogSetup();
*  FFLogPrint...();
*  FFLogTerminate();
*
*/
#ifndef _FFLV2_LOG_LIB_H_
#define _FFLV2_LOG_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif 	
	//
	//  对应FFL_logSender中的相关值
	//
	enum FFLogTargetType{
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
	//  对应FFLv2中的相应值
	//
	enum FFLogLevel{
		FFLOG_LEVEL_CRIT = 0,
		FFLOG_LEVEL_ERROR,
		FFLOG_LEVEL_WARNING,
		FFLOG_LEVEL_INFO,
		FFLOG_LEVEL_DEBUG,
		FFLOG_LEVEL_ALL
	};
#pragma pack(1)
	typedef struct FFLogProperty{
		//
		//  结构大小，相当结构的版本号
		//
		int size;
		//
		//  日志级别
		//
		FFLogLevel level;
		//
		//  日志目标存储类型,目标类型
		//
		FFLogTargetType targetType;
		const char* targetUrl;
	}FFLogProperty;
#pragma pack()

#ifndef FFLOG_API_IMPLEMENT
	//
	//   开始安装日志系统，返回0表示成功
	//
	int FFLogSetup();
	//
	//   结束日志系统
	//
	void FFLogTerminate();
	//
	//  配置日志系统
	//
	void FFLogConfig(FFLogProperty* property);
	//
	//  设置日志的生成目标
	//
	void  FFLogSetUrl(int type, const char* url);
	//
	//  设置日志级别
	//
	void  FFLogSetLevel(int level);
	//
	//  打印日志
	//
	void  FFLogPrint(int level, const char* format, ...);
	void  FFLogPrintCri(const char* format, ...);
	void  FFLogPrintErr(const char* format, ...);
	void  FFLogPrintWar(const char* format, ...);
	void  FFLogPrintInf(const char* format, ...);
	void  FFLogPrintDbg(const char* format, ...);
#define FFLOG_CRIT        FFLogPrintCri
#define FFLOG_ERROR       FFLogPrintErr
#define FFLOG_WARNING     FFLogPrintWar
#define FFLOG_INFO        FFLogPrintInf
#define FFLOG_DEBUG       FFLogPrintDbg

#endif // 
	
#ifdef __cplusplus
}
#endif 

#endif 