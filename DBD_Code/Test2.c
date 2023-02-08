#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#List of possible libraries that could be used


int main(int argc, char **argv){
  
  #method that can be used to get id of connected devices
  Id_of_d = hci_get_route(NULL);  
  
  #Opens a socket given a port number
  bluSock = hci_open_dev( dev_id );

  #variables neeeded for time of scans and quantityt along with flags.
  
  free();
  close();
  return 0;
}


