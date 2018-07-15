/*************************************************************************
	> File Name: mljx.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月23日 星期三 08时11分33秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<libgen.h>
#include<unistd.h>
#define BLUE 
#define GREEN 

char *optarg;
int optind;
int optopt; //最后一个已知选项
int opterr = 1;
int ans1 =0;
int ans2 =0;


//文件名
void lsfile(char *);
char getFileType(struct stat *);
void getFilePerm(struct stat *, char *);

void func(char *path){
    DIR *dir;
    dir = opendir(path);
    char str[100];
    struct dirent *p;
    while((p = readdir(dir))){
        char *fname;
        fname = p->d_name;
        sprintf(str,"%s/%s",path,fname);
        lsfile(str);
        if( ans1 == 1) printf("\033[1;32m""%s\n\033[0m", p->d_name);
        else if( ans2 == 1) printf("\033[1;34m""%s\n\033[0m", p->d_name);
        else printf("%s\n", p->d_name);
        ans1=ans2=0;
    }
    closedir(dir);
}
void func3(char *path){
    DIR *dir;
    dir = opendir(path);
    char str[100];
    struct dirent *p;
    while((p = readdir(dir))){
        strcpy(str, p->d_name);
        if(str[0] == '.') continue;
        char *fname;
        fname = p->d_name;
        sprintf(str,"%s/%s",path,fname);
        lsfile(str);
        if( ans1 == 1) printf("\033[1;32m""%s\n\033[0m", p->d_name);
        else if( ans2 == 1) printf("\033[1;34m""%s\n\033[0m", p->d_name);
        else printf("%s\n", p->d_name);
        ans1=ans2=0;
    }
    closedir(dir);
}
void func1(char *path){
        DIR *dir;
        dir = opendir(path);
    int i = 0;
        char str[100];
        struct dirent *p;
        while((p = readdir(dir))){           
            strcpy(str, p->d_name);
            if(!str)
                continue;
            printf("%-12s", str);
            i++;
        if(i % 6 == 0) printf("\n");
        }
        closedir(dir);
}
void func2(char *path){
    DIR *dir;
    dir = opendir(path);
    int i = 0;
    char str[100];
    struct dirent *p;
    while((p = readdir(dir))){
        strcpy(str, p->d_name);
        if(str[0] == '.') continue;
        if(!str) continue;
        printf("%-12s", str);
        i++;
    if(i % 6 == 0) printf("\n");
    }
    closedir(dir);
}
//获得文件类型
char getFileType(struct stat *st)
{
    char type = '-';
    switch (st->st_mode  & S_IFMT)
    {
        case S_IFSOCK: type = 's'; break;
        case S_IFLNK: type = 'l'; break;
        case S_IFREG: type = '-'; break;
        case S_IFBLK: type = 'b'; break;
        case S_IFDIR: type = 'd'; break;
        case S_IFCHR: type = 'c'; break;
        case S_IFIFO: type = 'p'; break;
    }
    return type;
}

//获得文件访问权限
void getFilePerm(struct stat *st, char *qx)
{
    mode_t mode = st->st_mode;
    if (mode & S_IRUSR) qx[1] = 'r';
    if (mode & S_IWUSR) qx[2] = 'w';
    if (mode & S_IXUSR) qx[3] = 'x';
    if (mode & S_IRGRP) qx[4] = 'r';
    if (mode & S_IWGRP) qx[5] = 'w';
    if (mode & S_IXGRP) qx[6] = 'x';
    if (mode & S_IROTH) qx[7] = 'r';
    if (mode & S_IWOTH) qx[8] = 'w';
    if (mode & S_IXOTH) qx[9] = 'x';
}

void lsfile(char *filename)
{
    struct stat q;
    stat(filename, &q);
    char buf[11];
    strcpy(buf,"----------");
    char type;
    type = getFileType(&q);
    buf[0] = type;
    getFilePerm(&q,buf);
    if(buf[0] == '-' && buf[9] == 'x') ans1 = 1;
    if(buf[0] == 'd' && buf[9] == 'x') ans2 = 1;
    struct passwd *p;
    struct group *gp;
    p = getpwuid(q.st_uid);
    gp = getgrgid(q.st_gid);    
    printf("%s ", buf);
    printf("%-4ld ", q.st_nlink);
    printf("%s ", p->pw_name);
    printf("%s ", gp->gr_name);
    printf("%-9ld %.12s ", (long)q.st_size, 4 + ctime(&q.st_mtime));
}


int main(int argc,char *argv[]) {
    int c;
    if(argc > 1) {
        while((c = getopt(argc, argv, "l::a::")) != -1) {
            switch(c) {
                case 'a':{
                    if(argv[optind]  == NULL) {
                        func1(".");
                        printf("3");
                    } else if(optarg[0] == 'l')
                       {func(argv[optind]);
                        printf("1");}
                    else{
                       // for(int i = optind; i < argc; i++)
                        func1(argv[optind]);
                        printf("2");
                    }
                }                
                    break;
                case 'l':{
                    if(argv[optind] == NULL) {
                        func3(".");
                    } else {
                        func(argv[optind]);
                    }
                }
            }
        }
    } else func2(".");
    printf("\n");
    return 0;

}
