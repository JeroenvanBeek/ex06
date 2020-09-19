#include <stdlib.h>  // strtoul(), exit()
#include <unistd.h>  // sleep()
#include <signal.h>  // kill()
#include <stdio.h>   // printf()
#include <fcntl.h>          // open(), O_* constants


int main(int argc, char *argv[])
{
  int fd;
  unsigned long int PID;

  fd = open("PIDpipe", O_RDONLY);          // Open the FIFO read-only
  read(fd, &PID, sizeof(PID));  // Read from the FIFO
  close(fd);                            // Close the FIFO
  printf("%li\n", PID);              // Print message to screen

  while(1) 
  {
    printf("Proces with PID num =%li will be killed in three seconds\n",PID);
    sleep(3);
    kill(PID, 25);
  }

}



