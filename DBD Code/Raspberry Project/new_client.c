#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BUF 1024

int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 }; // creates the structure for THIS device
    int s, status;
    char dest[18] = "58:11:22:62:56:CD"; // mac of the kali machine
    char buf[BUF];// inits the buffer 

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
        // same as server it screate the socket with these parameters same as in the server

    addr.rc_family = AF_BLUETOOTH; // sets the type of family to be bleutooth
    addr.rc_channel = (uint8_t) 1; // sets the channel to 1 same as in the server
    str2ba( dest, &addr.rc_bdaddr ); // converts the string amc address to a binary val

    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
        // manually passing the value to the connect function to connect to it 
    if( status < 0 ) { // error handling!
        perror("Can't Connect To Server!");
        return -1;
    }

    // here since the connection is established from earlier we can start the loop of
        // communication with the server 
    while(1) {
        printf("Enter Message: ");
        fgets(buf, BUF, stdin);
                // this will read from the other terminal, stores it into the buf var 
                // but it has to be with in the size of BUF 1024 
        if(strncmp(buf, "quit", 4) == 0) break;
                // compaites the strings from the first 4 chars in the buffer to strign
                // if the 2 srtings are equal it will return 0 and quits the loop

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
