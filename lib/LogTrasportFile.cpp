
/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogTrasportFile.cpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/05
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  日志转发接口，保存日志文件
*/

#include "LogTrasportFile.hpp"

namespace FFL {
	LogTranportFile::LogTranportFile(const char* filePath) {
		String path(filePath);
		mFile.create(path);
	}
	LogTranportFile::~LogTranportFile() {
		mFile.close();
	}
	//
	//  发送实现函数
	//
	bool LogTranportFile::sendPacket(FFL::sp<LogPacket>& packet) {
		String info;
		packet->toString(info);
		if (info.size() > 0) {
			mFile.write((void*)(info.string()), info.size(), NULL);
		}
		return true;
	}
}


