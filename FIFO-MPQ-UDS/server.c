#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#define path "/tmp/socket"

int main()
{
    struct sockaddr_un server_socket;

    unlink(path);

    int sender_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&server_socket, 0, sizeof(struct sockaddr_un));

    server_socket.sun_family = AF_UNIX;

    strncpy(server_socket.sun_path, path, sizeof(server_socket.sun_path) - 1);

    bind(sender_socket, (const struct sockaddr *) &server_socket, sizeof(struct sockaddr_un));

    listen(sender_socket, 20);

    int reciever_socket = accept(sender_socket, NULL, NULL);

    char buffer[1024]={0};

    for(int i=0; i<10; i++)
    {
        printf("String Batch %d:\n", i+1);

        char num[2];

        for(int j=0; j<5; j++)
        {
            memset(buffer, 0, 1024);

            read(reciever_socket, buffer, 1024);

            memset(num, 0, sizeof(num));

            read(reciever_socket, num, sizeof(num));

            if(j+i*5<10)
            {
                printf("ID Recieved: %c || String Recieved: %s\n", num[0], buffer );
            }
            else
            {
                printf("ID Recieved: %c%c || String Recieved: %s\n", num[0], num[1], buffer);
            }
        }

        sleep(1);

        write(reciever_socket, num, strlen(num));
    }

    return 0;
}