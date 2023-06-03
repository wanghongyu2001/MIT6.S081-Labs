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

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        arg[i - 1] = argv[i];
    }
    char buf;
    // char* cmd = argv[0];
    char args[MAXARG][MAXLEN];
    while (read(stdin, &buf, 1) > 0)
    {
        // printf("%c", buf);
        if (buf == '\n' || buf == ' ')
        {
            arg[count + argc - 1] = args[count];
            len = 0;
            count++;

        }
        // args[0][len] = buf;
        // len++;
        else if (buf != ' ')
        {
            args[count][len] = buf;
            len++;
        }
    }
    if (fork() == 0)
    {
        exec(argv[1], arg);
        // exit(0);
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
