#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#define TYPES ".pcap"

int main(){

    DIR *f_info;
    struct dirent *in_dir;
    int num_f = 0;
	char* dir_name;

    //Open desired directory
	printf("Please enter your directory path that holds all your .pcap files: \n");
	scanf("%s", dir_name);
    f_info = opendir(dir_name);

    //Exception for no-existent directory
    if (f_info == NULL){
        perror("Cannot find directory");
        return (1);
    }

    //Looping through files in directory 
    while ((in_dir = readdir(f_info))){
        if(strstr(in_dir->d_name, TYPES)){
            num_f++;
            printf("%1d: %s\n",num_f, in_dir->d_name);
            return(0);
        }
    }
}
