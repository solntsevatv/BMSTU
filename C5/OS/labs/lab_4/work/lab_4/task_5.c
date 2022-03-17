#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pid;
int child_pid_1;
int child_pid_2;

int flag = 0;

void signal_handler(int signal) {flag = 1;}

int main(void)
{
    printf("Parent process|pid: %d|group: %d\n", getpid(), getpgrp());
    int message_pipe[2];
    if (pipe(message_pipe) == -1)
    {
        perror("Error: pipe cannot be executed!");
        return 1;
    }

    signal(SIGINT, signal_handler);

    child_pid_1 = fork();
    if (child_pid_1 == -1)
    {
        perror("Error: fork cannot be executed!");
        return 1;
    }
    else if (child_pid_1 == 0)
    {
        sleep(1);
        if (flag)
        {
            printf("Child №1 process|pid: %d|ppid: %d|group: %d\n", getpid(), getppid(), getpgrp());
            close(message_pipe[0]);
            write(message_pipe[1], "XXXXXXX", strlen("XXXXXXX") + 1);
        }
        else
        {
            printf("No signal was sent\n");
        }
        return 0;
    }

    child_pid_2 = fork();
    if (child_pid_2 == -1)
    {
        perror("Error: fork cannot be executed!");
        return 1;
    }
    else if (child_pid_2 == 0)
    {
        sleep(1);
        if (flag)
        {
            printf("Child №2 process|pid: %d|ppid: %d|group: %d\n", getpid(), getppid(), getpgrp());
            close(message_pipe[0]);
            write(message_pipe[1], "aaa", strlen("aaa") + 1);
        }
        else
        {
            printf("No signal was sent\n");
        }
        return 0;
    }

    int return_status[2];
    pid_t child_pid[2];
    for (int i = 0; i < 2; i++)
    {
        child_pid[i] = wait(&(return_status[i]));
        printf("Child process finished|pid = %d|status = %d\n", child_pid[i], return_status[i]);
        int status_value;
        if (WIFEXITED(status_value))
        {
            printf("Child process exited succesfully with code %d\n", WEXITSTATUS(status_value));
        }
    }

    close(message_pipe[1]);

    char read_symb = '0';    
    char buff_1[20] = {0};

    int str_index = 0;
    while (read_symb != '\0' && str_index < 20 && read(message_pipe[0], &read_symb, 1) > 0)
    {
        buff_1[str_index] = read_symb;
        str_index++;
    }

    printf("Received message from pipe: %s\n", buff_1);
    memset(buff_1, '\0', 20 && str_index < 20);

    str_index = 0;
    read_symb = '0';
    while (read_symb != '\0' && str_index < 20 && read(message_pipe[0], &read_symb, 1) > 0)
    {
        buff_1[str_index] = read_symb;
        str_index++;
    }

    printf("Received message from pipe: %s\n", buff_1);
    memset(buff_1, '\0', 20);

    str_index = 0;
    read_symb = '0';
    while (read_symb != '\0' && str_index < 20 && read(message_pipe[0], &read_symb, 1) > 0)
    {
        buff_1[str_index] = read_symb;
        str_index++;
    }

    printf("Received message from pipe: %s\n", buff_1);

    printf("End of parent process\n");
    return 0;
}