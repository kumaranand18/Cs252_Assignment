#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <limits.h>

#define MAX_THREADS 25
#define N 1000000

int mx;

int prime[N];

DWORD WINAPI SieveofEratosthenes()
{
    for (int i = 2; i <= mx; i++)
    {
        if (prime[i] == -1)
        {
            prime[i] = 1;
            for (int j = 2; i * j <= mx; j++)
            {
                prime[i * j] = 0;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    mx = atoi(argv[1]);
    for (int i = 0; i < N; i++)
    {
        prime[i] = -1;
    }
    DWORD ThreadId[MAX_THREADS];
    HANDLE ThreadHandle[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; i++)
    {
        ThreadHandle[i] = CreateThread(
            NULL,
            0,
            SieveofEratosthenes,
            NULL,
            0,
            &ThreadId[i]);
    }
    WaitForMultipleObjects(MAX_THREADS, ThreadHandle, TRUE, INFINITE);
    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(ThreadHandle[i]);
    }

    printf("The prime numbers less than %d are:\n", mx);
    int cnt = 0;
    for (int i = 0; i <= mx; i++)
    {
        if (prime[i] == 1)
        {
            cnt++;
            printf("%d ", i);
        }
    }
    printf("\nTotal number of prime numbers less than %d = %d\n", mx, cnt);
    return 0;
}