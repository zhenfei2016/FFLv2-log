/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  main-simple.cpp   
*  Created by zhufeifei(34008081@qq.com) on 2018/08/22 
*  https://github.com/zhenfei2016/FFLv2-log.git
*
*
*/
#include <stdio.h>
#include "../loglib/logLib.h"

extern "C" int main(int argc ,const char* argv[]) {			
	char logPath[1024] = {};
	snprintf(logPath, 1023, "%s.log", argv[0]);


	int i = 0;
	FFLogSetLevel(FFLOG_LEVEL_ALL);
	//
	//  ����Ŀ��Ϊ����һ���µ���־�ļ�
	//
	FFLogSetUrl(FFLOG_ST_NEW_FILE,logPath);
	void* log=FFLogCreateInstance();
	

	FFLOG_CRIT("crit=%d",i++);
	FFLOG_ERROR("error=%d", i++);
	FFLOG_WARNING("warning=%d", i++);
	FFLOG_INFO("info=%d", i++);
	FFLOG_DEBUG("debug=%d", i++);

	//
	//  FFLOG_xxx  ϵ�еĺ궼���첽����ģ�����getchar�����ܱ�֤���ݶ�д��ȥ��
	//  
	printf("press any key exit");
	getchar();

	FFLogDestroyInstance(log);	
	return 0;
}
