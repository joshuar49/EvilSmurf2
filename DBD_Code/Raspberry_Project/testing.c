#include <stdio.h>
#include <string.h>
#include "scanner.h"

// I need to learn about jag arrays
/*int main()
{
	//char ar1[4][18];
	//int inp;
	char (*str)[18];
	char dest[18];

	for (int i = 0; i < 4;i++){
		printf("enter a string: ");
		scanf("%s",ar1[i]);
		printf("\nhere is what you entered: %s\n", ar1[i]);
	}
	printf("The for loop is finished here is the strings in ar1:\n");
	for (int i = 0; i < 4; i++){
		printf("%s\n", ar1[i]);
	}
	printf("Pick which string you want to choose: \n");
	
	for (int i = 0; i < 4; i++){
		i++;
		printf("%i\t%s\n", i, ar1[i-1]);
		i--;
	}
	printf("Please enter a number from the top!: \n");
	scanf("%i", &inp);

	switch (inp) {
		case 1:
			printf("You have picked the first string: %s\n", ar1[inp-1]);
			break;
		case 2:
			printf("You have picked the second string: %s\n", ar1[inp-1]);
			break;
		case 3:
			printf("You have picked the third string: %s\n", ar1[inp-1]);
			break;
		case 4:
			printf("You have picked the fourth string: %s\n", ar1[inp-1]);
			break;
	}
	printf("End of loop\n");
	
	printf("Calling the bt function!\n");
	str = scanner();
	printf("Printing the string here: %s\n", *str);
	return 0;
}
*/

#include <stdio.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(void) {
    int device;

    // Get the Bluetooth device identifier for the default adapter
    device = hci_get_route(0);

    // Print the device identifier to the console
    printf("Bluetooth device identifier: %d\n", device);

    return 0;
}


/*int main()
{
	int ret = 0;
	int neg = !ret;
	printf("this is the real value of neg: %i\n", neg);
	if (0){
		printf("it worked frfr\n");
	}
	return 0;
}
*/
struct rfcomm_dev_req {
	int16_t		dev_id;
	uint32_t	flags;
	bdaddr_t	src;
	bdaddr_t	dst;
	uint8_t	channel;
};

