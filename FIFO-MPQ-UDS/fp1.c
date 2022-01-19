#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd; 
  
    char * myfifo="/tmp/myfifo"; 
    mkfifo(myfifo, 0777);

    int num=14;

    fd = open(myfifo, O_WRONLY);
    write(fd, &num, sizeof(num));
    close(fd);

    sleep(1);

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

        p++;

        i=i+num-1;
    }

    for(int k=0; k<10; k++)
    {
        for(int i=0; i<5; i++)
        {
            fd=open(myfifo, O_WRONLY);
            write(fd, ans[i+k*5], sizeof(ans[i+k*5]));
            close(fd);

            sleep(1);
        }

        for(int i=0; i<5; i++)
        {
            int g=i+k*5;

            fd=open(myfifo, O_WRONLY);
            write(fd, &g, sizeof(g));
            close(fd);

            sleep(1);
        }

        int idr;

        fd=open(myfifo, O_RDONLY);
        read(fd, &idr, sizeof(idr));
        close(fd);

        printf("Batch: %d || Max Id Recieved: %d\n", k+1, idr);
    }

    return 0; 
}