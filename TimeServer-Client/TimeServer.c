#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int serverfd;
	struct sockaddr_in servaddr;

	//创建套接字
	if((serverfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		std::cout<<"socket error"<<std::endl;
		exit(-1);
	}

	//写入协议族，端口和地址
	memset((void*)&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(4000);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	//绑定
	if(bind(serverfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		std::cout<<"bind error"<<std::endl;
		exit(-1);
	}

	//监听
	if(listen(serverfd,10)<0)
	{
		std::cout<<"listen error"<<std::endl;
		exit(-1);
	}

	//accept接受
	int connfd;
	time_t ticks;
	char buf[1024];
	int size;
	
	std::cout<<"server start..."<<std::endl;

	while(1)
	{
		size=sizeof(servaddr);
		if((connfd=accept(serverfd,(struct sockaddr*)&servaddr,(socklen_t*)&size))<0)
		{
			std::cout<<"accept error"<<std::endl;
			exit(-1);
		}
		
		ticks=time(NULL);
		
		snprintf(buf,sizeof(buf),"%.24s\r\n",ctime(&ticks));
		write(connfd,buf,strlen(buf));
		
		std::cout<<"from "<<inet_ntoa(servaddr.sin_addr)<<" time "<<buf;

		close(connfd);
	}

	return 0;
}




