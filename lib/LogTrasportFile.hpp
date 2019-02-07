
/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogTrasportFile.hpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/05
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  日志转发接口，保存日志文件
*/
#ifndef _FFLOG_TRANSPORT_FILE_HPP_
#define _FFLOG_TRANSPORT_FILE_HPP_
#include "LogTrasport.hpp"

namespace FFL {
	class LogTranportFile : public LogTranport{
	public:
		LogTranportFile(const char* filePath);
		virtual ~LogTranportFile();
	public:
		//
		//  发送实现函数
		//
		virtual bool sendPacket(FFL::sp<LogPacket>& packet);
	protected:
		FFL::File mFile;
	};
}

#endif