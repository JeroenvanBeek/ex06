#include <stdlib.h>  // strtoul(), exit()
#include <unistd.h>  // sleep()
#include <signal.h>  // kill()
#include <stdio.h>   // printf()


int main(int argc, char *argv[])
{
  unsigned long int PID;
  PID = strtoul(argv[1], NULL, 10);
  
  if(argc != 2) 
  {
    printf("Please give the PID of the receiving process as an argument.\n");
    exit(1);
  }

  while(1) 
  {
    printf("Proces with PID num =%li will be killed in three seconds\n",PID);
    sleep(3);
    kill(PID, 25);
  }

}



