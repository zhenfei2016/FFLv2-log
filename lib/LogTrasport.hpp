/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogTrasport.hpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/05
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  日志转发接口类
*/

#ifndef _FFLOG_TRANSPORT_HPP_
#define _FFLOG_TRANSPORT_HPP_
#include <FFL_lib.hpp>
#include "LogPacket.hpp"

namespace FFL {
	class LogTranport : public RefBase{
	public:
		LogTranport();
		virtual ~LogTranport();
	public:
		//
		//  创建跟url匹配的transport
		//
		static LogTranport* create(const char* url, void* data);
	public:
		//
		//  发送实现函数
		//
		virtual bool sendPacket(FFL::sp<LogPacket>& packet)=0;
	};
}

#endif