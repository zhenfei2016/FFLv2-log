/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  main.cpp   
*  Created by zhufeifei(34008081@qq.com) on 2018/07/26 
*  https://github.com/zhenfei2016/FFL-v2.git
*
*
*/
#include <stdio.h>
#include <utils/FFL_MemoryWatch.hpp>
extern int FFL_main();
const char* gExePath;
extern "C" int main(int argc ,const char* argv[]) {	
	FFL::startMemoryWatch();
    gExePath=FFL_strdup(argv[0]);       
    FFL_LogSetLevel(FFL_LOG_LEVEL_ALL);		
	FFL_main();	
	FFL_dumpMemoryLeak();	

	printf("press any key to exit");
	getchar();
	return 0;
}
