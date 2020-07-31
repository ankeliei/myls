#include "myls.h"
#include "sort.c"


int main(int argc,char **argv)
{
    int sort_mod = 0;           //排序方式：n(name)_0_名称_默认; t(time)_1_修改时间; s(size)_2_文件大小
    int R = 0;                  //递归方式：R(recursion)_1；默认为0时不会遍历显示目标目录的内容
    int show_hidden = 0;        //隐藏文件：a(all)_1; 默认为0时不显示隐藏文件
    int view_mod = 0;           //长型显示: l(long)_1; 默认为0时只显示文件名
    int r = 0;                  //反向排序：默认为0，用于在排序时参与位运算以获得反向排序效果

    if (argc == 1)
    {
        char str[256];
        getcwd(str, 256);
        printf("=======%s======\n", str);
        view(str, sort_mod, R, show_hidden, view_mod, r);
    }
    else
    {
        int i = 0;
        for(i = 1; i<argc; i++) {
            if( argv[i][0] == '-' ) {
                int j = 1;
                for( j = 1; j < strlen(argv[i]); j++ ) {
                    if( argv[i][j] == 'n' )
                        sort_mod = 0;
                    if( argv[i][j] == 't' )
                        sort_mod = 1;
                    if( argv[i][j] == 's' )
                        sort_mod = 2;
                    if( argv[i][j] == 'R' )
                        R = 1;
                    if( argv[i][j] == 'a' )
                        show_hidden = 1;
                    if( argv[i][j] == 'l' )
                        view_mod = 1;
                    if( argv[i][j] == 'r' )
                        r = 1;
                    if( argv[i][j] == 'h' ) {
                        printf("\t\tmyls命令--linux程序设计课程设计\n");
                        printf("默认参数为：当前目录、短显示、不递归、不反序、名称排序。\n");
                        printf("可选参数：\n");
                        printf("\t–t(time)、-s(size)、-n(name)选项调整输出顺序，冲突时以命令行中最后出现的为准。\n");
                        printf("\t-r(reverse)反次序输出。\n");
                        printf("\t-a(all)显示隐藏文件，. 与 ..文件不显示。\n");
                        printf("\t-l(long)长行输出文件的详细信息，文件大小自动化B、KB、MB。\n");
                        printf("\t-R(recursive)递归输出目标目录下所有子目录及其下文件。\n");
                        printf("\t-h(help)输出帮助信息，并立即退出。\n");
                        printf("可以处理命令行输入的零至多个目标目录参数并加以显示。\n");
                        return 0;
                    }
                }
            }
        }
        int single_options = 0;     //用来记录非选项('-'开头)的参数个数
        for(i = 1; i<argc; i++) {
            if( argv[i][0] != '-' ) {
                if( argv[i][0] == '/' ) {               //处理根目录开头的参数
                    char str[256];
                    strcpy(str, argv[i]);
                    printf("=======%s======\n", str);
                    view(str, sort_mod, R, show_hidden, view_mod, r);
                }
                else{
                    char str[256];
                    getcwd(str, 256);
                    sprintf(str, "%s/%s", str, argv[i]);
                    printf("=======%s======\n", str);
                    view(str, sort_mod, R, show_hidden, view_mod, r);
                }
                single_options = 1;
            }
        }
        if (single_options == 0) {
            char str[256];
            getcwd(str, 256);
            printf("=======%s======\n", str);
            view(str, sort_mod, R, show_hidden, view_mod, r);
        }
    }
    return 0;
}