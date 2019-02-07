/*
*  This file is part of FFL project.
*
*  The MIT License (MIT)
*  Copyright (C) 2017-2018 zhufeifei All rights reserved.
*
*  LogSender.cpp
*  Created by zhufeifei(34008081@qq.com) on 2018/08/05
*  https://github.com/zhenfei2016/FFL-v2.git
*
*  日志发送管理器
*/

#include "LogSender.hpp"
#include "LogTrasport.hpp"
#define MAX_LOG_LENGTH 4096

namespace FFL {
	//
	//  最多保存1000个未处理的数据包
	//
#define KMaxPacketSize 1000

	LogSender::LogSender():mLogList(NULL, KMaxPacketSize){
		mLogStartuped = false;				
	}
	LogSender::~LogSender() {			
	}	
	//		
	//  type：目标日志的类型
	//  url : 目标日志的路径
	//  startup前需要进行设置的
	//  startup中设置，会更新目标文件的
	//
	bool LogSender::setUrl(const char* url) {		
		if (!mTranport.isEmpty()) {
			return false;
		}

		mTranport = LogTranport::create(url, this);
		return !mTranport.isEmpty();
	}	
	//
	//  写日志
	//
	bool LogSender::write(int level, const char* tag, const char* data, size_t len) {
		if (!isStarted() || mTranport.isEmpty()) {
			return false;
		}

		FFL::sp<LogPacket> packet = new LogPacket();
		packet->mPid = 0;
		packet->mTid = (int32_t)FFL_CurrentThreadID();
		packet->mTimeus = FFL_getNowUs();

		packet->mLevel = level;
		packet->mSize = len;
		packet->mTag.setTo(tag ? tag : "");
		packet->mData.setTo(data,len);
		packet->mFlag = LOGF_RAW_DATA;
		return mLogList.incoming(packet);
	}
	bool LogSender::write(int level, const char* tag, const char *format, va_list args) {
		if (!isStarted() || mTranport.isEmpty()) {
			return false;
		}

		char data[MAX_LOG_LENGTH] = { 0 };
		size_t size = vsnprintf(data, MAX_LOG_LENGTH - 1, format, args);
		if (size > 0) {
			size += 1;
		}
		else {
			return false;
		}

		FFL::sp<LogPacket> packet=new LogPacket();
		packet->mPid = 0;
		packet->mTid = (int32_t)FFL_CurrentThreadID();
		packet->mTimeus = FFL_getNowUs();

		packet->mLevel = level;
		packet->mSize = size;
		packet->mTag.setTo(tag? tag:"");
		packet->mData.setTo(data, size);
		packet->mFlag = LOGF_RAW_DATA;
		return mLogList.incoming(packet);		
	}
	bool LogSender::write(int level, const char* tag, const char *format, ...) {
		if (!isStarted() || mTranport.isEmpty()) {
			return false;
		}

		bool ret=false;
		if (!mTranport.isEmpty()) {
			va_list args;
			va_start(args, format);
			ret= write(level, tag, format, args);
			va_end(args);			
		}
		return ret;
	}

	//
	//  调用。start，stop会触发onStart,onStop的执行
	//  onStart :表示准备开始了 ,可以做一些初始化工作
	//  onStop :表示准备停止了 ,可以做停止前的准备，想置一下信号让eventloop别卡住啊 
	//  在这些函数中，不要再调用自己的函数，例如：start,stop, isStarted等
	//
	bool LogSender::onStart() {
		mLogList.start();
		mLogStartuped = true;
		return true;
	}
	void LogSender::onStop() {
		mLogList.stop();
		mLogStartuped = false;
		return;
	}
	//
	//   阻塞的线程中执行的eventloop,返回是否继续进行eventLoop
	//   waitTime:输出参数，下一次执行eventLoop等待的时长
	//   true  : 继续进行下一次的eventLoop
	//   false : 不需要继续执行eventloop
	//
	bool LogSender::eventLoop(int32_t* waitTime) {
		int32_t erroNo=0;
		FFL::sp<LogPacket> packet=mLogList.next(&erroNo);
		if (!packet.isEmpty()) { 
			mTranport->sendPacket(packet);
		}
		else {
			mTranport = NULL;
			return false;
		}
		
		return true;
	}
}
