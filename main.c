#include "myls.h"
#include "sort.c"


int main(int argc,char **argv)
{
    int sort_mod = 0;           //排序方式：n(name)_0_名称_默认; t(time)_1_修改时间; s(size)_2_文件大小
    int r = 0;                  //递归方式：r(recursion)_1；默认为0时不会遍历显示目标目录的内容
    int show_hidden = 0;        //隐藏文件：a(all)_1; 默认为0时不显示隐藏文件
    int view_mod = 0;           //长型显示: l(long)_1; 默认为0时只显示文件名
    
    if (argc == 1)
    {
        char str[256];
        getcwd(str, 256);
        view(str, sort_mod, r, show_hidden, view_mod);
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
                    if( argv[i][j] == 'r' )
                        r = 1;
                    if( argv[i][j] == 'a' )
                        show_hidden = 1;
                    if( argv[i][j] == 'l' )
                        view_mod = 1;
                }
            }
        }
        for(i = 1; i<argc; i++) {
            if( argv[i][0] != '-' ) {
                if( argv[i][0] == '/' ) {               //处理根目录开头的参数
                    char str[256];
                    strcpy(str, argv[i]);
                    printf("=======%s======\n", str);
                    view(str, sort_mod, r, show_hidden, view_mod);
                }
                else{
                    char str[256];
                    getcwd(str, 256);
                    //strcat(str, argv[i]);
                    sprintf(str, "%s/%s", str, argv[i]);
                    printf("=======%s======\n", str);
                    view(str, sort_mod, r, show_hidden, view_mod);
                }
            }
        }
    }
    return 0;
}