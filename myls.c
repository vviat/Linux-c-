/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月19日 星期六 08时22分59秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<string.h>
void func(char *path){
        DIR *dir;
        dir = opendir(path);
        char str[100];
        struct dirent *p;
        while((p = readdir(dir))){
            strcpy(str, p->d_name);
            if(!str)
                continue;
            printf("%s  ", str);
        }
        printf("\n");
        closedir(dir);
}
int main(int argc,char *argv[]) {
    if(argc == 1) {
        func(".");
    } else {
        for(int i = 1; i < argc; ++i) {
            func(argv[i]);
        }
    }
    printf("\n");
    return 0;

}
