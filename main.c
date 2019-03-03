#include <stdio.h>
#include <stdlib.h>
#include "functii_sudoku.h"

int main()
{
    int **matrix,i,j,nr_joc;
    char dump_string[100]; // sir de caractere folosit pt a citi din fisier pana ajung
                           //la sudoku pe care trebuie sa il rezolv
    FILE *ModelSudoku=fopen("Modele Sudoku.txt","r"), *RezolvareSudoku=fopen("Rezolvari Sudoku.txt","w");
    matrix=calloc(9,sizeof(int));
    for (i=0;i<9; i++)
        matrix[i]=calloc(9,sizeof(int));
    printf("Ce joc doriti sa fie rezolvat? Introduceti un numar in intervalul 1-50: ");
    scanf("%d",&nr_joc);
    while (nr_joc<1 || nr_joc>50)
    {
        printf("\nVa rog introduceti un numar de joc din intervalul 1-50: ");
        scanf("%d",&nr_joc);
    }
    for (i=0;i<nr_joc*2+(nr_joc-1)*9+(nr_joc-1);i++)
        fgets(dump_string, sizeof(dump_string),ModelSudoku);
    for (i=0;i<9;i++)
        for (j=0;j<9;j++)
        fscanf(ModelSudoku,"%d ",&matrix[i][j]);
    solve_sudoku(matrix,0,0);
    if (check_square_rows(matrix)==1 && check_square_cols(matrix)==1)
    {
    //show_matrix(matrix);
    show_matrix_file(matrix,RezolvareSudoku);
    }
    else printf("\n\nModelul de sudoku nu poate fi rezolvat!");
    fclose(ModelSudoku);
    fclose(RezolvareSudoku);
    return 0;
}
