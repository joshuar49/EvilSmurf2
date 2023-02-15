#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main() {
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "00:11:22:33:44:55"; // replace with the address of the target device
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

    // send the file name to the server
    status = write(s, file_name, sizeof(file_name));

    // receive the file
    fp = fopen("received_file.txt", "w+");
    while( (status = read(s, buffer, sizeof(buffer))) > 0 ) {
        fwrite(buffer, 1, status, fp);
    }

    // close the file and the socket
    fclose(fp);
    close(s);

    return 0;
}
