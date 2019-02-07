#include <stdio.h>
#include <FFL_lib.h>
#include "FFLog.h"
#include <net/http/FFL_HttpServer.hpp>

class HttpCb : public FFL::HttpServer::Callback{
public:
	HttpCb() {
	}

	//
	//  返回false则强制关闭这个连接
	//
	virtual bool onHttpQuery(FFL::HttpRequest* request) {
		FFL::HttpUrl url;
		request->getUrl(url);

		url.mQuery;
		return false;
	}

};
extern "C" int main(int argc ,const char* argv[]) {	
	FFLogInitialize();

	FFL::HttpServer server("127.0.0.1", 5000);

	FFL::sp<HttpCb> cb=new HttpCb();
	FFL::HttpServer::HttpApiKey key;
	key.mPath = "fflog";
	server.registerApi(key,cb);
	server.start(NULL);
	while (true) {
		server.eventLoop(NULL);
	}
	server.stop();
	FFLogTerminate();
	getchar();
	printf("press any key quit.\r");
	getchar();	
	return 0;
}
