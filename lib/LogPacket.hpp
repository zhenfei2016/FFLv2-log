/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogPacket.hpp   
*  Created by zhufeifei(34008081@qq.com) on 2019/02/04 
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  每一条的日志内容结构
*/
#ifndef _LOG_PACKET_HPP_
#define _LOG_PACKET_HPP_

#include <FFL_lib.hpp>


namespace FFL {		
	typedef enum LogFlag {
		//
		// 原始裸数据
		//
		LOGF_RAW_DATA = 0,
		//
		//  添加头信息的数据
		//
		LOGF_ADDHEAD_DATA = 1,
	}LogFlag;

	class LogPacket : public RefBase{
	public:
		LogPacket() {}
		virtual ~LogPacket();

	public:
		void toString(String& string);

		//
		//  进程id，线程id,时间
		//
		int32_t mPid;
		int32_t mTid;
		int64_t mTimeus;
		//
		//  日志级别，大小，tag名称，日志内容
		//
		int mLevel;
		size_t mSize;
		String mTag;
		String mData;

		LogFlag  mFlag;
	};
	
}

#endif