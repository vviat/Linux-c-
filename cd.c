/*************************************************************************
	> File Name: cd.c
	> Author: 
	> Mail: 
	> Created Time: 2018年06月03日 星期日 00时34分48秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define N 256

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
            if((fd = open(buffer + 3, O_RDONLY)) < 0) {
                printf("打开失败!\n");
            }
            if(fchdir(fd) < 0) {
                printf("cd命令错误!\n");
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

