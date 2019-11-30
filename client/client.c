#include "func.h"

int main()
{
    int sfd;
    int ret;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser;
    ser.sin_family=AF_INET;
    ser.sin_addr.s_addr=inet_addr("192.168.3.101");
    ser.sin_port=htons(2000);
    connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
    printf("connect success\n");
    while(1)
    {
        int flag,len;
        char name[10]={0};
        salt_t a;
        printf("1.登陆\n2.注册\n");
        scanf("%d",&flag);
        switch(flag)
        {
        case 1:
            {
                send(sfd,&flag,4,0);
                printf("请输入用户名：");
                scanf("%s",name);
                len=strlen(name);
                send(sfd,&len,4,0);
                send(sfd,name,len,0);
                recv(sfd,&len,4,0);
                if(len==0)
                {
                    printf("没有该用户名，请重试\n");
                    break;
                }
                ret=get_passwd(sfd);//
                if(ret==1)
                {
                    send(sfd,&ret,4,0);
                    printf("登陆成功!\n");
                    break;
                }
                int b=0;
                send(sfd,&b,4,0);
                printf("密码错误，请重试!\n");
                break;
            }
        case 2:
            {
                send(sfd,&flag,4,0);
                printf("请输入用户名：");
                scanf("%s",name);
                get_salt(&a);
                len=strlen(name);
                send(sfd,&len,4,0);
                send(sfd,name,len,0);
                len=strlen(a.passwd);
                send(sfd,&len,4,0);
                send(sfd,a.passwd,len,0);
                for(int i=0;i<11;i++)
                {
                    a.salt[i]=a.passwd[i];
                }
                len=strlen(a.salt);
                send(sfd,&len,4,0);
                send(sfd,a.salt,len,0);
                int d;
                recv(sfd,&d,4,0);
                if(d==1)
                {
                    printf("注册成功！\n");
                }
                else
                {
                    printf("该用户名已存在\n");
                }
                break;
            }
        default:continue;
        }
        if(ret==1)
        {
            getchar();
            break;
        }
    }
    char buf[1024];
    bzero(buf,sizeof(buf));
    ret=recv(sfd,buf,sizeof(buf),0);//1
    printf("Current path:%s\n",buf);
    int i,j;
    while(1)
    {
        char buf_m[20]={0};
        fgets(buf_m,20,stdin);
        i=strlen(buf_m);
        buf_m[i-1]='\0';
        send(sfd,buf_m,20,0);//2
        char tmp[10]={0};
        char tmp_h[20]={0};
        i=0,j=0;
        while(buf_m[i]!=' '&&buf_m[i]!='\0')
        {
            tmp[i]=buf_m[i];
            i++;
        }
        i++;
        while(buf_m[i]!=' '&&buf_m[i]!='\0')
        {
            tmp_h[j]=buf_m[i];
            i++;
            j++;
        }
        if(strcmp(tmp,"cd")==0)
        {
            int c;
            recv(sfd,&c,4,0);
            if(c==1)
            {
                bzero(buf,sizeof(buf));
                ret=recv(sfd,buf,sizeof(buf),0);
                printf("Current path:%s\n",buf);  
            }
            else
            {
                printf("没有权限\n");
            }
        }
        else if(strcmp(tmp,"ls")==0)
        {
            bzero(buf,sizeof(buf));
            ret=recv(sfd,buf,sizeof(buf),0);//3
            printf("%s\n",buf);  
        }
        else if(strcmp(tmp,"remove")==0)
        {
            printf("remove success\n");
        }
        else if(strcmp(tmp,"gets")==0)
        {
            get_file(sfd,tmp_h);
        }
        else if(strcmp(tmp,"pwd")==0)
        {
            bzero(buf,sizeof(buf));
            ret=recv(sfd,buf,sizeof(buf),0);
            printf("%s\n",buf);
        }
        else if(strcmp(tmp,"puts")==0)
        {
            send_file(sfd,tmp_h);
        }
        else
        {
            printf("error\n");
        }

    }
    return 0;
}
