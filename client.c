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
    run_client();
    signal(SIGINT, sighandler);
    printf("\n");
    printf("Type in your input\n");

    while (1)
    {
        int fd0 = open("client1", O_WRONLY);
        fgets(input, sizeof(input), stdin);
        write(fd0, input, sizeof(input));
        close(fd0);

        int fd1 = open("server1", O_RDONLY);
        read(fd1, input, sizeof(input));
        printf("%s\n", input);
        close(fd1);
    }

    return 0;
}