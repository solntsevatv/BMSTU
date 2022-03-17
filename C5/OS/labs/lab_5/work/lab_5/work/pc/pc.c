#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <time.h>
#include <wait.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#define N 24
#define MAX_SEMS 3
#define ITERS 8

#define PRODUCE_COUNT 3
#define CONSUME_COUNT 3

#define BIN_SEM 0
#define BUF_FULL 1
#define BUF_EMPTY 2

#define MAX_RAND_PRODUCE 2
#define MAX_RAND_CONSUME 5

typedef char data_t[N];
typedef struct
{
    size_t r_pos;
    size_t w_pos;
    data_t data;
} cbuff_t;

int init_buff(cbuff_t *const buff)
{
    if (!buff)
    {
        return -1;
    }
    memset(buff, 0, sizeof(cbuff_t));

    return 0;
}

int write_buff(cbuff_t *const buff, const char c)
{
    if (!buff)
    {
        return -1;
    }
    buff->data[buff->w_pos++] = c;
    buff->w_pos %= N;

    return 0;
}

int read_buff(cbuff_t *const buff, char *const dst)
{
    if (!buff)
    {
        return -1;
    }
    *dst = buff->data[buff->r_pos++];
    buff->r_pos %= N;

    return 0;
}

struct sembuf PRODUCE_START[2] = {{BUF_EMPTY, -1, 0}, {BIN_SEM, -1, 0}};
struct sembuf PRODUCE_END[2] = {{BUF_FULL, 1, 0}, {BIN_SEM, 1, 0}};

int produce_run(cbuff_t *const buff, const int sem_id, const int produce_id)
{
    if (!buff)
    {
        return -1;
    }

    srand(time(NULL) + produce_id);

    int stime;
    char ch;

    for (size_t i = 0; i < ITERS; ++i)
    {
        stime = rand() % MAX_RAND_PRODUCE + 1;
        sleep(stime);

        if (semop(sem_id, PRODUCE_START, 2) == -1)
        {
            perror("Producer lock error.");

            exit(EXIT_FAILURE);
        }

        ch = 'a' + (char)(buff->w_pos % 26);

        if (write_buff(buff, ch) == -1)
        {
            perror("Buffer write error.");

            return EXIT_FAILURE;
        }
        printf("!Producer #%d wrote: %c // Idle time: %ds\n", produce_id, ch, stime);

        if (semop(sem_id, PRODUCE_END, 2) == -1)
        {
            perror("Producer release error.");

            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

struct sembuf CONSUME_START[2] = {{BUF_FULL, -1, 0}, {BIN_SEM, -1, 0}};
struct sembuf CONSUME_END[2] = {{BUF_EMPTY, 1, 0}, {BIN_SEM, 1, 0}};

int consume_run(cbuff_t *const buff, const int sem_id, const int consume_id)
{
    if (!buff)
    {
        return -1;
    }

    srand(time(NULL) + consume_id + PRODUCE_COUNT);

    int stime;
    char ch;

    for (size_t i = 0; i < ITERS; ++i)
    {
        stime = rand() % MAX_RAND_CONSUME + 1;
        sleep(stime);

        if (semop(sem_id, CONSUME_START, 2) == -1)
        {
            perror("Consumer lock error.");

            exit(EXIT_FAILURE);
        }

        if (read_buff(buff, &ch) == -1)
        {
            perror("Buffer read error.");

            return EXIT_FAILURE;
        }
        printf("?Consumer #%d read:  %c // Idle time: %ds\n", consume_id, ch, stime);

        if (semop(sem_id, CONSUME_END, 2) == -1)
        {
            perror("Consumer release error.");

            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

int main()
{
    setbuf(stdout, NULL);

    int fd = shmget(IPC_PRIVATE, sizeof(cbuff_t), IPC_CREAT | S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd == -1)
    {
        perror("shmget failed.");

        return EXIT_FAILURE;
    }

    cbuff_t *buff = shmat(fd, 0, 0);
    if (buff == (void *)-1)
    {
        perror("shmat failed.");

        return EXIT_FAILURE;
    }

    if (init_buff(buff) == -1)
    {
        perror("Buffer initialization failed.");

        return EXIT_FAILURE;
    }

    int sem_id = semget(IPC_PRIVATE, MAX_SEMS, IPC_CREAT | S_IRWXU | S_IRWXG | S_IRWXO);
    if (sem_id == -1)
    {
        perror("semget failed.");

        return EXIT_FAILURE;
    }

    semctl(sem_id, BIN_SEM, SETVAL, 1);
    semctl(sem_id, BUF_EMPTY, SETVAL, N);
    semctl(sem_id, BUF_FULL, SETVAL, 0);

    int chpid;
    for (size_t i = 0; i < PRODUCE_COUNT; ++i)
    {
        switch ((chpid = fork()))
        {
        case -1:
            perror("Producer fork failed.");

            exit(EXIT_FAILURE);
            break;
        case 0:
            produce_run(buff, sem_id, i);

            return EXIT_SUCCESS;
        }
    }

    for (size_t i = 0; i < CONSUME_COUNT; ++i)
    {
        switch ((chpid = fork()))
        {
        case -1:
            perror("Consumer fork failed.");

            exit(EXIT_FAILURE);
            break;
        case 0:
            consume_run(buff, sem_id, i);
            return EXIT_SUCCESS;
        }
    }

    for (size_t i = 0; i < CONSUME_COUNT + PRODUCE_COUNT; ++i)
    {
        int status;
        if (wait(&status) == -1)
        {
            perror("Child error.");

            exit(EXIT_FAILURE);
        }
        if (!WIFEXITED(status))
        {
            printf("Child process terminated abnormally\n");
        }
    }

    if (shmdt((void *)buff) == -1 ||
        shmctl(fd, IPC_RMID, NULL) == -1 ||
        semctl(sem_id, IPC_RMID, 0) == -1)
    {
        perror("Exit error.");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}