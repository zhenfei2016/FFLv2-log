#include <stdio.h>
#include <FFL_lib.h>
#include "FFLog.h"

extern "C" int main(int argc ,const char* argv[]) {	
	FFLogInitialize();

	FFLogSetUrl("file://d:/123.txt");	
	while (1) {
		char ch=getchar();
		if (ch == 'q') {
			FFLogPrint(1, "hi: nowms= %u  exit", FFL_getNowMs());
			break;
		}
		FFLogPrint(1, "hi:char=%c nowms= %u",ch, FFL_getNowMs());		
	}

	FFLogTerminate();
	getchar();
	printf("press any key quit.\r");
	getchar();	
	return 0;
}
