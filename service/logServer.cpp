
#include <FFL.h>
#include <FFL_CommandHelper.h>
#include <net/FFL_NetServer.hpp>
#include <net/http/FFL_Http.hpp>

#include <utils/FFL_StringHelper.hpp>

static int32_t gId=0;
class HttpApiGetLogListHandelr : public FFL::HttpApiHandler{
public:
    virtual void onHttpQuery(FFL::HttpConnect* conn, FFL::String& path, FFL::String& query){
        FFL::String json;     
        
        FFL::String jsonlist;
        
        int32_t id=gId+9;
        for(int32_t i=0;i<10;i++){
            FFL::formatString(json,"{\"id\":%d}",id--);
            
            if(jsonlist.size()!=0){
              jsonlist +=","+ json ;
            }else{
               jsonlist +=json ;
            }
        }
        
        gId +=10;
        jsonlist="[" +jsonlist + "]";
        
		if (json.size() > 0) {
			conn->createResponse()->writeJson(jsonlist);
		}
		conn->realese();
    }
    
};


class HttpCommFileHandelr : public FFL::HttpFileHandler {
	//
	//  返回是否处理这个请求
	//
	virtual bool onHttpFile(FFL::HttpConnect* conn, const FFL::String& path) {
		FFL::sp<FFL::HttpFileResponse> res = new FFL::HttpFileResponse(conn);
		char processdir[1024] = { 0 };
		char processname[1024] = { 0 };
		FFL_getCurrentProcessPath(processdir, 1023, processname);
        
		strcat(processdir, path.c_str());
		res->response(processdir);
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
	//ShellExecuteA(NULL,"open", "http://127.0.0.1:5000/timeline.html", NULL, NULL, SW_SHOW);
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

int serverMain() {
	FFL::HttpConnectMgr mgr;    
    FFL::sp<FFL::HttpApiHandler> handler=new HttpApiGetLogListHandelr();
    mgr.registerApi("/FFLv2?getLogList", handler);
	mgr.setFileHandler(new HttpCommFileHandelr());

	FFL::TcpServer server(NULL,5000);
	server.setConnectManager(&mgr);
	server.start();
	//
	//  打印一下帮助函数
	//
	FFL_cmdUsage(gCmdOption);

	FFL_inputLooper(gCmdOption, 0, quitFlag);
	return 0;
}
