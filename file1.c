#include <stdio.h>
#include <stdlib.h>

int ft_atoi(char *av)
{
    int ret = 0;
    int idx = 0;
    while (av[idx])
    {
        ret *= 10;
        ret += av[idx] - 48;
        ++idx;
    }
    return (ret);
}

int main(int ac, char *av[])
{
    int **map;
    int col = ft_atoi(av[1]);
    int row = ft_atoi(av[2]);
    map = malloc(sizeof(int *) * row);
    for (int i = 0; i < row; ++i) {
        map[i] = malloc(sizeof(int) * col);
        for (int j = 0; j < col; ++j) {
            map[i][j] = 0;
        }
    }
    int x = 0, y = 0, d = 0;
    while (1)
    {
        if (map[x][y] == 1)
            break ;
        map[x][y] = 1;
        if (d == 0) {
            if (x + 1 == row || ((x + 2 < row) && (map[x + 2][y] == 1)))
            {
                if (y + 2 >= col || map[x][y + 2] == 1)
                    break ;
                else {
                    d = 1;
                    ++y;
                }
            }
            else
                ++x;
        }
        else if (d == 1) {
            if (y + 1 == col || ((y + 2 < col) && (map[x][y + 2] == 1)))
            {
                if (x - 2 < 0 || map[x - 2][y] == 1)
                    break ;
                else {
                    d = 2;
                    --x;
                }
            }
            else
                ++y;
        }
        else if (d == 2) {
            if (x == 0 || (x > 1 && (map[x - 2][y] == 1)))
            {
                if (y - 2 < 0 || map[x][y - 2] == 1)
                    break ;
                else {
                    d = 3;
                    --y;
                }
            }
            else
                --x;
        }
        else if (d == 3) {
            if (y == 0 || (y > 1 && (map[x][y - 2] == 1)))
            {
                if (x + 2 >= row || map[x + 2][y] == 1)
                    break ;
                else {
                    d = 0;
                    ++x;
                }
            }
            else
                --y;
        }
        if (d % 2 == 1 && x > 0 && map[x - 1][y] == 1)
            break ;
        if (d % 2 == 0 && y + 1 < col && map[x][y + 1] == 1)
            break ;
        if (d % 2 == 1 && x + 1 < row && map[x + 1][y] == 1)
            break ;
        if (d % 2 == 0 && y > 0 && map[x][y - 1] == 1)
            break ;
    }
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            printf("%s", (map[i][j] == 1) ? "*" : " ");
        printf("\n");
    }
    for (int i = 0; i < row; ++i)
        free(map[i]);
    free(map);
    return (0);
}