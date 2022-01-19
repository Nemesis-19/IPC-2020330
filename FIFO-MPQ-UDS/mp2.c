#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct mesg_buffer {
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

	int id[50];

	for(int i=0; i<10; i++)
	{
		printf("String Batch %d:\n", i+1);

		for(int j=0; j<5; j++)
		{
			key = ftok("sending to p2", 3);

			msgid = msgget(key, 0644 | IPC_CREAT);

			msgrcv(msgid, &msgs, sizeof(msgs), 1, 2);

			id[j+i*5]=msgs.id;

			printf("Id recieved: %d || String Received: %s\n", msgs.id, msgs.mesg_text);
		}

		int max=-1;

		for(int g=0; g<(i+1)*5; g++)
		{
			if(id[g]>max)
			{
				max=id[g];
			}
		}

		sleep(1);

		keyr=ftok("sending to p1", 3);

		msgidr = msgget(keyr, 0644 | IPC_CREAT);

		msgr.mesg_type=2;
		msgr.id=max;

		msgsnd(msgidr, &msgr, sizeof(msgr), 3);
	}

	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}