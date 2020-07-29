#include "mysl.h"
#include "sort.c"


int main(int argc,char **argv)
{
    int r = 1;
    int show_hidden = 1;
    int view_mod = 0;
    char str[256];
    if (argc == 1)
    {
        // char dir[256];
        // getcwd(dir, 256);
        // test(dir);
        //printf("打印当前目录");
        getcwd(str, 256);
    }
    else if(argc == 2)
    {

        if(argv[1][0] == '-')
        {
            int i = 0;
            printf("参数有：");
            for(i = 1; i < strlen(argv[1]); i++)
            {
                printf("%c",argv[1][i]);
            }
            printf("\n");
        }
        else
        {
            printf("打印%s",argv[1]);
        }
    }
    else if(argc == 3)
    {
        if(argv[1][0] == '-')
        {
            int i = 0;
            printf("参数有：");
            for(i = 1; i < strlen(argv[1]); i++)
            {
                printf("%c",argv[1][i]);
            }
            printf("\n");
        }
        printf("打印%s\n",argv[2]);
    }
    view(str, 0, r, show_hidden, view_mod);
    printf("Hello world!\n");
    return 0;
}