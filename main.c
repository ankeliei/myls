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
                    //strcat(str, argv[i]);
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
            view(str, sort_mod, R, show_hidden, view_mod, r);
        }
    }
    return 0;
}