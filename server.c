
/*
server.c
*/
 
#include <stdio.h>
#include <strings.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
 
#define BUF_SIZE 128
 
int main(int argc, char *argv[])
{
	int sockfd, connfd, ret;
	struct sockaddr_in servaddr, cliaddr;
	char buf[BUF_SIZE] = {0};
	socklen_t peerlen;
	
	if(argc < 3)
	{
		printf("Usage：%s <IP> <port>\n", argv[0]);	//提示输入
		exit(-1);
	}
	
	/*建立socket连接*/
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(-1);
	}
	printf("sockfd = %d\n", sockfd);
	
	/*设置soscket_in结构体中相关参数*/
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));		//把字符串转换成整型数，然后转换成对应的网络字节序
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);	//sin_addr这个结构体中只有一个元素
	
	/*绑定函数bind()，将socket描述符与本地的Ip与端口绑定*/
	if((ret = bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) == -1)
	{
		perror("bind");
		exit(-1);
	}
	printf("bind success\n");
	
	/*调用accept()函数，等待客户端的连接*/
	peerlen = sizeof(cliaddr);
	while(1)
	{
		/*调用recv()函数接收客户端发送的数据*/
		memset(buf, 0, sizeof(buf));
		
		printf("get in while \n");
		if(recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)&cliaddr, &peerlen) == -1)
		{
			perror("recv");
			exit(-1);
		}
		printf("Receve a message from client: %s", buf);
		memset(buf, 0, sizeof(buf));
		strcpy(buf, "welcome to client\n");
		sendto(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)&cliaddr, peerlen);
	}
	
	close(sockfd);
	exit(0);	
}

