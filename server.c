#include "ch.h"
#include "sh.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

static void sighandler(int signo)
{
    if (signo == SIGINT)
    {
        remove("server1");
        remove("client1");
        exit(0);
    }
}
int main()
{
    char input[100];
    signal(SIGINT, sighandler);

    if (run_server() == 1)
    {
        mkfifo("server1", 0777);
        mkfifo("client1", 0777);

        while (1)
        {
            int fd1 = open("client1", O_RDONLY);
            read(fd1, input, sizeof(input));

            printf("1\n");

            char *p = input;
            while (*p)
            {
                (*p += 1);
                p++;
            }

            int fd0 = open("server1", O_WRONLY);
            printf("2\n");
            write(fd0, input, sizeof(input));
            printf("3\n");
        }
    }

    //int c = 1;

    return 0;
}