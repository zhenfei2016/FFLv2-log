/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  FFLog.cpp
*  Created by zhufeifei(34008081@qq.com) on 2018/08/31
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  �淶��־ϵͳ�ӿ�
*/
#include <FFL_lib.h>
#include "LogSender.hpp"

#define FFLOG_API_IMPLEMENT

#include <FFL_lib.h>
#include "FFLog.h"

FFL::LogSender gInstance;

extern "C" {
	//
	//  ��ʼ��ʼ��������ʼ����־ϵͳ
	//
	int FFLogInitialize() {
		FFL_initialize();
		gInstance.start(new FFL::ModuleThread("FFLog-module"));
		return 0;
	}
	void FFLogTerminate() {
		gInstance.stop();
	}
	//
	//  ������־������Ŀ��
	//
	int FFLogSetUrl(const char* url) {
		return gInstance.setUrl(url)?1:0;
	}
	static const char* KDefaultTag = NULL;
	//
	//  ��־�������
	//
	int FFLogPrint(int level, const char *format, ...) {
		int ret = 0;
		va_list args;
		va_start(args, format);
		ret = gInstance.write(level, KDefaultTag, format, args);
		va_end(args);
		return ret;
	}
	int FFLogPrintTag(int level, const char *tag, const char *format, ...) {
		int ret = 0;
		va_list args;
		va_start(args, format);
		ret=gInstance.write(level, tag,format, args);
		va_end(args);
		return ret;
	}
	int FFLogPrintV(int level, const char *format, va_list args) {
		return gInstance.write(level, KDefaultTag, format,args);
	}
}
