//
// Created by maruba on 11/03/20.
//

//
// Created by maruba on 11/03/20.
//

// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>
void sigint_handler(int signo)
{
    printf("In SIGINT handler ...\n");
}

int main(void)
{
    struct tms s;
    clock_t start, end;
    struct sigaction act;
    sigset_t mask;
    if (sigemptyset(&mask) < 0){
        printf("sigempty error\n");
        exit(1);
    }
    act.sa_handler = sigint_handler;
    struct sigaction old;
    double ticks = sysconf(_SC_CLK_TCK);
    if (sigaction(SIGINT, &act, NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }
    printf("Sleeping for 30 seconds ...\n");
    start = times(&s);
    end = times(&s);
    while ((double)(end-start)/ticks < 30){
        sleep(1);
        end = times(&s);
    }

    printf("Waking up ...\n");
    exit(0);
}


