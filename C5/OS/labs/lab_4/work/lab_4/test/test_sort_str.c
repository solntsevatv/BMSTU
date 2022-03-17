#include <stdlib.h>
#include <stdio.h>

int main()
{
    char argv[100] = {0};
    printf("Enter str: ");
    scanf("%s", argv);
    int len = 0;
    while (argv[len] != '\0')
    {
        len++;
    }
    
    char sorted[100] = {0};
    for (int i = 0; i < len; i++)
        sorted[i] = argv[i];
    char buff;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            if (sorted[j] > sorted[j + 1])
            {
                buff = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = buff;
            }
        }
    }
    printf("original: %s|sorted: %s\n", argv, sorted);
    return 0;
}