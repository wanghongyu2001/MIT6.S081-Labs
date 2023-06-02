#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

int main(int argc, char* argv[])
{
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);
    int pid = fork();
    char buf[1];
    if (pid < 0)
    {
        exit(1);
    }
    else if (pid == 0)
    {
        close(p1[WRITE]);
        close(p2[READ]);
        read(p1[READ], buf, 1);
        write(p2[WRITE], " ", 1);
        printf("%d: received ping\n", getpid());
        close(p1[READ]);
        close(p2[WRITE]);
        exit(0);
    }
    else
    {
        close(p1[READ]);
        close(p2[WRITE]);
        write(p1[WRITE], " ", 1);
        read(p2[READ], buf, 1);
        printf("%d: received pong\n", getpid());
        close(p1[WRITE]);
        close(p2[READ]);
        exit(0);
    }

    return 0;
}
