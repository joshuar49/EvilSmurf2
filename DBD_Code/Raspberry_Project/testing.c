#include <stdio.h>
#include <string.h>

int main()
{
	char ar1[4][18];

	for (int i = 0; i < 4;i++){
		printf("enter a string: ");
		scanf("%s",ar1[i]);
		printf("\nhere is what you entered: %s\n", ar1[i]);
	}
	printf("The for loop is finished here is the strings in ar1:\n");
	for (int i = 0; i < 4; i++){
		printf("%s\n", ar1[i]);
	}
	printf("End of loop\n");
	return 0;
}

