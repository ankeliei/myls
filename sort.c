#include "myls.h"
#include "view.c"
int view(char *str, int sort_mod, int r, int show_hidden , int view_mod) {      //接收main传来的参数，选择不同的排序方式
    if(sort_mod == 0)
        view0(str, r, show_hidden, view_mod, "");
    if(sort_mod == 1)
        view1(str, r, show_hidden, view_mod, "");
    if(sort_mod == 2)
        view2(str, r, show_hidden, view_mod, "");
}

int view0(char *str, int r, int show_hidden, int view_mod, char * r_head) {     //进行文件名排序输出
    DIR * dir;
    struct dirent *ptr;

    if((dir=opendir(str)) == NULL) //打开文件流指针
    {
        fprintf(stderr,"cannot open directory:%s\n",str);
        return -1;
    }

    int n = 0;

    while( (ptr = readdir(dir)) !=NULL ){
        if(strcmp(ptr->d_name, ".") && strcmp(ptr->d_name, "..")) {
            n = n + 1;
        }
    }
    closedir(dir);
    struct dirent tmp[n], t;

    n = 0;
    dir=opendir(str);
    while((ptr = readdir(dir)) != NULL)     //遍历出ptr存储在tmp[]中，不包括.和..文件
    {
        char *filename = ptr->d_name;
        if(strcmp(filename, ".") && strcmp(filename, "..")) {
            memcpy(&tmp[n], ptr, sizeof(tmp[n]));
            n = n + 1;
        }
    }

    int i=0;
    for( i=1; i<n; i++){           //至此完成排序存储在tmp[]中
        int j = 0;
        for(j=0; j<i; j++){
            if(strcmp(tmp[i].d_name, tmp[j].d_name) < 0) {
                memcpy(&t, &tmp[j], sizeof(tmp[n]));
                memcpy(&tmp[j], &tmp[i], sizeof(tmp[n]));
                memcpy(&tmp[i], &t, sizeof(tmp[n]));
            }
        }
    }

    for(i=0; i<n; i++){
        char *filename = tmp[i].d_name;
        struct stat get_message = {};        //准备好用于接收stat的的结构体
        chdir(str);
        stat(filename, &get_message);       //读出stat

        if(show_hidden == 0)
        {
            if(filename[0] != '.')
            {
                if(r)
                {
                    if(tmp[i].d_type == '\004')
                    {
                        int n1 = strlen(str) + strlen(filename) + strlen("/") + 1;
                        int n2 = strlen(r_head) + strlen("/") + strlen("/") + 1;

                        char *r_str = (char *)malloc( n1 );
                        sprintf(r_str, "%s/%s", str, filename);
                    
                        char r_str_t[n1];             //设置暂存字符串接收malloc分配出来的内容
                        strcpy(r_str_t, r_str);

                        char *new_r_head = (char *)malloc( n2 );
                        sprintf(new_r_head, "%s--", r_head);
                    
                        char new_r_head_t[n2];      //设置暂存字符串接收malloc分配出来的内容
                        strcpy(new_r_head_t, new_r_head);

                        list_message(filename, &get_message, view_mod, r_head);
                        view0(r_str_t, r, show_hidden, view_mod, new_r_head_t);
                        free(new_r_head);
                        free(r_str);
                    }
                    else
                    {
                        list_message(filename, &get_message, view_mod, r_head);
                    }
                }
                else
                {
                    list_message(filename, &get_message, view_mod, r_head);
                }
            }
        }
        if(show_hidden)
        {
            if(r)
            {
                if(tmp[i].d_type == '\004')
                {
                    int n1 = strlen(str) + strlen(filename) + strlen("/") + 1;
                    int n2 = strlen(r_head) + strlen("/") + strlen("/") + 1;

                    char *r_str = (char *)malloc( n1 );
                    sprintf(r_str, "%s/%s", str, filename);

                    char r_str_t[n1];             //设置暂存字符串接收malloc分配出来的内容
                    strcpy(r_str_t, r_str);

                    char *new_r_head = (char *)malloc( n2 );
                    sprintf(new_r_head, "%s--", r_head);
                    
                    char new_r_head_t[n2];      //设置暂存字符串接收malloc分配出来的内容
                    strcpy(new_r_head_t, new_r_head);

                    list_message(filename, &get_message, view_mod, r_head);
                    view0(r_str_t, r, show_hidden, view_mod, new_r_head_t);
                    free(new_r_head);
                    free(r_str);
                }
                else
                {
                    list_message(filename, &get_message, view_mod, r_head);
                }   
            }
            else
            {
                list_message(filename, &get_message, view_mod, r_head);
            }
        }
    }

    closedir(dir);
    return 0;
}

