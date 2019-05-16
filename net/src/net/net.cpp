/*
 * net.cpp
 * Copyright (C) 2019/05/13 LQ 
 *
 * Distributed under terms of the MIT license.
 */

#include "net.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <unistd.h>
#include <arpa/inet.h>

#define MAXSIZE 4096
void tcpServer(int port)
{
    printf("listen start, port: %d\n",port);
    /*
    初始化socket
    int  socket(int protofamily, int type, int protocol)
    protofamily：
        即协议域，又称为协议族（family）。
        常用的协议族有:AF_INET(IPV4)、AF_INET6(IPV6)、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等等。
        协议族决定了socket的地址类型，在通信中必须采用对应的地址，
        如AF_INET决定了要用ipv4地址（32位的）与端口号（16位的）的组合、
        AF_UNIX决定了要用一个绝对路径名作为地址。
    type：
        指定socket类型。
        常用的socket类型有:SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等。
    protocol：
        指定协议。
        常用的协议有:IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等.
        它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议
    */
    int socket_fd;
    if((socket_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("create socket error: %s. errno: %d\n",strerror(errno),errno);
        exit(0);
    }

    /*
    struct sockaddr_in {
        sa_family_t    sin_family;  address family: AF_INET 
        in_port_t      sin_port;    port in network byte order 
        struct in_addr sin_addr;    internet address 
    };

    Internet address. 
        struct in_addr {
        uint32_t       s_addr;      address in network byte order 
    };
    */
    //初始化
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//ip地址设置成INADDR_ANY，让系统自动获取本机ip
    servaddr.sin_port = htons(port);

    /*
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    函数的三个参数分别为：

    sockfd：即socket描述字，它是通过socket()函数创建了，唯一标识一个socket。bind()函数就是将给这个描述字绑定一个名字。
    addr：一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。
    addrlen：对应的是地址的长度。
    */
    if(bind(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
    {
        printf("blind error: %s, errno: %d\n",strerror(errno),errno);
        exit(0);
    }

    /*
    int listen(int sockfd, int backlog);
    listen函数的第一个参数即为要监听的socket描述字，
    第二个参数为相应socket可以排队的最大连接个数。
    socket()函数创建的socket默认是一个主动类型的，listen函数将socket变为被动类型的，等待客户的连接请求。
    */
    if(listen(socket_fd,10) == -1)
    {
        printf("listen error: %s, errno: %d\n",strerror(errno),errno);
        exit(0);
    }
    /*
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); //返回连接connect_fd
        sockfd:
            监听套接字，这个套接字用来监听一个端口，
            当有一个客户与服务器连接时，它使用这个一个端口号，而此时这个端口号正与这个套接字关联。
            客户不知道套接字这些细节，它只知道一个地址和一个端口号。
        addr:
            这是一个结果参数，它用来接受一个返回值，这返回值指定客户端的地址，
            这个地址是通过某个地址结构来描述的，用户应该知道这一个什么样的地址结构。
            如果对客户的地址不感兴趣，那么可以把这个值设置为NULL。
        len:
            结果的参数，用来接受上述addr的结构的大小的，它指明addr结构所占有的字节个数。
            同样的，它也可以被设置为NULL。
    */
   
   
    int connect_fd,n;
    struct sockaddr_in client_addr;
    socklen_t client_addr_length = sizeof(client_addr);
    if((connect_fd = accept(socket_fd,(sockaddr*)&client_addr,&client_addr_length)) == -1)
    {
        printf("accept error: %s, errno: %d\n",strerror(errno),errno);
            exit(0);
    }

    char strIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET,&client_addr.sin_addr,strIp,INET_ADDRSTRLEN);
    printf("recive socket from ip:%s,port:%d\n",
        strIp,  //inet_ntoa(ip)讲数字的ip地址转为字符串
        ntohs(client_addr.sin_port));
 
    char buff[MAXSIZE];
    char sendbuff[MAXSIZE];
    memset(sendbuff,0,sizeof(sendbuff));
    while(1)
    {
        n = read(connect_fd,buff,MAXSIZE);
        if(n > 0)
        {
            //buff[n] = '\n';
            printf("recv: %s",buff);
            fgets(sendbuff,MAXSIZE,stdin);
            write(connect_fd,sendbuff,strlen(sendbuff));
            printf("send: %s",sendbuff);
        }
        else if(n == 0)
        {
            printf("client break\n");
            break;
        }
        else
        {
            printf("recive error\n");
            break;
        }
    }
    close(connect_fd);
    close(socket_fd);
}
void tcpClient(const char* ip,int port)
{
    printf("connect to %s:%d\n",ip,port);
    int socket_fd;
    if((socket_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        printf("creat socket error: %s,errno: %d",strerror(errno),errno);
        exit(0);
    }

    struct sockaddr_in sockaddr;
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    if(inet_pton(AF_INET,ip,&sockaddr.sin_addr) <= 0)
    {
        printf("inet_pton error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0); 
    }

    if(connect(socket_fd,(struct sockaddr*)&sockaddr,sizeof(sockaddr)) < 0)
    {
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);
    }
    char sendbuff[MAXSIZE];
    memset(sendbuff,0,MAXSIZE);
    char recvbuff[MAXSIZE];
    memset(recvbuff,0,MAXSIZE);
    int n;
    while(1)
    {
        fgets(sendbuff,MAXSIZE,stdin);
        if(sendbuff == "quit")
        {
            break;
        }
        
        printf("send: %s",sendbuff);
        if(write(socket_fd,sendbuff,strlen(sendbuff)) < 0)
        {
            printf("sendmsg error: %s(errno: %d)\n",strerror(errno),errno);  
            exit(1);
        }
        n = read(socket_fd,recvbuff,MAXSIZE);
        if(n == -1)
        {
            printf("sendmsg error: %s(errno: %d)\n",strerror(errno),errno);  
            exit(1);
        }
        else if(0 == n)
        {
            printf("server stop.\n");
            break;
        }
        printf("recv: %s",recvbuff);
    }
    close(socket_fd);

    return;

}
