#include <iostream>
#include <string>

#include "udt.h"

#include <Windows.h>

#ifndef WIN32
void* monitor(void*);
#else
DWORD WINAPI monitor(LPVOID);
#endif

//uint64_t lastick = 0;
/*
void p2p_connect_handler(int err,const char* reason, void* arg)
{
	DWORD dwNow = ::GetTickCount();

	re_printf("connect ok, spend(s):%d\n", (DWORD)(dwNow-lastick)/1000);
}

void p2p_init_handler(int err, struct p2p* p2p)
{
	re_printf("init return:%d\n", err);
}
void p2p_receive_handler(const char* data, uint32_t len, void *arg)
{
	re_printf("p2p receive data:%s\n", data);
}

void p2p_request_handler(struct p2p *p2p, const char* peername, struct p2pconnection **ppconn)
{
	int err;
	err = p2p_accept(p2p, ppconn, peername, p2p_receive_handler, *ppconn);
	if (err)
	{
		re_fprintf(stderr, "p2p accept error:%s\n", strerror(err));
	}
}

static int print_handler(const char *p, size_t size, void *arg)
{
	struct pl *pl = (struct pl*)arg;

	if (size > pl->l)
		return ENOMEM;

	memcpy((void *)pl->p, p, size);

	pl_advance(pl, size);

	return 0;
}


void print_icem(struct icem *icem)
{
	struct re_printf pt;
	struct pl pl;
	char *buf = new char[2048];

	memset(buf, 0, 2048);
	pl.l = 2048;
	pl.p = buf;
	pt.vph = print_handler;
	pt.arg = &pl;

	memset(buf, 0, 2048);
	pl.l = 2048;
	pl.p = buf;
	icem_debug(&pt, icem);
	re_printf("%s\n",buf);
}*/



int main(int argc, char* argv[])
{
#ifdef WIN32
	char* filePath = argv[0];
	memset(argv, 0, sizeof(argv));
	argc = 2;
	argv[0] = filePath;
	argv[1] = "7777";
#endif

	//usage: sendfile [server_port]
	if ((2 < argc) || ((2 == argc) && (0 == atoi(argv[1]))))
	{
		std::cout << "usage: sendfile [server_port]" << std::endl;
		return 0;
	}

	int err;
	err = UDT::p2p_init("54.254.169.186", 3456, "54.254.169.186", 3478, "zhujianwen", "123456");
	if (err)
	{
		std::cout<< "p2p_init error"<<std::endl;
		goto out;
	}

	UDTSOCKET psock = 0;

	char buf[100] = {0};
	while (gets_s(buf))
	{
		if (strcmp("connect", buf) == 0)
		{
			char msg[1024] = {0};
			gets_s(msg);
			err = UDT::p2p_connect("liuhong");
		}
		else if (strcmp("send", buf) == 0)
		{
			char msg[1024] = {0};
			gets_s(msg);
			err = UDT::p2p_send("liuhong", msg, strlen(msg));
		}
		else if (strcmp("exit", buf) == 0)
		{
			break;
		}
	}

out:
	UDT::p2p_close();
	return err;
}