int view1(char *str, int r, int show_hidden, int view_mod, char * r_head) {     //进行修改时间排序输出
    DIR * dir;
    struct dirent *ptr;

    if((dir=opendir(str)) == NULL) //打开文件流指针
    {
        fprintf(stderr,"cannot open directory:%s\n",str);
        return -1;
    }

    int n = 0;

    while( (ptr = readdir(dir)) !=NULL ){
        if(strcmp(ptr->d_name, ".") && strcmp(ptr->d_name, "..")) {
            n = n + 1;
        }
    }
    closedir(dir);
    struct dirent tmp[n], t;
    struct tm chtime[n], tt;                //接收存储时间的数组

    n = 0;
    dir=opendir(str);
    while((ptr = readdir(dir)) != NULL)     //遍历出ptr存储在tmp[]中，不包括.和..文件
    {
        char *filename = ptr->d_name;
        struct stat get_message = {};        //准备好用于接收stat的的结构体
        chdir(str);
        stat(filename, &get_message);       //读出stat

        if(strcmp(filename, ".") && strcmp(filename, "..")) {
            memcpy(&tmp[n], ptr, sizeof(tmp[n]));
            memcpy(&chtime[n], localtime(&(get_message.st_mtime)), sizeof(tt));
            n = n + 1;
        }
    }

    int i=0;
    for( i=1; i<n; i++){           //排序存储在tmp[]中
        int j = 0;
        for(j=0; j<i; j++){
            
            time_t ti = mktime(&chtime[i]);
            time_t tj = mktime(&chtime[j]);
            
            if( ti < tj ) {
                memcpy(&t, &tmp[j], sizeof(tmp[n]));
                memcpy(&tmp[j], &tmp[i], sizeof(tmp[n]));
                memcpy(&tmp[i], &t, sizeof(tmp[n]));

                tt = chtime[j];
                chtime[j] = chtime[i];
                chtime[i] = tt;
            }
        }
    }

    for(i=0; i<n; i++){
        char *filename = tmp[i].d_name;
        struct stat get_message = {};        //准备好用于接收stat的的结构体
        chdir(str);
        stat(filename, &get_message);       //读出stat

        if(show_hidden == 0)
        {
            if(filename[0] != '.')
            {
                if(r)
                {
                    if(tmp[i].d_type == '\004')
                    {
                        int n1 = strlen(str) + strlen(filename) + strlen("/") + 1;
                        int n2 = strlen(r_head) + strlen("/") + strlen("/") + 1;

                        char *r_str = (char *)malloc( n1 );
                        sprintf(r_str, "%s/%s", str, filename);
                    
                        char r_str_t[n1];             //设置暂存字符串接收malloc分配出来的内容
                        strcpy(r_str_t, r_str);

                        char *new_r_head = (char *)malloc( n2 );
                        sprintf(new_r_head, "%s--", r_head);
                    
                        char new_r_head_t[n2];      //设置暂存字符串接收malloc分配出来的内容
                        strcpy(new_r_head_t, new_r_head);

                        list_message(filename, &get_message, view_mod, r_head);
                        view1(r_str_t, r, show_hidden, view_mod, new_r_head_t);
                        free(new_r_head);
                        free(r_str);
                    }
                    else
                    {
                        list_message(filename, &get_message, view_mod, r_head);
                    }
                }
                else
                {
                    list_message(filename, &get_message, view_mod, r_head);
                }
            }
        }
        if(show_hidden)
        {
            if(r)
            {
                if(tmp[i].d_type == '\004')
                {
                    int n1 = strlen(str) + strlen(filename) + strlen("/") + 1;
                    int n2 = strlen(r_head) + strlen("/") + strlen("/") + 1;

                    char *r_str = (char *)malloc( n1 );
                    sprintf(r_str, "%s/%s", str, filename);

                    char r_str_t[n1];             //设置暂存字符串接收malloc分配出来的内容
                    strcpy(r_str_t, r_str);

                    char *new_r_head = (char *)malloc( n2 );
                    sprintf(new_r_head, "%s--", r_head);
                    
                    char new_r_head_t[n2];      //设置暂存字符串接收malloc分配出来的内容
                    strcpy(new_r_head_t, new_r_head);

                    list_message(filename, &get_message, view_mod, r_head);
                    view1(r_str_t, r, show_hidden, view_mod, new_r_head_t);
                    free(new_r_head);
                    free(r_str);
                }
                else
                {
                    list_message(filename, &get_message, view_mod, r_head);
                }   
            }
            else
            {
                list_message(filename, &get_message, view_mod, r_head);
            }
        }
    }

    close(dir);
    return 0;
};

