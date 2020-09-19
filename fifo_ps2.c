#include <stdio.h>          // printf()
#include <unistd.h>         // read(), close()
#include <fcntl.h>          // open(), O_* constants

int main(void) {
  int fd;
  unsigned long int PID;

  fd = open("PIDpipe", O_RDONLY);          // Open the FIFO read-only
  read(fd, &PID, sizeof(PID));  // Read from the FIFO
  close(fd);                            // Close the FIFO
  printf("%li\n", PID);              // Print message to screen
  
  return 0;
}
