#define	VERSION	"0.1"

#define CUSTOM  	0x1
#define READ		0x2
#define WRITE		0x3
#define SEARCH  	0x4
#define LIST    	0x5
#define DDIAL   	0x6
#define INFO    	0x7
#define MESS		0x8
#define SMSL        0x9

#define RFCOMMDEV	"/dev/bluetooth/rfcomm/"
#define DEFAULTPB	"AT+CPBS=\"ME\"\r\n"
#define DEFAULTMS	"AT+CPMS=\"ME\"\r\n"


struct opt {

	int act;			/* action					*/

	char *bd_addr; 		/* bd_addr dst of snarf		*/
	int  channel; 		/* rfcomm channel 			*/
	int mode;           /* SMS mode PDU or Text */
	int type;           /* Type of messages to be displayed */

	char *phonebook;    /* memory storage phonebook	*/
	char *smsbook;
	
	int N_MIN;			/* entry number MIN    		*/
	int N_MAX; 			/* entry number MAX			*/
	char *name;			/* name 					*/

	char *custom_cmd;	 /* custom AT+CMD    		*/

} options;

int device, ctl;

void bt_rfcomm_rel();
void usage(char *);
void parse_rw(struct opt *, char *);

FILE *bt_rfcomm_config();
FILE *bt_rfcomm(int , char *, int );

char *parse(char *);
char *rfcomm_read(FILE *, char *);
char *rfcomm_readsms(FILE *, char *);

int list_cmd(FILE *);
int list_sms(FILE *);
int bluesnarfer(struct opt);
int custom_cmd(FILE *, char *);
int bt_get_remote_name(char *);
int rw_cmd(FILE *, struct opt options);
int rw_sms(FILE *, struct opt options);
int search_cmd(FILE *, struct opt );
int switch_cmd(FILE *, struct opt );
