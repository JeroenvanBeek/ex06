#define _POSIX_C_SOURCE 199309L // sigaction(), struct sigaction, sigemptyset()
#define  _XOPEN_SOURCE 500      // For S_IFIFO in C99+

#include <stdio.h>          // printf, getchar
#include <string.h>         // memset
#include <signal.h>         // sigaction, sigemptyset, struct sigaction, SIGINT, kill()
#include <unistd.h>         // sleep() 
#include <stdlib.h>         // strtoul(), exit()
#include <sys/stat.h>       // mkfifo()
#include <fcntl.h>          // open(), O_* constants
#include <pthread.h>

#define mySigNr 25

void *ThreadFunction(void *arg);

volatile sig_atomic_t i = 0;
void newHandler();//(int sig);

int killed = 1;
int fd;
int main(void) 
{
  struct sigaction act, oldact;
  
  pthread_t ThreadID_A;

  int arg_P1 = 1;

  // Define SHR:
  memset(&act, '\0', sizeof(act));  // Fill act with NULLs by default
  act.sa_handler = newHandler;      // Set the custom SHR
  act.sa_flags = 0;                 // No flags, used with act.sa_handler
  sigemptyset(&act.sa_mask);        // No signal masking during SHR execution 
  
  // Install SHR:
  sigaction(SIGINT, &act, &oldact);  // This cannot be SIGKILL or SIGSTOP

  printf("Waiting for signal %i.  My PID is %i.\n", mySigNr, getpid() );

  
  unsigned long int PID;
  PID = getpid();
  
  mkfifo("PIDpipe", S_IFIFO|0666);          // Create FIFO; permissions: u/g/o r/w
  fd = open("PIDpipe", O_WRONLY);           // Open FIFO write-only
  write(fd, &PID, sizeof(PID));  // Write message to FIFO
  close(fd);                             // Close FIFO
  //unlink("F

  
  if(pthread_create(&ThreadID_A, NULL, ThreadFunction, (void*) &arg_P1)) 
  {
    fprintf(stderr, "No thread A\n");
    exit(EXIT_FAILURE);
  }
  sleep(1);

  while(i<25); 

  printf("\ncounted 1, %d times.  Press Ctrl-C again to exit.\n", i);
  
  // Restore original SHR:
  sigaction(SIGINT, &oldact, NULL);
  // Wait for Ctrl-C to exit:
  while(1);
  
  return 0;
}

void *ThreadFunction(void *arg) 
{
    int *s_arg= (int*) arg;

    switch(*s_arg)
    {
      case 1:
          printf("\n");
          char message[3] = "1\n";
          for(i = 1; i < 25; ++i)
          { 
          write(O_WRONLY, &message, sizeof(message)); 
          sleep(1);
          }
      break;         // End of thread function
    }
pthread_exit(NULL);
}
// SHR using sa_handler:
void newHandler()
{
    printf("\n Stop thread's\n");
    killed = 0;
}
