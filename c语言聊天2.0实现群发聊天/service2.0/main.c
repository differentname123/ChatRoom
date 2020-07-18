#include <winsock2.h>
#include <stdio.h>
#include <process.h>          // for _beginthread()
#define BUFF 1024
int Port=6666,ret;
char sendbuff[BUFF];
char recvbuff[BUFF];
struct infor
{
    SOCKET client;
    char name[1024];
};
struct infor info[100];
SOCKET c;
struct sockaddr_in serveadd;
int i=0;
void thread_send()
{
    int j;
    while(1)
    while(i)
    {
        {
            scanf("%s",sendbuff);
            if(strcmp(sendbuff,"quit") == 0)   //退出
                return 0;
                //printf("\n用户2:");
            for(j=0;j<i;j++)
            {
                send((info+j)->client,"服务器",BUFF,0);
                send((info+j)->client,":",BUFF,0);
                if(send((info+j)->client,sendbuff,BUFF,0) == SOCKET_ERROR)
                {
                    printf("消息发送失败!\n");
                    break;
                }
            }

    }
}
}
/*void thread_listen(SOCKET *arry)
{

    serveadd.sin_port=htons(Port);
    serveadd.sin_family=AF_INET;
    serveadd.sin_addr.s_addr = inet_addr("0.0.0.0");
    bind(c,(struct sockaddr*)(&serveadd),sizeof(serveadd));
    listen(c,5);
    printf("等待连接...");
    *(arry+i)=accept(c,(struct sockaddr*)(&serveadd),&serveadd);
    i++;
}*/
void thread_recv(int k)
{
    int j,flag;
    flag=k;
    while(1)
    {

           ret=recv((info+flag)->client,recvbuff,BUFF,0);
           //printf("client1 %d",newc.client);
            if(ret>0)
            {
                printf("%s:%s\n",(info+flag)->name,recvbuff);
                 for(j=0;j<i;j++)
                 {
                     if(j!=k)
                     {
                          send((info+j)->client,(info+flag)->name,BUFF,0);
                         send((info+j)->client,":",BUFF,0);
                        if(send((info+j)->client,recvbuff,BUFF,0) == SOCKET_ERROR)
                        {
                            printf("消息发送失败!\n");
                            break;
                        }
                     }


                }
            }
            else if(ret < 0)
            {
                printf("接收错误%d\n",SOCKET_ERROR);
                closesocket((info+flag)->client);
                WSACleanup();
                return -1;
            }
    }
}
void main()
{

    int j=0;
    SOCKET newc;
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    c=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    _beginthreadex(NULL,0,&thread_send,0,NULL,0);

    while(1)
    {
        serveadd.sin_port=htons(Port);
        serveadd.sin_family=AF_INET;
        serveadd.sin_addr.s_addr = inet_addr("0.0.0.0");//它告知内核去选择IP地址,也可以把一个特定的IP地址绑定到它的套接字上，不过这个IP地址必须属于它所在主机的网络接口之一
        bind(c,(struct sockaddr*)(&serveadd),sizeof(serveadd));
        listen(c,5);
        //printf("等待连接...");
        newc=accept(c,(struct sockaddr*)(&serveadd),&serveadd);
        if(newc==-1)
        {
            return -1;
        }
        printf("连接成功\n");
        ret=recv(newc,recvbuff,BUFF, 0);
            if(ret > 0)
            printf("%s:上线了\n",recvbuff);
        (info+i)->client=newc;
        strcpy((info+i)->name,recvbuff);
        //printf("client %d",newc);
        _beginthreadex(NULL,0,&thread_recv,i,NULL,0);
        i++;
    }
   /* while(1)
    {

        scanf("%s",sendbuff);
        if(strcmp(sendbuff,"quit") == 0)   //退出
            break;
        //printf("\n用户2:");
        for(j=0;j<i;j++)
        if(send(newc,sendbuff,BUFF,0) == SOCKET_ERROR)
        {
            printf("消息发送失败!\n");
            break;
        }
    }*/
    shutdown(newc, SD_BOTH);
    closesocket(c);
    closesocket(newc);
    WSACleanup();
}
//差多台电脑测试了
