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
        int fd0 = open("client1", O_WRONLY);
        int fd1 = open("server1", O_RDONLY);
        close(fd0);
        close(fd1);
        exit(0);
    }
}

int main()
{
    char input[100];
    signal(SIGINT, sighandler);

    if (run_client() == 1)
    {
        sleep(1);
        printf("\n");
        printf("Type in your input\n");

        while (1)
        {
            int fd0 = open("client1", O_WRONLY);
            fgets(input, sizeof(input), stdin);
            write(fd0, input, sizeof(input));

            int fd1 = open("server1", O_RDONLY);
            read(fd1, input, sizeof(input));
            printf("%s\n", input);
        }
    }

    return 0;
}