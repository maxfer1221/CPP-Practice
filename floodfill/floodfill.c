// #include <stdio.h>

// int main(){
//     char tmp[4];
//     scanf("%s", tmp);

// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_stars(int rows, int columns);
// void flood_fill(char **array, int row, int col);
void find_neighbours(char **array, int x, int y);

int main()
{

    int rows;
    int columns;

    while (1)
    {
        scanf("%d", &rows);
        scanf("%d", &columns);

        // printf("%i", find_stars(rows, columns));
    }
}

void find_neighbours(char **array, int row, int col)
{
    array[row][col] = '#';

    int **pn = (int **)malloc(4 * sizeof(int **));
    int **neighbours = (int **)malloc(4 * sizeof(int **));
    for (int i = 0; i < 4; i++)
    {
        pn[i] = (int *)malloc(2 * sizeof(int *));
        neighbours[i] = (int *)malloc(2 * sizeof(int *));
    }

    pn[0][0] = row + 1;
    pn[0][1] = col;

    pn[1][0] = row;
    pn[1][1] = col + 1;

    for (int i = 2; i < 4; i++)
    {
        pn[i][0] = row;
        pn[i][1] = col;
    }
    if (row > 0)
    {
        pn[2][0] = row - 1;
        pn[2][1] = col;
    }
    if (col > 0)
    {
        pn[3][0] = row;
        pn[3][1] = col - 1;
    }

    int count = 0;

    for (int i = 0; i < 4; i++)
    {
        int r = pn[i][0];
        int c = pn[i][1];
        if (array[r][c] == '-')
        {
            neighbours[count][0] = r;
            neighbours[count][1] = c;
            count++;
        }
    }

    neighbours = realloc(neighbours, count * sizeof(int **));

    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         printf("%c ", array[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    for (int i = 0; i < count; i++)
    {
        find_neighbours(array, neighbours[i][0], neighbours[i][1]);
    }

    // check surrounding cells to see if they have the same value

    //recursives
}

int find_stars(int rows, int columns)
{
    char **array = (char **)malloc((rows + 1) * sizeof(char **));
    for (int i = 0; i < rows + 1; i++)
    {
        array[i] = (char *)malloc((columns + 1) * sizeof(char *));
    }
    // char tempStr[columns + 1];
    // char *tempStr = (char *)calloc(columns + 1, sizeof(char *));

    // char *array[rows + 1][columns + 1];

    for (int i = 0; i < rows; i++)
    {
        scanf("%s", array[i]);
        //strcpy(*(array + i), tempstr);
        // strcpy(array[i], tempStr);
    }

    char *str = "###";

    // strcpy(array[rows], *str);

    int star_count = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (array[i][j] == '-')
            {
                find_neighbours(array, i, j);
                star_count++;
            }
        }
    }

    return star_count;
}
