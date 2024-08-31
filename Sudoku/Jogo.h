#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>

#define TAMTAB 9

int geraNumRandom();
int checkLinCol(int TAB[TAMTAB][TAMTAB], int posCol, int posLin, int num);
int check3x3(int TAB[TAMTAB][TAMTAB], int posCol, int posLin, int num);
int insereSudoku(int TAB[TAMTAB][TAMTAB], int posCol, int posLin, int num);

int geraNumRandom()
{
    return rand() % 9 + 1;
}

int checkLinCol(int TAB[TAMTAB][TAMTAB], int posCol, int posLin, int num)
{
    for (int i = 0; i < TAMTAB; i++)
    {
        if (TAB[posLin][i] == num || TAB[i][posCol] == num)
            return 0;
    }
    return 1;
}

int check3x3(int TAB[TAMTAB][TAMTAB], int posCol, int posLin, int num)
{
    int linResult, colResult;
    linResult = posLin - (posLin % 3);
    colResult = posCol - (posCol % 3);
    for (int a = 0; a < 3; a++)
    {
        for (int b = 0; b < 3; b++)
        {
            if (TAB[linResult + a][colResult + b] == num)
                return 0;
        }
    }
    return 1;
}

int insereSudoku(int TAB[TAMTAB][TAMTAB], int posCol, int posLin, int num)
{
    if (check3x3(TAB, posCol, posLin, num) && checkLinCol(TAB, posCol, posLin, num))
    {
        return 1;
    }

    return 0;
}

#endif