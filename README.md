# OS-IPC-2020330
Made an IPC project to display the communication between process using different options: SIGNALS, FIFO, Message Passing Ques &amp; Unix Domain Sockets

There are 3 code files in SIGNAL, SR, ST & main. main uses exec call to intiate SR and ST programs. SR generates a randum number and sends it to main using the SIGTERM 
handler. ST generates a random number and uses __rdtsc functionality to generate current time and sends both to main. main has to recieve from both SR & ST and print the data
in a phased manner. This process continues infinitely.

There are 6 files in FIFO, MPQ, UDS. 2 files each, fifo:fp1, fp2; mpq:mp1, mp2; uds:server, client. In all 3 cases the first file generates a batch of 5 random strings along 
with their ids, and sends it to the second file 10 times using their specified mode. The second file prints the recieved strings and sends back the highest id recieved to the 
first file again using the same specified mode. First program prints the highest ID recieved and this process continues for 10 cycles.
