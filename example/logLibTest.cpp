#include <FFL.h>
#include <FFL_CommandHelper.h>
#include <thread/FFL_Thread.hpp>
#include <net/base/FFL_Net.h>
#include "../loglib/FFLv2Log.h"

static int gExitFlag = 0;
void quit(const char* args, void* userdata) {
	
	gExitFlag = 1;
	printf("exit sys. \n");
}
static int quitFlag(void* userdata) {
	return gExitFlag;
}


static void getNewLogFilePath(char* path,size_t size){
    static int gFilePathIndex = 1;
    char processDir[1024]={};
    FFL_getCurrentProcessPath(processDir, 1024, NULL);
    snprintf(path,size, "%slogsender_%d.txt", processDir,gFilePathIndex++);

}
void setTarget(const char* args, void* userdata) {
 
    char path[1024]={};
    getNewLogFilePath(path, 1024);
   
	FFLogSetUrl(FFLOG_ST_NEW_FILE, path);
}

static CmdOption  gCmdOption[] = {
	{ "exit",0,quit,"exit sys." },	
	{ "setTarget",0,setTarget,"set log Target file path." },
	{ 0,0,0,0 },
};


static int32_t gIndex = 0;
class TestThread : public FFL::Thread {
public:
	virtual bool threadLoop() {
		FFLOG_ERROR("test =%d", gIndex++);
		FFL_sleep(1000 * 5);
		return gExitFlag!=1;
	}
};
int FFL_main() {
	//
	//  模拟日志输入
	//
	FFL::sp<TestThread> testThread = new TestThread();
	testThread->run("test");

	//
	//
	//
    char path[1024]={};
    getNewLogFilePath(path, 1024);
	FFLogSetUrl(FFLOG_ST_NEW_FILE, path);
	FFLogSetLevel(FFLOG_LEVEL_ALL);
	FFLogSetup();
	//
	//  打印一下帮助函数
	//
	FFL_cmdUsage(gCmdOption);
	FFL_cmdLooper(gCmdOption,0, quitFlag);
	FFLogTerminate();
	testThread->requestExitAndWait();

	return 0;
}
