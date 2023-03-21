#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main() {
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "58:11:22:62:56:CE"; // replace with the address of the target device
    char file_name[256] = "file.txt"; // replace with the known file name
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer)); //ensures the buffer is initalized to 0 and contains no garbage data
    FILE *fp;

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (s < 0) {
        perror("Error allocating to the socket");
        return 1;
    
    }

    // connect to the server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
    	perror("Error connecting to server");
    	return 1;
    }
    printf("Properly connected to server\n");
    
    // send the file name to the server
    status = write(s, file_name, sizeof(file_name));
    printf("Properly wrote to host\n");
    //needs filepath to help get the file from the server, the name is not enough to grasp the file
    
    
    //receive the file
    //creates file working on using file to extract other files from server to client
    fp = fopen("file.txt", "w+");
	if (fp == NULL){
		printf("ERROR: couldnt open file!\n");
		close(s);
		return 1;
	}
	printf("File was able to be written to!\n");
    //using int n might also cause the issue
    int n = 0;
    int done = 0;
    //why are u using a read function to fix this, maybe read is the issue
    while (!done) {
        n = read(s, buffer, sizeof(buffer));
        if (n > 0) {
        //writes data from the buffer into fp, where buffer is the pointer, 1 is the size of each byte, n is the number of bytes needing to be written number of bytes from the socket, file pointer to the file being written
            fwrite(buffer, 1, n, fp);
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
       printf("Received data: %s\n", buffer);
       perror("Error receiving data from server");
    }
    

    // close the file and the socket
    fclose(fp);
    close(s);

    return 0;
}

