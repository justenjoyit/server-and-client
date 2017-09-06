#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>

int main()
{
	int serverfd;
	struct sockaddr_in serveraddr;

	//创建套接字
	if((serverfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		std::cout<<"socket error"<<std::endl;
		exit(-1);
	}

	//写入协议族，端口，地址
	memset((void*)&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(4000);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	//建立连接
	if(connect(serverfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0)
	{
		std::cout<<"connect error"<<std::endl;
		exit(-1);
	}

	int n;
	char buf[1024];

	while((n=read(serverfd,buf,1024))>0)
	{
		buf[n]='\0';
		std::cout<<buf;
	}

	if(n<0)
	{
		std::cout<<"read error"<<std::endl;
		exit(-1);
	}
	
	return 0;
}

