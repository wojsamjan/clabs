/* File: pipe2.c
 * Purpose: Basic example of pipe. 
 *          Read and write variable length records across a pipe.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* pipe */
#include <signal.h>

void Child  (pid_t Handle);
void Parent (pid_t Handle);

int main() {
  pid_t		Pid;
  int 		fd[2];
  pipe(fd); /* Create two file descriptors  */
  Pid = fork();
  if ( Pid == 0) { /* Child */
    close(fd[0]);
    Child(fd[1]);
    puts("Child end");
  }
  else { /* Parent */
    close(fd[1]);
    Parent(fd[0]);
    puts("Parent end");
  }
  return 0;
}

/* The Child sends data to the parent. */
void Child(pid_t Handle) {
  int Len;
  char Buff[50]="Bass Beer";

  Len = strlen(Buff)+1;
  write(Handle, &Len, sizeof(Len));
  write(Handle, Buff, Len);

  strcpy(Buff, "Wild times.");
  Len = strlen(Buff)+1;
  write(Handle, &Len, sizeof(Len));
  write(Handle, Buff, Len);

  strcpy(Buff, "Alex was ere.");
  Len = strlen(Buff)+1;
  write(Handle, &Len, sizeof(Len));
  write(Handle, Buff, Len);

  strcpy(Buff, "Bon Jovi rules the world.");
  Len = strlen(Buff)+1;
  write(Handle, &Len, sizeof(Len));
  write(Handle, Buff, Len);  
  
  close(Handle);
}

/* Read the data sent by the child. */
void Parent(pid_t Handle) {
  int		Len;
  char 		Buff[50];
  /* Perform two reads. THe first gets the length of the data
     the second gets the actual data.			*/
  while (read(Handle, &Len, sizeof(Len)) > 0) {
    read(Handle,Buff, Len);
    printf("%s\n", Buff);
  }
}
