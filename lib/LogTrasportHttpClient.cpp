#include "LogTrasportHttpClient.hpp"
#include <net/http/FFL_HttpRequest.hpp>
#include <net/http/FFL_HttpClientAccess.hpp>

namespace FFL {
	LogTranportHttpClient::LogTranportHttpClient(const LogUrl& url){
		mHttpMgr = new HttpClientAccessManager();
		mHttpMgr->start();
		mUrl = url.mUrl;
	}
	LogTranportHttpClient::~LogTranportHttpClient() {
		mHttpMgr->stop();
		FFL_SafeFree(mHttpMgr);
	}
	//
	//  发送实现函数
	//
	bool LogTranportHttpClient::sendPacket(FFL::sp<LogPacket>& packet) {				
		FFL::sp<HttpRequest> request = new FFL::HttpRequest(NULL);

		FFL::HttpUrl url;
		url.parse(mUrl);		
		request->setUrl(url);		

		FFL::String info;
		packet->toString(info);
		request->setContent((uint8_t*)info.string(),info.size());
		mHttpMgr->post(request,NULL);
		return true;
	}
}


