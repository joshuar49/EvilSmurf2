// we will nee to install bluez on the raspberry pi in order for all this to work properaly

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

// this will be the server code used

int main(int argc, char **argv)
{
        int socketDesc = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
//JON's porion
//what SOCKET does is that it creates a unbounded socket,
//with this once specifies 3 params DOMAIN, TYPE, PROTOCOL
//BTPROTO is a protocol to ask for a rfcomm socket

        struct sockaddr_rc server_addr = {0};
        server_addr.rc_family = AF_BLUETOOTH;
        server_addr.rc_bdaddr = *BDADDR_ANY;
        server_addr.rc_channel = (uint8_t) 1;

        bind(socketDesc, (struct sockaddr *)&server_addr, sizeof(server_addr));

        listen(socketDesc, 1);

        struct sockaddr_rc client_addr = {0};
        socklen_t opt = sizeof(client_addr);
        int client = accept(socketDesc, (struct scokaddr *)&client_addr, &opt);

        char mini_buf[256] = {0};

        char buf[1024] = {0};
