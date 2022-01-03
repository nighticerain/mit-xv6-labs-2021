#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2], p2[2];
    int pid;

    if (pipe(p1) < 0 || pipe(p2) < 0) {
        exit(1);
    }

    if (fork() == 0) {
        pid = getpid();
        char buf[2];
        close(p1[1]);
        if (read(p1[0], buf, 1) != 1) {
            fprintf(2, "child fail to read\n");
            exit(1);
        }
        close(p1[0]);
        printf("%d: received ping\n", pid);
        close(p2[0]);
        if (write(p2[1], buf, 1) != 1) {
            fprintf(2, "child fail to write\n");
            exit(1);
        }
        close(p2[1]);
        exit(0);
    } else {
        pid = getpid();
        char buf[2];
        close(p1[0]);
        if (write(p1[1], "O", 1) != 1) {
            fprintf(2, "parent fail to write\n");
            exit(1);
        }
        close(p1[1]);
        if (read(p2[0], buf, 1) != 1) {
            fprintf(2, "parent fail to read\n");
            exit(1);
        }
        printf("%d: received pong\n", pid);
        close(p2[0]);
        close(p2[1]);
        exit(0);
    }
}