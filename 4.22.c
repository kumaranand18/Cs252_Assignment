#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <limits.h>

double avg = 0;
int max = INT_MIN;
int min = INT_MAX;
double median = 0;
double standardDeviation = 0;

void avgFunc(int *arr)
{
    int len = *arr;
    int sum = 0;

    for (int i = 1; i <= len; i++)
    {
        sum += *(arr + i);
    }

    avg = ((double)sum) / len;
    printf("Average = %lf\n", avg);
}

void maxFunc(int *arr)
{
    int len = *arr;

    for (int i = 1; i <= len; i++)
    {
        max = max > *(arr + i) ? max : *(arr + i);
    }

    printf("Maximum = %d\n", max);
}

void minFunc(int *arr)
{
    int len = *arr;

    for (int i = 1; i <= len; i++)
    {
        min = min < *(arr + i) ? min : *(arr + i);
    }

    printf("Minimum = %d\n", min);
}

void medianFunc(int *arr)
{
    int len = *arr;
    int temp;

    for (int i = len; i >= 1; i--)
    {
        for (int j = 1; j < i; j++)
        {
            if (*(arr + j) > *(arr + i))
            {
                temp = *(arr + i);
                *(arr + i) = *(arr + j);
                *(arr + j) = temp;
            }
        }
    }

    if (len % 2)
    {
        median = *(arr + (int)(len + 1) / 2);
    }
    else
    {
        median = (double)(*(arr + (int)len / 2) + *(arr + (int)len / 2 + 1)) / 2;
    }

    printf("Median = %lf\n", median);
}

void standardDeviationFunc(int *arr)
{
    int len = *arr;
    double Var = 0;

    for (int i = 1; i <= len; i++)
    {
        Var += pow((avg - (double)*(arr + i)), 2);
    }

    standardDeviation = sqrt(Var / len);
    printf("Standard deviation = %.4lf\n", standardDeviation);
}

int main(int argc, char *argv[])
{
    DWORD ThreadId[5];
    HANDLE ThreadHandle[5];
    int *arr = (int *)malloc(argc * sizeof(int));

    // arr(0) stores the size of the given array
    *arr = argc - 1;
    for (int i = 1; i < argc; i++)
    {
        *(arr + i) = atoi(argv[i]);
    }

    ThreadHandle[0] = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)*avgFunc,
        arr,
        0,
        &ThreadId[0]);

    ThreadHandle[1] = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)*maxFunc,
        arr,
        0,
        &ThreadId[1]);

    ThreadHandle[2] = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)*minFunc,
        arr,
        0,
        &ThreadId[2]);

    ThreadHandle[3] = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)*medianFunc,
        arr,
        0,
        &ThreadId[3]);

    ThreadHandle[4] = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)*standardDeviationFunc,
        arr,
        0,
        &ThreadId[4]);

    WaitForMultipleObjects(5, ThreadHandle, TRUE, INFINITE);
    CloseHandle(ThreadHandle[0]);
    CloseHandle(ThreadHandle[1]);
    CloseHandle(ThreadHandle[2]);
    CloseHandle(ThreadHandle[3]);
    CloseHandle(ThreadHandle[4]);

    return 0;
}