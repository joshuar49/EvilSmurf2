#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main() {
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "58:11:22:62:56:E3"; // replace with the address of the target device
    char file_name[256] = "pi.sh"; // replace with the known file name
    char buffer[1024];
    FILE *fp;

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to the server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
    	perror("Error connecting to server");
    	close(s);
    	return 1;
    }
    printf("Properly connected to server");
    // send the file name to the server
    status = write(s, file_name, sizeof(file_name));
	printf("Properly wrote to host\n");
    // receive the file
    fp = fopen("pi.sh", "w+");
	if (fp == NULL){
		printf("ERROR: couldnt open fie!\n");
		close(s);
		return 1;
	}
	printf("File was able to be written to!\n");
    int n;
    while( (n = read(s, buffer, sizeof(buffer))) > 0 ) {
        fwrite(buffer, 1, n, fp);
		printf("I am here now in th loop\n");
    }

    // close the file and the socket
    fclose(fp);
    close(s);

    return 0;
}
