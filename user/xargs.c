#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAXARG 32 
#define stdin 0 
#define stdout 1 
#define stderr 2
#define MAXLEN 32
char* arg[MAXARG];
int count, len;
char args[MAXARG][MAXLEN];

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        // argv[0] = xargs, argv[1] = cmd , 因为exec(cmd, arg) 中 arg[0] == cmd
        arg[i - 1] = argv[i];
    }
    char buf;
    // char* cmd = argv[0];
    // 从stdin中读入数据 管道前面的命令输出在stdin当中，
    while (read(stdin, &buf, 1) > 0)
    {
        // printf("%c", buf);
        //测试当中 find . b 输出是以\n分割的， echo的输出是' '分割
        if (buf == '\n' || buf == ' ')
        {
            arg[count + argc - 1] = args[count];
            len = 0;
            count++;

        }
        else if (buf != ' ')
        {
            args[count][len] = buf;
            len++;
        }
    }
    if (fork() == 0)
    {
        exec(argv[1], arg);
        // exec命令执行后会自动exit(0);
    }
    else
    {
        wait(0);
        exit(0);
    }
    for (int i = 0; i < count + argc + 1; i++)
    {
        printf("arg[%d] = %s\n", i, arg[i]);
    }
    // printf("args = %s\n", args[0]);
    exit(0);
}
