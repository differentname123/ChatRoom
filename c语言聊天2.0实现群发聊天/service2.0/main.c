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
            if(strcmp(sendbuff,"quit") == 0)   //�˳�
                return 0;
                //printf("\n�û�2:");
            for(j=0;j<i;j++)
            {
                send((info+j)->client,"������",BUFF,0);
                send((info+j)->client,":",BUFF,0);
                if(send((info+j)->client,sendbuff,BUFF,0) == SOCKET_ERROR)
                {
                    printf("��Ϣ����ʧ��!\n");
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
    printf("�ȴ�����...");
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
                            printf("��Ϣ����ʧ��!\n");
                            break;
                        }
                     }


                }
            }
            else if(ret < 0)
            {
                printf("���մ���%d\n",SOCKET_ERROR);
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
        serveadd.sin_addr.s_addr = inet_addr("0.0.0.0");//����֪�ں�ȥѡ��IP��ַ,Ҳ���԰�һ���ض���IP��ַ�󶨵������׽����ϣ��������IP��ַ������������������������ӿ�֮һ
        bind(c,(struct sockaddr*)(&serveadd),sizeof(serveadd));
        listen(c,5);
        //printf("�ȴ�����...");
        newc=accept(c,(struct sockaddr*)(&serveadd),&serveadd);
        if(newc==-1)
        {
            return -1;
        }
        printf("���ӳɹ�\n");
        ret=recv(newc,recvbuff,BUFF, 0);
            if(ret > 0)
            printf("%s:������\n",recvbuff);
        (info+i)->client=newc;
        strcpy((info+i)->name,recvbuff);
        //printf("client %d",newc);
        _beginthreadex(NULL,0,&thread_recv,i,NULL,0);
        i++;
    }
   /* while(1)
    {

        scanf("%s",sendbuff);
        if(strcmp(sendbuff,"quit") == 0)   //�˳�
            break;
        //printf("\n�û�2:");
        for(j=0;j<i;j++)
        if(send(newc,sendbuff,BUFF,0) == SOCKET_ERROR)
        {
            printf("��Ϣ����ʧ��!\n");
            break;
        }
    }*/
    shutdown(newc, SD_BOTH);
    closesocket(c);
    closesocket(newc);
    WSACleanup();
}
//���̨���Բ�����
