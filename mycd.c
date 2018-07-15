/*************************************************************************
	> File Name: mycd.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月28日 星期一 17时02分46秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define N 256
int mychdir(const char *p) {
    char path[100];
    char *start;
    char *end;
    int res;
    int n= 0;
    memset(path,'\0',100);
    start = strchr(p,' ');
    end = strchr(p,'\n');
    if(!start || !end) {
        printf("can't support this format \n");
        return 1;
    }
    strncpy(path,p+3,end-start-1); // get the path in inputting command
    res = chdir(path); //change dir
    if(res != 0)
        printf("%s is nod a path,please check again \n",path);
    return res;
}

int main(int argc, char *argv[]) {
    char buffer[N];
    int fd ;
    char a[100];
    while(1)
    {
        getcwd(a,100);
        printf("\033[1;32m""ygy@y--g--y\033[0m");
        printf(":");
        printf("\033[1;34m""%s\033[0m",a);
        printf("$ ");
        bzero(buffer, N);
        fgets(buffer, N, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        if(strncmp(buffer, "exit", 4) == 0) {
            printf("退出MY SHELL\n");
            break;
        } else if (strncmp(buffer, "cd", 2) == 0) {
            if(strncmp(buffer, "cd ~", 4) == 0) {
                chdir("/home/ygy");
            }
            if(strncmp(buffer, "cd -", 4) == 0) {
                chdir("/home/ygy");
            }
            if(strncmp(buffer, "cd .", 4) == 0) {
                chdir("/home/ygy");
            }
            if(strncmp(buffer, "cd", 2) == 0) {
                chdir("/home/ygy");
            } 
             if((fd = open(buffer + 3, O_RDONLY)) < 0) {
                //printf("打开失败!\n");
            }
            if(fchdir(fd) < 0) {
                //printf("cd命令错误!\n");
            }
        } else if(strncmp(buffer, "ls", 2) == 0) {
            if(system(buffer) < 0) {
                printf("ls命令错误！\n");
            }
        } else if(strncmp(buffer, "pwd", 3) == 0) {
            if(system(buffer) < 0) printf("pwd命令错误！");
        } else {
            printf("其他命令 ，没写\n");
        }
        close(fd);
    }
    return 0;
}
