/*************************************************************************
	> File Name: lsal.c
	> Author: 
	> Mail: 
	> Created Time: 2018年05月19日 星期六 17时41分11秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<libgen.h>
#define BLUE 
#define GREEN 
//文件名
void lsfile(char *);
char getFileType(struct stat *);
void getFilePerm(struct stat *, char *);

void func(char *path){
    DIR *dir;
    dir = opendir(path);
    char str[100];
   // char a[1];
   // a[0] = getFileType(&fname);
    struct dirent *p;
    while((p = readdir(dir))){
        char *fname;
        fname = p->d_name;
        sprintf(str,"%s/%s",path,fname);
        lsfile(str);
        //int ans;
        //if( ans == 3) printf("%S\n", p->d_name);
        //else {
            printf("%s\n", p->d_name);
        //}
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
     
    //char *bname = basename(filename);
    buf[0] = type;
    
    getFilePerm(&q,buf);
    //struct tm *ftime;
    int ans = 0;

    //ftime = localtime(&q.st_mtime);
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
    if(argc == 1) func(".");
    else {
        for(int i = 1; i < argc; i++) {
            func(argv[i]);
        }
    }
    printf("\n");
    return 0;

}
