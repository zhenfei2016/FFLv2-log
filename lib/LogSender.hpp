/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogSender.hpp   
*  Created by zhufeifei(34008081@qq.com) on 2018/08/05 
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  ��־���͹����� 
*/
#ifndef _LOG_SENDER_HPP_
#define _LOG_SENDER_HPP_

#include <FFL_lib.hpp>
#include <FFL_Mutex.hpp>
#include <FFL_BlockList.hpp>
#include "LogPacket.hpp"

namespace FFL {	
	class LogTranport;
	class LogSender : public FFL::Module{
	public:
		LogSender();
		~LogSender();	
		//				
		//  url : Ŀ����־��·��
		//  startupǰ��Ҫ�������õ�
		//  startup�����ã������Ŀ���ļ���
		//
		bool setUrl(const char* url);
		//
		//  д��־
		//
		bool write(int level, const char* tag, const char* data, size_t len);
		bool write(int level, const char* tag, const char *format, va_list args);
		bool write(int level, const char* tag, const char *format, ...);
	protected:
		//
		//  ���á�start��stop�ᴥ��onStart,onStop��ִ��
		//  onStart :��ʾ׼����ʼ�� ,������һЩ��ʼ������
		//  onStop :��ʾ׼��ֹͣ�� ,������ֹͣǰ��׼��������һ���ź���eventloop��ס�� 
		//  ����Щ�����У���Ҫ�ٵ����Լ��ĺ��������磺start,stop, isStarted��
		//
		virtual bool onStart();
		virtual void onStop();
		//
		//   �������߳���ִ�е�eventloop,�����Ƿ��������eventLoop
		//   waitTime:�����������һ��ִ��eventLoop�ȴ���ʱ��
		//   true  : ����������һ�ε�eventLoop
		//   false : ����Ҫ����ִ��eventloop
		//
		virtual bool eventLoop(int32_t* waitTime) ;
	private:
		bool mLogStartuped;
		FFL::sp<LogTranport> mTranport;

	protected:		
		FFL::BlockingList< FFL::sp<LogPacket> > mLogList;
	};
}

#endif