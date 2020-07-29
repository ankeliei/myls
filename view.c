#include "mysl.h"

void file_type(const struct stat * get_message) {
    mode_t mode =  (*get_message).st_mode;
    if(S_ISREG(mode))
        printf("-");/*普通文件*/
    else if(S_ISDIR(mode))
        printf("d");/*目录文件*/
    else if(S_ISCHR(mode))
        printf("c");/*字符设备文件*/
    else if(S_ISBLK(mode))
        printf("b");/*块设备文件*/
    else if(S_ISFIFO(mode))
        printf("p");/*管道文件*/
    else if(S_ISLNK(mode))
        printf("l");/*链接文件*/
    else if(S_ISSOCK(mode))
        printf("s");/*socket文件*/
}

void file_power_char(mode_t mode,mode_t type,const char ch)
    {
        if((mode & type) == type)
            printf("%c",ch);
        else
            printf("-");
    }

void file_power(const struct stat * get_message) {
    
    mode_t mode = (*get_message).st_mode & 07777;/*取后四位*/

    file_power_char(mode,S_IRUSR,'r');/*判断user有无读权限*/
    file_power_char(mode,S_IWUSR,'w');/*判断user有无写权限*/
    file_power_char(mode,S_IXUSR,'x');/*判断user有无可执行权限*/

    file_power_char(mode,S_IRGRP,'r');/*判断group有无读权限*/
    file_power_char(mode,S_IWGRP,'w');/*判断group有无写权限*/
    file_power_char(mode,S_IXGRP,'x');/*判断group有无可执行权限*/

    file_power_char(mode,S_IROTH,'r');/*判断other有无读权限*/
    file_power_char(mode,S_IWOTH,'w');/*判断other有无写权限*/
    file_power_char(mode,S_IXOTH,'x');/*判断other有无可执行权限*/

    printf(" ");
}

void file_user_group(const struct stat * get_message) {
    struct passwd * pwd;
    struct group * grp;
    pwd = getpwuid(get_message->st_uid);
    grp = getgrgid(get_message->st_gid);
    printf("%10s\t%-10s\t",pwd->pw_name, grp->gr_name);
}

void file_time(const struct stat * get_message) {

    struct tm * chtime = localtime(&(get_message->st_mtime));
    if(chtime == NULL) {
        printf("localtime is error!");
        exit(EXIT_FAILURE);
    }
    else {
        printf("%4d/%02d/%02d_%02d:%02d:%02d  ", chtime->tm_year+1900, chtime->tm_mon+1,chtime->tm_mday, chtime->tm_hour, chtime->tm_min, chtime->tm_sec);
    }
}

void file_size(const struct stat * get_message) {

    long int size = get_message->st_size;
    if ( size < 1024) {
        printf("%7.2f B   ", (float)size);
    }
    if( 1024 <= size && size < 1048576){
        printf("%7.2f KB  ",size/(float)1024);
    }
    if( 1048576 <= size && size < 1073741824) {
        printf("%7.2f MB  ",size/( (float) 1024*1024  ) );
    }
    if( 1073741824 <= size) {
        printf("%7.2f GB  ",size/((float)1024*1024*1024));
    }
}

void file_name(const struct stat * get_message, const char * filename, char * r_head) {
    mode_t mode =  (*get_message).st_mode;
    if(S_ISREG(mode)) {
        mode_t mode = (*get_message).st_mode & 07777;/*取后四位*/
        if((mode & S_IXUSR) == S_IXUSR){
            printf("%s",r_head);
            PRINT_GREEN(filename)
        }
        else
            printf("%s%s",r_head,filename);/*普通文件*/
    }
    else if(S_ISDIR(mode)){
        printf("%s",r_head);
        PRINT_BULE(filename)       //目录 蓝色
    }
    else if(S_ISCHR(mode)){
        printf("%s",r_head);
        PRINT_PURPLE(filename)     //字符设备 紫色
    }
    else if(S_ISBLK(mode)){
        printf("%s",r_head);
        PRINT_RED(filename)            //块设备 红色
    }
    else if(S_ISFIFO(mode)){
        printf("%s",r_head);
        PRINT_YELLOW(filename)     //管道文件 黄色
    }
    else if(S_ISLNK(mode)){
        printf("%s",r_head);
        PRINT_CYAN(filename)           //链接文件 青色
    }
    else if(S_ISSOCK(mode)){
        printf("%s",r_head);
        PRINT_WHITE(filename)          //套接字 白色
    }
    else 
        printf("%s%s", r_head, filename);
}

void list_message(const char * filename, const struct stat * get_message, int view_mod, char * r_head)   //stat显示函数
{
    if(view_mod) {
        file_type(get_message);
        file_power(get_message);
        printf("%4d  ",get_message->st_nlink);
        file_user_group(get_message);
        file_size(get_message);
        file_time(get_message);
        file_name(get_message, filename, r_head);
        //printf("\t%s ",r_head);
        printf("\n");
    }
    else {
        //printf("%s ",r_head);
        file_name(get_message, filename, r_head);
        printf("\n");
    }
}
