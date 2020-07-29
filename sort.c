#include "myls.h"
#include "view.c"
int view(char *str, int sort_mod, int r, int show_hidden , int view_mod) {
    if(sort_mod == 0)
        view1(str, r, show_hidden, view_mod, "");
    if(sort_mod == 1)
        view2(str, r, show_hidden, view_mod, "");
    if(sort_mod == 3)
        view3(str, r, show_hidden, view_mod);
}

int view1(char *str, int r, int show_hidden, int view_mod, char * r_head) {     //进行文件名排序输出
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
                //tmp[j] = t;
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
                        char *r_str = (char *)malloc( strlen(str) + strlen(filename) + strlen("/") );
                        sprintf(r_str, "%s/%s", str, filename);
                        char *new_r_head = (char *)malloc( strlen(r_head) + strlen("/") );
                        sprintf(new_r_head, "%s--", r_head);
                        //printf("%s\n",r_str);
                        list_message(file_name, &get_message, view_mod, r_head);
                        view1(r_str, r, show_hidden, view_mod, new_r_head);
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
                    char *r_str = (char *)malloc( strlen(str) + strlen(filename) + strlen("/") );
                    sprintf(r_str, "%s/%s", str, filename);
                    char *new_r_head = (char *)malloc( strlen(r_head) + strlen("/") );
                    sprintf(new_r_head, "%s--", r_head);
                    //printf("%s\n",r_str);
                    list_message(filename, &get_message, view_mod, r_head);
                    view1(r_str, r, show_hidden, view_mod, new_r_head);
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
                //list_message(filename, &get_message, view_mod, "");
        }
    }

    closedir(dir);
    return 0;
}

int view2(char *str, int r, int show_hidden, int view_mod, char * r_head) {     //进行时间排序输出
    
};

int view3(char *str, int r, int show_hidden, int view_mod){};


// int view_simple(char *str)
// {

//     DIR * dir;
//     struct dirent *ptr;

//     if((dir=opendir(str)) == NULL) //打开文件流指针
//     {
//         fprintf(stderr,"cannot open directory:%s\n",str);
//         return -1;
//     }

//     chdir(str);

//     while((ptr = readdir(dir)) != NULL)
//     {
//         if (ptr->d_name[0] != '.')
//             printf("%-10s\t", ptr->d_name);
//     }
//     closedir(dir);

//     return 0;
// }

// int view2(char *str)     //复杂化输出
// {
//     DIR * dir;
//     struct dirent *ptr;

//     if((dir=opendir(str)) == NULL) //打开文件流指针
//     {
//         fprintf(stderr,"cannot open directory:%s\n",str);
//         return -1;
//     }

//     //chdir(str);

//     while((ptr = readdir(dir)) != NULL)
//     {
//         char * filename = ptr->d_name;   //遍历得到文件名
//         struct stat get_message = {};        //准备好用于接收stat的的结构体
//         stat(filename, &get_message);
//         if ( strcmp(filename, ".") && strcmp(filename, "..") )
//         {
//             list_message(filename, &get_message);
//         }
//     }

//     closedir(dir);
//     return 0;
// }

// void test( char * str){
//     //view1(str, 1, 1, 1);
// }