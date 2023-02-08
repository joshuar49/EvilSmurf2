#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  //Given wireshark hex values
  char wireshark[50] = "68 65 6C 6C 6F";

  //Space splits hex string into chunks
  const char splitter[2] = " ";
  char *chunk;

  //List defined for hex values above 10 and up to 16
  char list[7] = {'A','B','C','D','E','F'};

  //Define first chunk
  chunk = strtok(wireshark, splitter);

  //Loops through all chunks in the string
  while (chunk != NULL)
  {
    int hexnum = 0;
    int ascii = 0;
    //printf("%s\n", chunk); DEBUGGING PURPOSES ONLY

    //Indexes through chunks
    for (int i = 0; i < 2; i++)
    {
      //Index through alphabet list
      for (int alpha = 0; alpha < 7; alpha++)
      {
        //Checks if the hex letter is found in the list
        if ((int)chunk[i] == (int)list[alpha])
        {
          //Subtracts 55 from ASCII number to reach hex equivalent
          hexnum = (int)chunk[i] - 55;
          break;
        }
        else
        {
          //Turns character digit into integer
          hexnum = chunk[i] - '0';
        }
      }
      //printf("%d\n", hexnum); DEBUGGING PURPOSES ONLY
      //Character is found using the formula ex. 50 = 5*16^1 + 0*16^0
      ascii += hexnum * pow(16,abs(i-1));
      }
    printf("%c", ascii);
    //Moves to the next chunk
    chunk = strtok(NULL, splitter);
  }
  printf("\n");
  return (0);
}
