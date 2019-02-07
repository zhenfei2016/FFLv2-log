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
*  日志发送管理器 
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
		//  url : 目标日志的路径
		//  startup前需要进行设置的
		//  startup中设置，会更新目标文件的
		//
		bool setUrl(const char* url);
		//
		//  写日志
		//
		bool write(int level, const char* tag, const char* data, size_t len);
		bool write(int level, const char* tag, const char *format, va_list args);
		bool write(int level, const char* tag, const char *format, ...);
	protected:
		//
		//  调用。start，stop会触发onStart,onStop的执行
		//  onStart :表示准备开始了 ,可以做一些初始化工作
		//  onStop :表示准备停止了 ,可以做停止前的准备，想置一下信号让eventloop别卡住啊 
		//  在这些函数中，不要再调用自己的函数，例如：start,stop, isStarted等
		//
		virtual bool onStart();
		virtual void onStop();
		//
		//   阻塞的线程中执行的eventloop,返回是否继续进行eventLoop
		//   waitTime:输出参数，下一次执行eventLoop等待的时长
		//   true  : 继续进行下一次的eventLoop
		//   false : 不需要继续执行eventloop
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