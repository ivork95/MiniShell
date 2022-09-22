#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int _) {
  (void)_;
  printf("\nEnter a number:1 ");
  fflush(stdout);
}
int main(void) {

  pid_t pid;

  pid = fork();
  int n = 0;

  if (pid < 0) {
    perror("Can't fork");
  } else if (pid == 0) {
    // Child process
    kill(getpid(), SIGKILL); // Killing the child process as we don't need it
    printf("child process\n");
  } else {
    // Parent process
    struct sigaction sg;
    sg.sa_flags = SA_RESTART;
    sg.sa_handler = handler;
    sigaction(SIGINT, &sg, NULL);
    printf("Enter a number: ");
    scanf("%d", &n);
  }
  printf("Value of n = %d", n);

  return 0;
}