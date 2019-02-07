/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogTrasport.cpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/05
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  日志转发接口类
*/

#include "LogTrasport.hpp"
#include "LogTrasportFile.hpp"
#include "LogTrasportTcpClient.hpp"
#include "LogUrl.hpp"

namespace FFL {
	LogTranport::LogTranport(){
	}
	LogTranport::~LogTranport() {
	}
	//
	//  创建跟url匹配的transport
	//
	LogTranport* LogTranport::create(const char* url, void* data) {
		if (url == NULL) {
			return NULL;
		}

		LogUrl logUrl(url);
		logUrl.mProtol;

		LogTranport* transport = NULL;
		if (LogUrl::isFile(&logUrl)) {
			// file://
			transport = new LogTranportFile(logUrl.mUrl.string()+7);
		}
		else
		{

		}

		//transport = new LogTranportHttpClient(logUrl);
		//transport = new LogTranportHttpServer(logUrl);

		return transport;
	}
}


