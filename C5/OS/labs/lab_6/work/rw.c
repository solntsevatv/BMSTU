#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TIMEOUT_DIFF 4000

#define READ_TIMEOUT 200
#define WRITE_TIMEOUT 200

#define READERS_COUNT 5
#define WRITERS_COUNT 3

#define READ_ITERS 5
#define WRITE_ITERS 5

HANDLE mutex;
HANDLE can_read;
HANDLE can_write;

bool active_writer = false;

LONG waiting_writers = 0;
LONG waiting_readers = 0;
LONG active_readers = 0;

int value = 0;

void start_write(void)
{
    InterlockedIncrement(&waiting_writers);

    if (active_writer || active_readers > 0)
        WaitForSingleObject(can_write, INFINITE);

    InterlockedDecrement(&waiting_writers);

    active_writer = true;
}

void stop_write(void)
{
    active_writer = false;

    if (waiting_readers)
        SetEvent(can_read);
    else
        SetEvent(can_write);
}

void start_read()
{
    InterlockedIncrement(&waiting_readers);

    if (active_writer || (WaitForSingleObject(can_write, 0) == WAIT_OBJECT_0 && waiting_writers))
        WaitForSingleObject(can_read, INFINITE);

    WaitForSingleObject(mutex, INFINITE);

    InterlockedDecrement(&waiting_readers);
    InterlockedIncrement(&active_readers);

    SetEvent(can_read);
    ReleaseMutex(mutex);
}

void stop_read()
{
    InterlockedDecrement(&active_readers);

    if (active_readers == 0)
    {
        ResetEvent(can_read);
        SetEvent(can_write);
    }
}

DWORD WINAPI reader_run(CONST LPVOID lpParams)
{
    int reader_id = (int)lpParams;
    srand(time(NULL) + reader_id);

    int sleep_time;

    for (size_t i = 0; i < READ_ITERS; i++)
    {
        sleep_time = READ_TIMEOUT + rand() % TIMEOUT_DIFF;
        Sleep(sleep_time);

        start_read();
        printf("reader %d read: %3d | time: %dms\n", reader_id, value, sleep_time);
        stop_read();
    }
    return 0;
}

DWORD WINAPI writer_run(CONST LPVOID lpParams)
{
    int writer_id = (int)lpParams;
    srand(time(NULL) + writer_id + READERS_COUNT);

    int sleep_time;

    for (size_t i = 0; i < WRITE_ITERS; ++i)
    {
        sleep_time = WRITE_TIMEOUT + rand() % TIMEOUT_DIFF;
        Sleep(sleep_time);

        start_write();
        ++value;
        printf("writer %d wrote: %3d | time: %dms\n", writer_id, value, sleep_time);
        stop_write();
    }
    return 0;
}

int main()
{
    setbuf(stdout, NULL);

    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL)
        return -1;

    can_read = CreateEvent(NULL, TRUE, FALSE, NULL);
    can_write = CreateEvent(NULL, FALSE, FALSE, NULL);

    if (can_read == NULL || can_write == NULL)
        return -1;

    HANDLE readers_threads[READERS_COUNT];
    HANDLE writers_threads[WRITERS_COUNT];

    for (size_t i = 0; i < READERS_COUNT; ++i)
    {
        readers_threads[i] = CreateThread(NULL, 0, reader_run, (LPVOID)i, 0, NULL);
        if (readers_threads[i] == NULL)
            return -1;
    }

    for (size_t i = 0; i < WRITERS_COUNT; ++i)
    {
        writers_threads[i] = CreateThread(NULL, 0, writer_run, (LPVOID)i, 0, NULL);
        if (writers_threads[i] == NULL)
            return -1;
    }

    WaitForMultipleObjects(READERS_COUNT, readers_threads, TRUE, INFINITE);
    WaitForMultipleObjects(WRITERS_COUNT, writers_threads, TRUE, INFINITE);

    CloseHandle(mutex);
    CloseHandle(can_read);
    CloseHandle(can_write);

    return 0;
}