#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<pwd.h>         //用户名的获取用到
#include<grp.h>       //用户组的获取用到
#include<time.h>     //文件修改时间
#include <unistd.h>     //getcwd()函数需要

#define PRINT_RED(s) printf("\033[0;31m%s\033[0;39m",s);
#define PRINT_GREEN(s) printf("\033[0;32m%s\033[0;39m",s);
#define PRINT_YELLOW(s) printf("\033[0;33m%s\033[0;39m",s);
#define PRINT_BULE(s) printf("\033[0;34m%s\033[0;39m",s);
#define PRINT_PURPLE(s) printf("\033[0;35m%s\033[0;39m",s);
#define PRINT_CYAN(s) printf("\033[0;36m%s\033[0;39m",s);
#define PRINT_WHITE(s) printf("\033[0;36m%s\033[0;39m",s);