#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
new_proc(int p[2])
{
    close(p[1]);
    int prime;
    read(p[0], &prime, 4);
    if (prime) {
        printf("prime %d\n", prime);
        int next_p[2];
        pipe(next_p);
        if (fork() == 0) {
            new_proc(next_p);
        } else {
            close(next_p[0]);
            int num;
            while (read(p[0], &num, 4)) {
                if (num % prime) {
                    write(next_p[1], &num, 4);
                }
            }
            close(next_p[1]);
            wait(0);
        }
    }
}

int
main(int argc, char *argv[])
{
    int p[2];
    pipe[p];
    int prime = 2;
    printf("prime %d\n", 2);

    if (fork() == 0) {
        new_proc(p);
    } else {
        close(p[0]);
        for (int num=2; num<=35; ++num) {
            if (num % prime) {
                write(p[1], &num, 4);
            }
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}