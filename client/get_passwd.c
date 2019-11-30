#include "func.h"

int get_passwd(int sfd)
{
    char passwd[64]={0};
    recv(sfd,passwd,34,0);
    char salt[16]={0};
    for(int i=0;i<11;i++)
    {
        salt[i]=passwd[i];
    }
    char* pass;
    pass=getpass("请输入密码：");
    char* p=crypt(pass,salt);
    if(strcmp(passwd,p)==0)
    {
        return 1;
    }
    return 0;
}

