#include "LogTrasportHttpClient.hpp"
#include <net/http/FFL_HttpRequestBuilder.hpp>
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
		HttpRequestBuilder builder;
		FFL::sp<HttpRequest> request = builder.createRequest(NULL);

		FFL::HttpUrl url;
		url.parse(mUrl);

		FFL::String info;
		packet->toString(info);
		url.mQuery = "d=";
		url.mQuery += info;

		request->setUrl(url);		
		mHttpMgr->post(request,NULL);

		return true;
	}
}


