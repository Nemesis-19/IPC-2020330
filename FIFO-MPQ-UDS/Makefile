default:
	sudo touch socket
	sudo chmod 755 socket
	gcc server.c -o server
	gcc client.c -o client
fifo:
	gcc fp1.c -o fp1
	gcc fp2.c -o fp2
msg:
	gcc mp1.c -o mp1
	gcc mp2.c -o mp2
clean:
	rm -f fp1 fp2 mp1 mp2 server client socket