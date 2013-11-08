// UDTTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include "UdtProxy.h"

int _tmain(int argc, _TCHAR* argv[])
{
	printf("\t/***********************************\n");
	printf("\t 1 - 发送文本消息   2 - 发送单多文件\n\t 3 - 确定接收文件   4 - 拒绝接收文件\n\t 5 - 停止发送文件   6 - 停止接收文件\n");
	printf("\t ***********************************/\n");

	CUdtProxy * pUdt = CUdtProxy::GetInStance();
	pUdt->core()->StartListen(7777, 7778);
	int sock;
	char ip[32] = {0};
	char buf[256] = {0};

	while (gets_s(buf))
	{
		if (strcmp(buf, "1") == 0)
		{
			printf("输入目标IP：");
			gets_s(ip);
			printf("输入消息内容 :");
			gets_s(buf);
			pUdt->core()->SendMsg(ip, buf, "zhujianwen");
		}
		else if (strcmp(buf, "2") == 0)
		{
			printf("输入目标IP：");
			gets_s(ip);
			printf("输入文件名全路径 , end 结束输入\n");
			std::vector<std::string> vecNames;
			char fileName[256];
			while (gets_s(fileName) != NULL)
			{
				if (strcmp("end", fileName) == 0)
					break;
				vecNames.push_back(fileName);
			}
			sock = pUdt->core()->SendFiles(ip, vecNames, "HTC G18", "ANDROID", "zhujianwen", "WIN7", "GENIETURBO");
		}
		else if (strcmp(buf, "3") == 0)
		{
			char path[MAX_PATH];
#if WIN32
			GetCurrentDirectoryA(MAX_PATH, path);
#else
			if (NULL == getcwd(path, MAX_PATH))
				Error("Unable to get current path");
#endif
			if ('\\' != path[strlen(path)-1])
			{
				strcat(path, ("\\"));
			}
			pUdt->core()->ReplyAccept(pUdt->GetSockID(1), "D:\\Genie\\Recv\\");
		}
		else if (strcmp(buf, "4") == 0)
		{
			pUdt->core()->ReplyAccept(pUdt->GetSockID(1), "REJECT");
		}
		else if (strcmp(buf, "5") == 0)
		{
			// stop send file
			pUdt->core()->StopTransfer(sock, 1);
		}
		else if (strcmp(buf, "6") == 0)
		{
			// stop recv file
			pUdt->core()->StopTransfer(pUdt->GetSockID(1), 2);
		}
		else if (strcmp(buf, "0") == 0)
		{
			printf("quit.....\n");
			break;
		}
	}

	pUdt->core()->StopListen();
	
	return 0;
}

