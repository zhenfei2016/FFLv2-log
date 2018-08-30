/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  FFL_LogSenderType.hpp   
*  Created by zhufeifei(34008081@qq.com) on 2018/08/14 
*  https://github.com/zhenfei2016/FFL-v2.git
*  logsender��Ŀ������
*
*/
#ifndef _FFL_LOG_SENDER_TYPE_HPP_
#define _FFL_LOG_SENDER_TYPE_HPP_

namespace FFL {	

	enum LogSenderType {
		LOG_ST_NONE = 0,
		//
		//  һ��tcp���ӣ�����һ��������
		//
		LOG_ST_TCP_CONNECT=1,
		//
		//  �Ѿ��������ļ�
		//
		LOG_ST_EXIST_FILE = 2,
		//
		//  �´���һ���ļ�
		//
		LOG_ST_NEW_FILE = 3,
	};
	
}

#endif