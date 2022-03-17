#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int argc;
    printf("Enter arr len: ");
    scanf("%d", &argc);

    if (argc == 0)
        return 0;
    int *arr = NULL;
    arr = (int*) malloc(sizeof(int) * argc);
    if (arr == NULL)
        return -1;

    if (argc > 1)
        for (int i = 0; i < argc; i++)
            scanf("%d", &arr[i]);
    int min = arr[0];
    int max = arr[0];
    for (int i = 0; i < argc; i++)
    {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }
    printf("max: %d|min: %d\n", max, min);
    free(arr);
    return 0;
}