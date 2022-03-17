#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLEEP_TIME 2

int pid;
int child_pid_1;
int child_pid_2;

int main(void)
{
    printf("Parent process|pid: %d|group: %d\n", getpid(), getpgrp());

    child_pid_1 = fork();
    if (child_pid_1 == -1)
    {
        perror("Error: fork cannot be executed!");
        return 1;
    }
    else if (child_pid_1 == 0)
    {
        sleep(SLEEP_TIME);
        printf("Child №1 process|pid: %d|ppid: %d|group: %d\n", getpid(), getppid(), getpgrp());
        exit(0);
    }

    child_pid_2 = fork();
    if (child_pid_2 == -1)
    {
        perror("Error: fork cannot be executed!");
        return 1;
    }
    else if (child_pid_2 == 0)
    {
        sleep(SLEEP_TIME);
        printf("Child №2 process|pid: %d|ppid: %d|group: %d\n", getpid(), getppid(), getpgrp());
        exit(0);
    }
    printf("Child PIDs of parent process|child №1: %d|child №2: %d\n", child_pid_1, child_pid_1);
    printf("End of parent process\n");
    return 0;
}