int view2(char *str, int r, int show_hidden, int view_mod, char * r_head) {     //进行文件大小排序输出
    DIR * dir;
    struct dirent *ptr;

    if((dir=opendir(str)) == NULL) //打开文件流指针
    {
        fprintf(stderr,"cannot open directory:%s\n",str);
        return -1;
    }

    int n = 0;

    while( (ptr = readdir(dir)) !=NULL ){
        if(strcmp(ptr->d_name, ".") && strcmp(ptr->d_name, "..")) {
            n = n + 1;
        }
    }
    closedir(dir);
    struct dirent tmp[n], t;
    long int size[n], st;

    n = 0;
    dir=opendir(str);
    while((ptr = readdir(dir)) != NULL)     //遍历出ptr存储在tmp[]中，不包括.和..文件
    {
        char *filename = ptr->d_name;
        struct stat get_message = {};        //准备好用于接收stat的的结构体
        chdir(str);
        stat(filename, &get_message);       //读出stat

        if(strcmp(filename, ".") && strcmp(filename, "..")) {
            memcpy(&tmp[n], ptr, sizeof(tmp[n]));
            size[n] = get_message.st_size;
            n = n + 1;
        }
    }

    int i=0;
    for( i=1; i<n; i++){           //先进行名称排序，覆盖文件同大小的情况
        int j = 0;
        for(j=0; j<i; j++){
            if(strcmp(tmp[i].d_name, tmp[j].d_name) < 0) {
                memcpy(&t, &tmp[j], sizeof(tmp[n]));
                memcpy(&tmp[j], &tmp[i], sizeof(tmp[n]));
                memcpy(&tmp[i], &t, sizeof(tmp[n]));
                
                st = size[j];
                size[j] = size[i];
                size[i] = st;
            }
        }
    }

    for( i=1; i<n; i++){           //排序存储在tmp[]中
        int j = 0;
        for(j=0; j<i; j++){    
            if( size[i] < size[j] ) {
                memcpy(&t, &tmp[j], sizeof(tmp[n]));
                memcpy(&tmp[j], &tmp[i], sizeof(tmp[n]));
                memcpy(&tmp[i], &t, sizeof(tmp[n]));

                st = size[j];
                size[j] = size[i];
                size[i] = st;
            }
        }
    }

    for(i=0; i<n; i++){
        char *filename = tmp[i].d_name;
        struct stat get_message = {};        //准备好用于接收stat的的结构体
        chdir(str);
        stat(filename, &get_message);       //读出stat

        if(show_hidden == 0)
        {
            if(filename[0] != '.')
            {
                if(r)
                {
                    if(tmp[i].d_type == '\004')
                    {
                        int n1 = strlen(str) + strlen(filename) + strlen("/") + 1;
                        int n2 = strlen(r_head) + strlen("/") + strlen("/") + 1;

                        char *r_str = (char *)malloc( n1 );
                        sprintf(r_str, "%s/%s", str, filename);
                    
                        char r_str_t[n1];             //设置暂存字符串接收malloc分配出来的内容
                        strcpy(r_str_t, r_str);

                        char *new_r_head = (char *)malloc( n2 );
                        sprintf(new_r_head, "%s--", r_head);
                    
                        char new_r_head_t[n2];      //设置暂存字符串接收malloc分配出来的内容
                        strcpy(new_r_head_t, new_r_head);

                        list_message(filename, &get_message, view_mod, r_head);
                        view2(r_str_t, r, show_hidden, view_mod, new_r_head_t);
                        free(new_r_head);
                        free(r_str);
                    }
                    else
                    {
                        list_message(filename, &get_message, view_mod, r_head);
                    }
                }
                else
                {
                    list_message(filename, &get_message, view_mod, r_head);
                }
            }
        }
        if(show_hidden)
        {
            if(r)
            {
                if(tmp[i].d_type == '\004')
                {
                    int n1 = strlen(str) + strlen(filename) + strlen("/") + 1;
                    int n2 = strlen(r_head) + strlen("/") + strlen("/") + 1;

                    char *r_str = (char *)malloc( n1 );
                    sprintf(r_str, "%s/%s", str, filename);

                    char r_str_t[n1];             //设置暂存字符串接收malloc分配出来的内容
                    strcpy(r_str_t, r_str);

                    char *new_r_head = (char *)malloc( n2 );
                    sprintf(new_r_head, "%s--", r_head);
                    
                    char new_r_head_t[n2];      //设置暂存字符串接收malloc分配出来的内容
                    strcpy(new_r_head_t, new_r_head);

                    list_message(filename, &get_message, view_mod, r_head);
                    view2(r_str_t, r, show_hidden, view_mod, new_r_head_t);
                    free(new_r_head);
                    free(r_str);
                }
                else
                {
                    list_message(filename, &get_message, view_mod, r_head);
                }   
            }
            else
            {
                list_message(filename, &get_message, view_mod, r_head);
            }
        }
    }

    close(dir);
    return 0;
};