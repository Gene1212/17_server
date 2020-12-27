#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int run_client()
{
    char s[100] = "Success";
    char x[100];
    char y[100] = "Server sent data successfully";
    printf("Handshake initialized, attempting to contact server...\n");
    int fd1 = open("serverpipe", O_RDONLY);
    int fd0 = open("clientpipe", O_WRONLY);

    write(fd0, s, sizeof(s));
    read(fd1, x, sizeof(x));

    if (!strcmp(x, "Server recieved data"))
    {
        printf("Client recieved data\n");
        printf("Client sent data successfully\n");
    }

    write(fd0, y, sizeof(y));

    return 1;
}