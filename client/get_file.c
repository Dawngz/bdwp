#include "func.h"

int recvcycle(int sfd,void* p,int datalen)
{
    int ret;
    off_t total=0;
    char* pstart=(char*)p;
    while(total<datalen)
    {
        ret=recv(sfd,pstart+total,datalen-total,0);
        if(ret==-1)
        {
            return -1;
        }
        total+=ret;
    }
    return 0;
}
int get_file(int sfd,char* p)
{
    int fd,ret;
    char buf[1000];
    fd=open(p,O_CREAT|O_RDWR,0600);
    struct stat buf_l;
    fstat(fd,&buf_l);
    printf("size=%ld\n",buf_l.st_size);
    lseek(fd,buf_l.st_size,SEEK_SET);
    send(sfd,&buf_l.st_size,4,0);
    off_t filesize=0,downsize=buf_l.st_size,datalen=0;
    ret=recv(sfd,&filesize,4,0);//接收文件大小
    while(1)
    {
        ret=recv(sfd,&datalen,4,0);
        if(datalen>0)
        {
            ret=recvcycle(sfd,buf,datalen);
            write(fd,buf,datalen);
            downsize+=datalen;
            if(downsize<filesize)
            {
                printf("\r%5.2f%%",(float)downsize/filesize*100);
                fflush(stdout);
            }
        }
        else
        {
            printf("\r100%%   \n");
            break;
        }
    }
    close(fd);
    return 0;
}
