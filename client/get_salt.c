#include "func.h"

int get_salt(salt_t* a)
{
    char str[STR_LEN + 1] = {0};
    int i,flag;
    srand(time(NULL));//通过时间函数设置随机数种子，使得每次运行结果随机。
    for(i = 0; i < STR_LEN; i ++)
    {
        flag = rand()%3;
        switch(flag)
        {
        case 0:
            str[i] = rand()%26 + 'a'; 
            break;
        case 1:
            str[i] = rand()%26 + 'A'; 
            break;
        case 2:
            str[i] = rand()%10 + '0'; 
            break;
        }
    }
    char* passwd;
    char* salt;
    char q[]="$1$";
    salt=strcat(q,str);
    passwd=getpass("请输入密码：");
    char* p=crypt(passwd,salt);
    a->passwd=p;
    a->salt=salt;
    return 0;
}

