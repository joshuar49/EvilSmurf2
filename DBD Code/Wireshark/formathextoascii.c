#include <stdio.h>

#include <stdlib.h>


char hexToAscii(char first, char second)

{

    char hex[5], *stop;

    hex[0] = '0';

    hex[1] = 'x';

    hex[2] = first;

    hex[3] = second;

    hex[4] = '\0';

    return (char)strtol(hex, &stop, 16);

}


int main(void)

{

    char c = hexToAscii('4', '2');

    printf("%c\n", c);

    return 0;

}
