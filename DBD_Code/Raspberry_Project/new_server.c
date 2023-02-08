#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BUF 1024

int main(int argc, char **argv)
{
    struct sockaddr_rc serv_addr = { 0 }, cli_addr = { 0 };
        // this is needed so that it can work properly with accpet!!!
    int s, client, items_read;
    socklen_t opt = sizeof(cli_addr);// this is used to hold the size of the client tp be passed right 
    char buf[BUF]; // inits the buffer to be this size, will change if needed

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM); //Thi will make the socket

    serv_addr.rc_family = AF_BLUETOOTH; // set for bluetooth comms
    serv_addr.rc_bdaddr = *BDADDR_ANY; // connects to any bluetooth device needs to be changed for later
    serv_addr.rc_channel = (uint8_t)1; // sets the serv addr to channel one
    bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        // bind will allows connections from the client! (cli_addr)

    listen(s, 1); // makes the socket listen to any connections and limits it to only one connection

    client = accept(s, (struct sockaddr *)&cli_addr, &opt);
        // accepts connection to the socket s 
        // we need to type cast to a sockaddr pointer at the address of the client address 
        // opt is the size socket lenght 
    ba2str( &cli_addr.rc_bdaddr, buf );
        // converts the bluetooth address at the address of cli_addr to a string
        // this string is stored in the buffer
        // this is needed since we are converting the binary from the address of cli_addr 
        // to a more readable bluetooth address string
        // this allows us to see what connection has been accpeted at fprintf 
    fprintf(stderr, "accepted connection from %s\n", buf);
        // have to use fprintf to write to the standard error stream instead of teh standard output stream 
    // enter a loop for sending and receiving messages
    while(1) {
        memset(buf, 0, sizeof(buf));
                // sets the blocks of memory in the buffer to be ZERO
        items_read = read(client, buf, sizeof(buf)); // reads characters from the client
        if( items_read <= 0 ) {
            perror("Didn't Get Message"); 
                        //stops since nothing has been sent or encounters an error
            break;
        }
        printf("Message Received: %s\n", buf);

        // send a message
        if(write(client, buf, sizeof(buf)) < 0) {
            perror("Couldn't Send Message");
                        // error control
            break;
        }
    }

    close(client); // important to close the client and the socket we made!!!!
    close(s);
    return 0;
}
