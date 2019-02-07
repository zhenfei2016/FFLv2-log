/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogUrl.hpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/05
*  https://github.com/zhenfei2016/FFL-v2.git
*  外部设置的URL，分离出协议，参数等
*/
#ifndef _LOG_URL_HPP_
#define _LOG_URL_HPP_

#include <FFL_String.hpp>

namespace FFL {	
	
	class LogUrl{
	public:
		LogUrl(const char* url);
		~LogUrl();

	public:
		bool static isFile(LogUrl* logUrl);
		bool static isTcpClient(LogUrl* logUrl);
		bool static isHttpClient(LogUrl* logUrl);

	public:
		bool parseUrl(const char* url);

		String mProtol;		
		String mUrl;
	};
}

#endif