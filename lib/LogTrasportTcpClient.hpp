/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogTrasportTcpClient.hpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/06
*  https://github.com/zhenfei2016/FFL-v2.git
*  日志转发接口实现类，通过tcp转发出去
*/
#ifndef _FFLOG_TRANSPORT_TCP_CLIENT_HPP_
#define _FFLOG_TRANSPORT_TCP_CLIENT_HPP_
#include "LogTrasport.hpp"
#include "LogUrl.hpp"
#include <net/FFL_TcpClient.hpp>

namespace FFL {
	class LogTranportTcpClient : public LogTranport{
	public:
		LogTranportTcpClient(const LogUrl& url);
		virtual ~LogTranportTcpClient();
	public:
		//
		//  发送实现函数
		//
		virtual bool sendPacket(FFL::sp<LogPacket>& packet);

	private:
		bool connect();
		void disConnect();
	protected:
		String mServerUrl;
		TcpClient* mClient;
	};
}

#endif