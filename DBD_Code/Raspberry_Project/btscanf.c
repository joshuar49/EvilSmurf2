#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

char (*scanner())[18];
char addr[8];
char ar1[10][18];
char ar2[10][1024]; // This will be used for the device names 
// but im tempted to just add all this in a "Jaggaed Array"

char (*scanner())[18]
{
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i, inp;
    char name[248];

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    len = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("hci_inquiry");

    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
            name, 0) < 0)
        strcpy(name, "[unknown]");
		strcpy(ar2[i], name);
		strcpy(ar1[i], addr);
		printf("%s  %s\n", addr, name);
    }
	for (int i = 0; i < 10; i++){
		i++;
		printf("%i\t%s\n",i , ar1[i-1]);
		i--;
    }
	printf("Please enter the number of the MAC address you want to pair to:");
	scanf("%i", &inp);
	switch (inp) {
		case 1:
			printf("You have picked the first device: %s\n", ar1[inp-1]);
			break;
		case 2:
			printf("You have picked the second device: %s\n", ar1[inp-1]);
			break;
		case 3:
			printf("You have picked the third device: %s\n", ar1[inp-1]);
			break;
		case 4:
			printf("You have picked the fourth device: %s\n", ar1[inp-1]);
			break;
		case 5:
			printf("You have picked the first device: %s\n", ar1[inp-1]);
			break;
		case 6:
			printf("You have picked the second device: %s\n", ar1[inp-1]);
			break;
		case 7:
			printf("You have picked the third device: %s\n", ar1[inp-1]);
			break;
		case 8:
			printf("You have picked the fourth device: %s\n", ar1[inp-1]);
			break;
		case 9:
			printf("You have picked the first device: %s\n", ar1[inp-1]);
			break;
		case 10:
			printf("You have picked the second device: %s\n", ar1[inp-1]);
			break;	
		default:
			printf("You didnt pick a valid number try again!\n");
	}
	printf("End of loop\n");
	return &ar1[inp-1];
    free(ii);
    close(sock);
}

int main()
{	
	char (*conar1)[18];
	printf("Calling the function\n");
	conar1 = scanner();
	printf("Connecting to: %s\n", *conar1);
	return 0;
}



