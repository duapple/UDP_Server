/*
client.c
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
	int sockfd;
	struct sockaddr_in servaddr;
	char buf[BUF_SIZE] = {"hello Server\n"};
	
	if(argc < 3)
	{
		printf("Usage：%s <IP> <port>\n", argv[0]);	//提示执行程序是 传递的参数
		exit(-1);
	}
	
	/*建立socket*/
	
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(-1);
	}
	printf("listenfd = %d\n", sockfd);
	
	/*设置soscket_in结构体中相关参数*/
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));		//把字符串转换成整型数，然后转换成对应的网络字节序
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);	//sin_addr这个结构体中只有一个元素
	
	sendto(sockfd, buf, BUF_SIZE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    memset(buf, 0, sizeof(buf));
    if (buf[0] != '\0') {
        printf("the buf: %s", buf);
    }
	/*调用recv()函数接收客户端发送的数据*/
	if(recvfrom(sockfd, buf, BUF_SIZE, 0, NULL, NULL) == -1)
	{
		perror("recv");
		exit(-1);
	}
	printf("Receve a message from server: %s", buf);
	close(sockfd);
	exit(0);	
}