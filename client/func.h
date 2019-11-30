#include <aio.h>
#include <assert.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/select.h>
#include <syslog.h> 
#include <sys/mman.h>
#define ARGC_CHECK(argc,val) {if(argc!=val) \
    {printf("error argc\n");return -1;}}
#define ERROR_CHECK(ret,retval,funcName){if(ret==retval)\
    {printf("%d:",__LINE__);perror(funcName);return -1;}}
#define THREAD_ERROC_CHECK(ret,funcName){if(ret!=0)\
    {printf("%d:",__LINE__);printf("%s:%s\n",funcName,strerror(ret));return -1;}}
#define N 5
#define STR_LEN 8
typedef struct {
    char* passwd;
    char* salt;
}salt_t;
int send_file(int,char*);
int get_file(int,char*);
int get_salt(salt_t*);
int get_passwd(int);
