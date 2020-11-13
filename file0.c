#include <stdio.h>

int main()
{
    for (int i = 0; i < 5; ++i)
    {
        if (i == 4)
            printf("4444422222\n");
        else
        {
            for (int j = 0; j < 4 - i; ++j)
                printf(" ");
            printf("4");
            for (int j = 0; j < 2 * i; ++j)
                printf(" ");        
            printf("2\n");
        }
    }
    return (0);
}