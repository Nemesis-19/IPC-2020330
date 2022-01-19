#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#define path "/tmp/socket"

int main()
{
    int num=14;

    char arr[26]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    char res[num*50+1];

    for(int i=0; i<num*50; i++)
    {
        res[i]=arr[rand()%26];
    }

    char ans[50][num+1];

    int p=0;

    for(int i=0; i<num*50; i++)
    {
        int k=0;

        for(int j=i; j<i+num; j++)
        {

            ans[p][k]=res[j];

            k++;
        }

        ans[p][k]='\0';

        p++;

        i=i+num-1;
    }

    struct sockaddr_un client_socket;

    int reciever_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&client_socket, 0, sizeof(struct sockaddr_un));

    client_socket.sun_family = AF_UNIX;
    strncpy(client_socket.sun_path, path, sizeof(client_socket.sun_path) - 1);

    connect (reciever_socket, (const struct sockaddr *) &client_socket, sizeof(struct sockaddr_un));

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<5; j++)
        {
            char str[11];
            strcpy(str, ans[j+i*5]);
            write(reciever_socket, str, strlen(str));
            sleep(1);

            char snum[2];
            sprintf(snum, "%d", (j+i*5));
            write(reciever_socket, snum, strlen(snum));
            sleep(1);
        }

        char max[100];

        read(reciever_socket, max, sizeof(max));

        if(i<2)
        {
            printf("Batch: %d || Highest ID Recieved: %c\n", i+1, max[0]);
        }
        else
        {
            printf("Batch: %d || Highest ID Recieved: %c%c\n", i+1, max[0], max[1]);
        }
    }

    return 0;
}