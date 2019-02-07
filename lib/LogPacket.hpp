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
*  ÿһ������־���ݽṹ
*/
#ifndef _LOG_PACKET_HPP_
#define _LOG_PACKET_HPP_

#include <FFL_lib.hpp>


namespace FFL {		
	typedef enum LogFlag {
		//
		// ԭʼ������
		//
		LOGF_RAW_DATA = 0,
		//
		//  ���ͷ��Ϣ������
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
		//  ����id���߳�id,ʱ��
		//
		int32_t mPid;
		int32_t mTid;
		int64_t mTimeus;
		//
		//  ��־���𣬴�С��tag���ƣ���־����
		//
		int mLevel;
		size_t mSize;
		String mTag;
		String mData;

		LogFlag  mFlag;
	};
	
}

#endif