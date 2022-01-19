#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <unistd.h>

typedef struct mesg_buffer 
{
	long mesg_type;
	char mesg_text[100];
	int id;
} message;

int main()
{
	message msgs;
	key_t key;
	int msgid;

	message msgr;
	key_t keyr;
	int msgidr;

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

        p++;

        i=i+num-1;
    }

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<5; j++)
		{
			key = ftok("sending to p2", 2);

			msgid = msgget(key, 0644 | IPC_CREAT);
			msgs.mesg_type = 1;
			msgs.id=j+i*5;

			for(int k=0; k<num; k++)
			{
				msgs.mesg_text[k]=ans[j+i*5][k];
			}

			msgsnd(msgid, &msgs, sizeof(msgs), 2);
		}

		keyr=ftok("sending to p1", 3);

		msgidr = msgget(keyr, 0644 | IPC_CREAT);

		msgrcv(msgidr, &msgr, sizeof(msgr), 2, 3);

		printf("Batch: %d || Highest Id Recieved: %d\n", i+1, msgr.id);
	}

	msgctl(msgidr, IPC_RMID, NULL);

	return 0;
}