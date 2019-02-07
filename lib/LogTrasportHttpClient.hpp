
#ifndef _FFLOG_TRANSPORT_HTTPCLIENT_HPP_
#define _FFLOG_TRANSPORT_HTTPCLIENT_HPP_
#include "LogTrasport.hpp"
#include "LogUrl.hpp"

namespace FFL {
	class HttpClientAccessManager;
	class LogTranportHttpClient: public LogTranport{
	public:
		LogTranportHttpClient(const LogUrl& url);
		virtual ~LogTranportHttpClient();
	public:
		//
		//  发送实现函数
		//
		virtual bool sendPacket(FFL::sp<LogPacket>& packet);	
	protected:
		HttpClientAccessManager* mHttpMgr;
		String mUrl;
	};
}

#endif