#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main() {
    struct sockaddr_rc addr = { 0 };
    int s, client, status;
    char buf[BUFFER_SIZE];
    char file_name[256];
    FILE *fp;

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (s < 0) {
        perror("Error allocating socket");
        return 1;
    }

    // bind socket to port 1 of the first available local bluetooth adapter
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_bdaddr = *BDADDR_ANY;
    addr.rc_channel = (uint8_t) 1;
    status = bind(s, (struct sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        perror("Error binding socket");
        return 1;
    }

    // listen for connections
    status = listen(s, 1);
    if (status < 0) {
        perror("Error listening for connections");
        return 1;
    }

    printf("Server is listening for connections\n");

    // accept one connection
    client = accept(s, NULL, NULL);
    if (client < 0) {
        perror("Error accepting connection");
        return 1;
    }
    printf("Client connected\n");

    // receive file name from client
    memset(buf, 0, sizeof(buf));
    status = read(client, buf, sizeof(buf));
    if (status < 0) {
        perror("Error receiving filename from client");
        close(client);
        close(s);
        return 1;
    }
    strcpy(file_name, buf);
    printf("Received file name: %s\n", file_name);

    // open file and read its contents
    fp = fopen(file_name, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        close(client);
        close(s);
        return 1;
    }

    memset(buf, 0, sizeof(buf));
    int bytes_read = fread(buf, 1, BUFFER_SIZE, fp);
    while (bytes_read > 0) {
        // send the read bytes to the client
        int bytes_sent = write(client, buf, bytes_read);
        if (bytes_sent < 0) {
            perror("Error sending file data to client");
            break;
        }
        // read the next chunk of bytes
        bytes_read = fread(buf, 1, BUFFER_SIZE, fp);
    }

    // close the file and the sockets
    fclose(fp);
    close(client);
    close(s);

    return 0;
}
