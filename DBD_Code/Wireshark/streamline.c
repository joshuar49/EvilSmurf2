#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int result;
	const char *filename = "client_and_server_message.pcap";


	result = access(filename, F_OK);
	printf("%d", result);
	
	if(result == 0)
	{
		char command[100];
		char command1[50];
		strcpy(command, "strings client_and_server_message.pcap > output.txt");
		system(command);
		strcpy(command1, "grep 'hello' output.txt");
		system(command1);
	}
	return 0;
}
