// PROGRAMA p6.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
 
int main(void)
{
	pid_t pid;
	int i, j;
	printf("I'm process %d. My parent is %d.\n", getpid(),getppid());
	for (i=1; i<=3; i++) {
		int arg = -1; 
		int status;
		pid = fork();
		if ( pid < 0) {
			printf("fork error");
			exit(1);
		}
		else if (pid == 0) {
			printf("I'm process %d. My parent is %d.I'm going to work for 1 second ...\n",getpid(),getppid());
			sleep(1); // simulando o trabalho do filho
			printf("I'm process %d. My parent is %d. I finished my work\n", getpid(),getppid());
			exit(0);
		}
		else // simulando o trabalho do pai
			for (j=1; j<=10; j++) {
                waitpid(-1, &status, WNOHANG); //checking each second if there's a zombie process
                sleep(1);
                printf("father working ...\n");
		}
	}
	exit(0);
}
