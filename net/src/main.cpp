/*
 * main.cpp
 * Copyright (C) 2019/04/09 LQ 
 *
 * Distributed under terms of the MIT license.
 */

#include <list>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <string>
#include "utility.h"
#include "net.h"

using namespace std;


int main(int argc,char** argv)
{
	if(argc < 2)
	{
		printf("args error: %d",argc);
		return 0;
	}
	int port = 8003;
	
	int mode = atoi(argv[1]);
	if(mode == 0)
	{
		if(argc == 3)
		{
			port = atoi(argv[2]);
		}
		tcpServer(port);
	}
	else
	{
		char* ip = "127.0.0.1";
		if(argc == 3)
		{
			port = atoi(argv[2]);
		}
		else if(argc == 4)
		{
			ip = argv[2];
			port = atoi(argv[3]);
		}
		tcpClient(ip,port);
	}
	return 0;
}



