#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

void prime_s(int* p)
{
    close(p[WRITE]);
    int num, prime;
    int p2[2];
    pipe(p2);
    if (read(p[READ], &num, sizeof(int)) == 0)
        exit(0);

    if (fork() == 0)
    {
        prime_s(p2);
    }
    else
    {
        prime = num;
        printf("prime %d\n", num);
        close(p2[READ]);
        while (read(p[READ], &num, sizeof(int)))
        {
            if (num % prime)
                write(p2[WRITE], &num, sizeof(int));
        }
        close(p2[WRITE]);
        wait(0);
    }
    close(p[READ]);
    exit(0);
}

int main(int argc, char** argv)
{
    int pid;
    int p1[2];
    pipe(p1);
    if ((pid = fork()) < 0)
    {
        exit(1);
    }
    else if (pid > 0)
    {
        close(p1[READ]);
        for (int i = 2; i < 36; i++)
            write(p1[WRITE], &(i), sizeof(int));
        close(p1[WRITE]);
        wait(0);
    }
    else if (pid == 0)
    {
        prime_s(p1);
    }
    exit(0);

}
