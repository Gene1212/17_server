#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int run_server()
{

    mkfifo("clientpipe", 0777);
    mkfifo("serverpipe", 0777);
    char s[100];
    char x[100] = "Server recieved data";
    char y[100];
    printf("Handshake initialized, attempting to contact client...\n");
    int fd0 = open("serverpipe", O_WRONLY);
    int fd1 = open("clientpipe", O_RDONLY);

    read(fd1, s, sizeof(s));
    if (!strcmp(s, "Success"))
    {
        printf("Server recieved data\n");
    }
    write(fd0, x, sizeof(x));
    read(fd1, y, sizeof(y));

    if (!strcmp(y, "Server sent data successfully"))
    {
        printf("Server sent data successfully\n");
    }
    remove("serverpipe");
    remove("clientpipe");

    return 0;
}