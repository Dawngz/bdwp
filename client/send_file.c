#include "func.h"

typedef struct {
    int datalen;
    char buf[1000];
}train_t;
int send_file(int new_fd,char* p)
{
    int fd,ret;
    off_t offset=0;
    recv(new_fd,&offset,4,0);
    fd=open(p,O_RDWR);
    struct stat buf;
    fstat(fd,&buf);
    ret=send(new_fd,&buf.st_size,4,0);//发送文件大小
    train_t train;
    lseek(fd,offset,SEEK_SET);
    off_t sendlen=offset;
    if(buf.st_size<1024*1024*100)
    {
        while((train.datalen=read(fd,train.buf,sizeof(train.buf))))
        {
            sendlen+=train.datalen;
            ret=send(new_fd,&train,4+train.datalen,0);//发送文件
            if(ret==-1)
            {
                return 0;
            }
            if(sendlen<buf.st_size)
            {
                printf("\r%5.2f%%",(float)sendlen/buf.st_size*100);
                fflush(stdout);
            }
        }
        send(new_fd,&train,4+train.datalen,0);
        printf("\r100%%   \n");
    }
    else
    {
        char* q=(char*)mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
        sendlen=offset;
        while(sendlen+1000<buf.st_size)
        {
            memcpy(train.buf,q+sendlen,sizeof(train.buf));
            train.datalen=1000;
            send(new_fd,&train,4+train.datalen,0);
            sendlen+=train.datalen;
            if(sendlen<buf.st_size)
            {
                printf("\r%5.2f%%",(float)sendlen/buf.st_size*100);
                fflush(stdout);
            }
        }
        train.datalen=buf.st_size-sendlen;
        memcpy(train.buf,q+sendlen,train.datalen);
        send(new_fd,&train,4+train.datalen,0);
        train.datalen=0;
        bzero(train.buf,sizeof(train.buf));
        send(new_fd,&train,4,0);
        printf("\r100%%   \n");
    }
    return 0;
}

