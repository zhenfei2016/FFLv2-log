/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogPacket.cpp
*  Created by zhufeifei(34008081@qq.com) on 2019/02/04
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  每一条的日志内容结构
*/
#include "LogPacket.hpp"

namespace FFL {
	LogPacket::~LogPacket() {
	}
	void LogPacket::toString(String& string) {		
		if (mFlag == LOGF_RAW_DATA) {
			char timeFormat[64] = { 0 };
			FFL_usToString(mTimeus, timeFormat, 63);

			string=String::format("%s:%s tid = %d %s \n",
				FFL_LogGetLevelString(mLevel),
				timeFormat,
				(int)FFL_CurrentThreadID(),
				mData.string());
		}
		else {
			string = mData;
		}
	}
}