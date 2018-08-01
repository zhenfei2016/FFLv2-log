
#include <FFL.h>
#include <FFL_CommandHelper.h>
#include <net/FFL_NetServer.hpp>
#include <net/http/FFL_Http.hpp>

#include <utils/FFL_StringHelper.hpp>


class  LogMap {
	public:
		LogMap() {
			mIndex = 0;
		}
		void add(uint8_t* data, int32_t len) {
			FFL::String info;
			info = (const char*)data;

			FFL::CMutex::Autolock l(mLock);
			while (mLogList.size() > 20) {
				mLogList.pop_front();
			}

			mLogList.push_back(info);
		}

		int mIndex;
		void getJson(FFL::String& jsonList) {
			FFL::CMutex::Autolock l(mLock);		
			if (mLogList.size() < 1) {
				return;
			}

			int32_t count = 0;
			while (mLogList.size() > 0) {
				FFL::String json;
				json = mLogList.front();
				mLogList.pop_front();

				if (jsonList.size() == 0) {
					jsonList = json;
				}
				else
				{
					jsonList = jsonList + "\n" + json;
				}
				count++;
				if (count >= 10) {
					break;
				}
			}
		}

		FFL::List< FFL::String > mLogList;
		FFL::CMutex mLock;
};
static LogMap  gLogMap;
static int32_t gId=0;
class HttpApiGetLogListHandelr : public FFL::HttpApiHandler{
public:
    virtual void onHttpQuery(FFL::HttpConnect* conn,FFL::String& query,FFL::HttpRequest* req){                 
        FFL::String jsonlist;        
		gLogMap.getJson(jsonlist);
        
      //  jsonlist="[" +jsonlist + "]";
        
		if (jsonlist.size() > 0) {
			conn->createResponse()->writeJson(jsonlist);
		}
		conn->realese();
    }
    
};

extern const char* gExePath;

class HttpCommFileHandelr : public FFL::HttpFileHandler {
	//
	//  返回是否处理这个请求
	//
	virtual bool onHttpFile(FFL::HttpConnect* conn, const FFL::String& path) {
		FFL::sp<FFL::HttpFileResponse> res = new FFL::HttpFileResponse(conn);
		char processdir[1024] = { 0 };
		char processname[1024] = { 0 };
		FFL_getCurrentProcessPath(processdir, 1023, processname);
        
        FFL::String fullpath=gExePath;
        fullpath +="/../" +path;
		strcat(processdir, path.c_str());
        
        printf("file:%s",fullpath.c_str());
		res->response(fullpath.c_str());
		conn->realese();
		return true;
	}
};

static int gExitFlag = 0;
void trackExit(const char* args, void* userdata) {	
	gExitFlag = 1;	
	printf("exit sys. \n");
}
static int quitFlag(void* userdata) {
	return gExitFlag;
}
void startService(const char* args, void* userdata) {	
	printf("startService. \n");
}
void restartService(const char* args, void* userdata) {	
	printf("restartService. \n");
}
void stopService(const char* args, void* userdata) {	
	printf("stopService. \n");
}

void openTool(const char* args, void* userdata) {
#if WIN32
	//ShellExecuteA(NULL,"open", "http://127.0.0.1:5000/index.html", NULL, NULL, SW_SHOW);
#else
    printf("failed to openTool. \n");
#endif
}


static CmdOption  gCmdOption[] = {
	{ "exit",0,trackExit,"exit sys." },	
	//{ "start",0,startService,"start service" },
	//{ "restart",0,restartService,"re start service" },
	//{ "stop",0,stopService,"stop service" },
	//{ "open",0,openTool,"open timeline tool" },
	{ 0,0,0,0 },
};


class MyTcpConnect : public FFL::TcpConnect {
public:
	MyTcpConnect(NetFD fd,FFL::NetServer* srv): FFL::TcpConnect(fd), mSocket(fd){
	}

	virtual bool process() {
		uint8_t buf[4096] = {};
		size_t readed=0;
        if(FFL_OK!=mSocket.read(buf,4095,&readed)){
            printf("socket read failed");
            return false;
        }

		if (readed > 0) {
			gLogMap.add(buf, readed);
		}

		return true;			 
	}

	FFL::CSocket mSocket;
};
int serverMain() {
	//
	//  http  server
	//
	FFL::HttpConnectMgr mgr;    
    FFL::sp<FFL::HttpApiHandler> handler=new HttpApiGetLogListHandelr();
    mgr.registerApi("/FFLv2?getLogList", handler);
	mgr.setFileHandler(new HttpCommFileHandelr());
	FFL::TcpServer server(NULL,5000);
	server.setConnectManager(&mgr);
	server.start();


	//
	//  tcp  server
	//
	FFL::TcpServer tcpServer(NULL, 5100);
	FFL::SimpleConnectManager<MyTcpConnect> tcpMgr;
	tcpServer.setConnectManager(&tcpMgr);
	tcpServer.start();

	//
	//  打印一下帮助函数
	//
	FFL_cmdUsage(gCmdOption);

	FFL_inputLooper(gCmdOption, 0, quitFlag);
	return 0;
}
