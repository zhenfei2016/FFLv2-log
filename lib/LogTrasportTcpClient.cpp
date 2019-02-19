/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogTrasportTcpClient.cpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/06
*  https://github.com/zhenfei2016/FFL-v2.git
*  日志转发接口实现类，通过tcp转发出去
*/
#include "LogTrasportTcpClient.hpp"
#include <net/FFL_NetUtils.hpp>

namespace FFL {
	LogTranportTcpClient::LogTranportTcpClient(const LogUrl& url):mClient(NULL){
		mServerUrl=url.mUrl.string() + url.mProtol.size()+3;
	}
	LogTranportTcpClient::~LogTranportTcpClient() {
		disConnect();
	}
	//
	//  发送实现函数
	//
	bool LogTranportTcpClient::sendPacket(FFL::sp<LogPacket>& packet) {
		if(!connect()){
			return false;
		}

		if (mClient != NULL) {
			String info;
			packet->toString(info);
			//
			//  数据量不是很大不判断是否成功了
			//
			mClient->write((void*)info.string(), info.size(), NULL);
		}
		return true;
	}

	bool LogTranportTcpClient::connect() {
		if (mClient != NULL) {
			return true;
		}

		mClient = new TcpClient();
		String ip;
		int16_t port = 0;
		FFL_parseHostport(mServerUrl, ip, port);
		if (FFL_OK != TcpClient::connect(ip, port, *mClient)) {
			FFL_SafeFree(mClient);
			return false;
		}

		return true;
	}
	void LogTranportTcpClient::disConnect() {
		if (mClient != NULL) {
			mClient->close();
			FFL_SafeFree(mClient);
		}
	}
}


