#include <stdio.h>
#include "Desenhos.h"
#include "Jogo.h"

#define TAMTAB 9

int backSudoku(int sudoku[TAMTAB][TAMTAB]);
int brincaSu();
int jogar(int tab[TAMTAB][TAMTAB], int tab2[TAMTAB][TAMTAB]);
int newGame(int tab[TAMTAB][TAMTAB], int tab2[TAMTAB][TAMTAB]);

int backSudoku(int sudoku[TAMTAB][TAMTAB])
{
    int linha, coluna;

    int faltaCelula = 0;
    for (linha = 0; linha < TAMTAB; linha++)
    {
        for (coluna = 0; coluna < TAMTAB; coluna++)
        {
            if (sudoku[linha][coluna] == 0)
            {
                faltaCelula = 1;
                break;
            }
        }
        if (faltaCelula)
            break;
    }
    if (!faltaCelula)
    {
        return 1;
    }

    for (int numero = 1; numero <= TAMTAB; numero++)
    {
        // printf("teste");
        if (insereSudoku(sudoku, coluna, linha, numero))
        {
            sudoku[linha][coluna] = numero;
            // Recursão para resolver outras células
            if (backSudoku(sudoku))
            {
                return 1;
            }
            sudoku[linha][coluna] = 0;
        }
    }
    return 0;
}

int brincaSu()
{
    int tab[TAMTAB][TAMTAB] =
        {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        };

    if (backSudoku(tab))
    {
        printf("Sudoku resolvido\n");
        desenhaSudoku(tab);
    }
    else
    {
        printf("Nao foi possivel resolver\n");
    }
    return 1;
};

int jogar(int tab[TAMTAB][TAMTAB], int tab2[TAMTAB][TAMTAB])
{
    int numero, posCol, posLin;

    newGame(tab, tab2);
    do
    {
        desenhaSudoku(tab2);

        gotoxy(30, 32);
        printf("Numero: ");
        scanf("%d", &numero);

        gotoxy(60, 32);
        printf("linha: ");
        scanf("%d", &posLin);

        gotoxy(90, 32);
        printf("coluna: ");
        scanf("%d", &posCol);

        if (tab[posLin - 1][posCol - 1] == numero)
        {
            tab2[posLin - 1][posCol - 1] = numero;
        }
        else
        {
            gotoxy(50, 30);
            printf("---NAO FOI POSSIVEL INSERIR O NUMERO---");
            Sleep(400);
        }

        system("cls");

    } while (numero != -1 && confereSudoku(tab2));
}

int newGame(int tab[TAMTAB][TAMTAB], int tab2[TAMTAB][TAMTAB])
{

    srand((unsigned)time(NULL));

    int numero, posCol, posLin, verificado;
    int possivel = 1;
    do
    {
        for (int a = 0; a < TAMTAB; a++)
        {
            for (int b = 0; b < TAMTAB; b++)
            {
                tab[a][b] = 0;
            }
        }
        for (int a = 0; a < 20;)
        {

            numero = geraNumRandom();
            posLin = geraNumRandom();
            posCol = geraNumRandom();

            verificado = insereSudoku(tab, posCol - 1, posLin - 1, numero);
            if (verificado && numero > 0 && numero < 10 && tab[posLin][posCol] == 0)
            {
                a++;
                tab[posLin - 1][posCol - 1] = numero;
            }

            for (int a = 0; a < TAMTAB; a++)
            {
                for (int b = 0; b < TAMTAB; b++)
                {
                    tab2[a][b] = tab[a][b];
                }
            }
        }
        if (backSudoku(tab))
        {
            possivel = 0;
        }
    } while (possivel);
    return 1;
}

int main()
{

    int tab[TAMTAB][TAMTAB];
    int tabJogo[TAMTAB][TAMTAB];
    memset(tab, 0, sizeof(tab));
    memset(tabJogo, 0, sizeof(tabJogo));

    system("mode con:cols=130 lines=35"); // Controlar tamanho do cmd

    int verificador = 0, menu = 0;
    do
    {
        menu = Menu_Desenho();
        switch (menu)
        {
        case 1:
            jogar(tab, tabJogo);
            break;
        case 2:
            comoJogar();
            break;
        case 3:
            do
            {
                if (newGame(tab, tabJogo))
                {
                    verificador = 1;
                }
                else
                {
                    memset(tab, 0, sizeof(tab));
                }

            } while (!verificador);
            desenha2Sudoku(tabJogo,tab);
            getch();
            break;
        default:
            break;
        }
    } while (menu != 4);

    getch();
    return 0;
}