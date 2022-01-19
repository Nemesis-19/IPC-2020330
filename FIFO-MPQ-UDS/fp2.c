#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
    int fd1; 
    char * myfifo = "/tmp/myfifo";

    int num1;

    fd1 = open(myfifo,O_RDONLY);
    read(fd1, &num1, sizeof(num1));
    close(fd1);

    char arr[50][num1+1];

    int arr2[50];

    for(int h=0; h<10; h++)
    {
        printf("String Batch %d:\n", h+1);

        for(int i=0; i<5; i++)
        {
            fd1 = open(myfifo,O_RDONLY); 
            read(fd1, arr[i+h*5], sizeof(arr[i+h*5]));
            close(fd1);
        }

        for(int i=0; i<5; i++)
        {
            fd1 = open(myfifo,O_RDONLY); 
            read(fd1, &arr2[i+h*5], sizeof(arr2[i+h*5]));
            close(fd1);
        }

        int id=-1;

        for(int i=0; i<(h+1)*5; i++)
        {
            if(i>id)
            {
                id=i;
            }
        }

        fd1=open(myfifo, O_WRONLY);
        write(fd1, &id, sizeof(id));
        close(fd1);

        for(int i=0; i<5; i++)
        {
            printf("ID Recieved: %d || String Recieved: ", arr2[i+h*5]);

            for(int j=0; j<14; j++)
            {
                printf("%c", arr[i+h*5][j]);
            }

            printf("\n");
        }
    }

    return 0; 
}