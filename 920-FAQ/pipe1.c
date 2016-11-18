/* File: pipe1.c
 * Purpose: Basic example of pipe. 
 *          Read and write fixed length records across a pipe.
 *          This is about a simple as they come. */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* pipe */
#include <signal.h>

void Child  (pid_t Handle);
void Parent (pid_t Handle);

int main() {
  pid_t		Pid;
  int 		fd[2];
  pipe(fd); /* Create two file descriptors */
  Pid = fork();
  if ( Pid == 0) { /* Child */
    close(fd[0]);
    Child(fd[1]);
    puts("Child end");
  }
  else {/* Parent. */
    close(fd[1]);
    Parent(fd[0]);
    puts("Parent end");
  }
  return 0;
}

/* The Child sends data to the parent. */
void Child(pid_t Handle)
{
  char Buff[]="Martin 1 abcdefghijklmnop ";
  write(Handle, Buff, strlen(Buff)+1);
  Buff[7] = '2';
  write(Handle, Buff, strlen(Buff)+1);
  Buff[7] = '3';
  write(Handle, Buff, strlen(Buff)+1);
  Buff[7] = '4';
  write(Handle, Buff, strlen(Buff)+1);  
 close(Handle);
}

/* Read the data sent by the child. */
void Parent(pid_t Handle) {
  char Buff[50];
  /* Read EXACTLY the number of bytes sent. 
     0 is returned when the pipe is closed by the child. */
  while (read(Handle,Buff, 27) > 0) {
    printf("%s\n", Buff);
  }
}





