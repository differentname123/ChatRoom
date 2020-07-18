#include <winsock2.h>
#include <stdio.h>
#define BUFF 1024
int Port=6666,f;
char IP[13];
int flag=0;
char sendbuff[1024];
char recvbuff[1024];
SOCKET c,ret;
int thread_send(SOCKET c)
{
    while(1)
    {

        scanf("%s",sendbuff);
        if(strcmp(sendbuff, "quit") == 0)   //quit
        break;
        //printf("\n用户1:");
        f=send(c,sendbuff,BUFF,0);
        if(-1==f)
        {
            printf("发送失败\n");
            closesocket(c);
            WSACleanup();
            return -1;
        }
    }


}

int thread_recive(SOCKET c)
{
            ret = recv(c,recvbuff, BUFF, 0);
            if(ret>0)
            {
                if(flag<2)
                {
                   printf("%s",recvbuff);
                }
                else
                printf("%s\n",recvbuff);
                flag++;
                flag=flag%3;

            }

            else
            {
                printf("接受失败\n");
                closesocket(c);
                WSACleanup();
                return -1;

            }


}
void main()
{

    struct sockaddr_in serveadd;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);//将相关链接库（Ws2_32.lib）加入链接，并使用WSAStartUp函数初始化。以便后面能够成功调用socket相关函数
    c=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);// 建立一个socket用于连接
    serveadd.sin_port=htons(Port);
    serveadd.sin_family=AF_INET;
    printf("输入要访问的IP地址\n");
    scanf("%s",IP);
    serveadd.sin_addr.s_addr = inet_addr(IP);
    printf("输入你的昵称\n");
    scanf("%s",sendbuff);
    if(connect(c, (SOCKADDR*)&serveadd, sizeof(serveadd))==-1)
    {
        printf("连接失败");
        return -1;
    }
    send(c,sendbuff,BUFF,0);
    _beginthreadex(NULL,0,&thread_send,c,NULL,0);//开启发送线程
    _beginthreadex(NULL,0,&thread_recive,c,NULL,0);//开启接受线程
    while(1)
        {

        }
    shutdown(c, SD_BOTH);
    closesocket(c);
    WSACleanup();
}
