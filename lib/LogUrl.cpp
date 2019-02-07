/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogUrl.cpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/05
*  https://github.com/zhenfei2016/FFL-v2.git
*  外部设置的URL，分离出协议，参数等
*/
#include "LogUrl.hpp"
namespace FFL {
	LogUrl::LogUrl(const char* url) {
		parseUrl(url);
	}

	LogUrl::~LogUrl() {

	}

	bool LogUrl::isFile(LogUrl* logUrl) {
		return (logUrl != NULL && logUrl->mProtol.equal("file"));
	}

	bool LogUrl::isTcpClient(LogUrl* logUrl) {
		return (logUrl != NULL && logUrl->mProtol.equal("tcp"));
	}

	bool LogUrl::parseUrl(const char* url) {
		if (url == NULL || url[0] == NULL) {
			return false;
		}

		String inputUrl(url);
		int pos=inputUrl.find(":");
		if (pos < 0) {
			return false;
		}

		mProtol.setTo(inputUrl.string(), pos);
		mUrl = url;
		return true;
	}
}
