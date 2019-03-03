/** Afisarea matricei de sudoku (in consola) **/

int show_matrix (int **matrix)
{
    int i,j,k;
    for (i=0; i<9; i++) //parcurge linia
    {
        for (k=0; k<9; k++) // parcurgere pentru afisarea conturului
        {
            if (k<8) printf("----");
            else printf("-----"); // if-ul a fost scris pentru un aspect decent
        }
        printf("\n");
        for (j=0; j<9; j++)
        {
            if (j==0) printf("|"); // inainte de primul element, pentru contur stanga
            printf(" %d |",matrix[i][j]);
            if (i==8 && j==8)
            {
                printf("\n");
                for (k=0; k<9; k++)
                {
                    if (k<8) printf("----");
                    else printf("-----");
                }
            }
        }
        printf("\n");
    }
}


/**Afisarea matricei de sudoku (in fisier text)**/

int show_matrix_file (int **matrix,FILE *RezolvareSudoku)
{
    int i,j,k;
    for (i=0; i<9; i++)
    {
        for (k=0; k<9; k++)
        {
            if (k<8) fprintf(RezolvareSudoku,"----");
            else fprintf(RezolvareSudoku,"-----");
        }
        fprintf(RezolvareSudoku,"\n");
        for (j=0; j<9; j++)
        {
            if (j==0) fprintf(RezolvareSudoku,"|");
            fprintf(RezolvareSudoku," %d |",matrix[i][j]);
            if (i==8 && j==8)
            {
                fprintf(RezolvareSudoku,"\n");
                for (k=0; k<9; k++)
                {
                    if (k<8) fprintf(RezolvareSudoku,"----");
                    else fprintf(RezolvareSudoku,"-----");
                }
            }
        }
        fprintf(RezolvareSudoku,"\n");
    }
}

/**Functie de verificare pe o linie **/

int check_row (int **matrix, int number, int row)
{
    int i;
    for (i=0; i<9; i++)
            if (matrix[row][i]==number)
                return 0;
    return 1;
}


/** Functie de verificare pe o coloana **/

int check_col (int **matrix, int number, int col)
{
    int i;
    for (i=0; i<9; i++)
            if (matrix[i][col]==number)
                return 0;
    return 1;
}




/** Functie de verificare a unui patrat 3x3 **/

/*Avem nevoie si de o functie de verificare a unui patrat de 3x3
pentru ca exista cazuri in care numerele nu se vor duplica pe linii
si/sau pe coloane, dar pot exista duplicate ale acelorasi numere in
patratul de 3x3 in care se afla pe tabla de joc.*/


int check_square (int **matrix, int row, int col, int number)
{
    int RowStart=(row/3)*3, ColStart=(col/3)*3, i,j; //aflu in ce patrat de 3/3 ma aflu
    for (i=RowStart; i<RowStart+3; i++)
        for (j=ColStart; j<ColStart+3; j++) //parcurg patratul
        {
            if (!(i==row && j==col))  // nu mai verifiv umarulpe care l am pus deja in matrice, totul in afara de el
                if (matrix[i][j]==number) return 0;
        }
    return 1;
}

/** Functie pentru manipularea rezultatelor celor 3 verificari ale conditiilor
necesare pentru un joc corect. (E mai usor sa scrii o singura functie decat 3) **/

int check_board (int **matrix, int row, int col, int number) //pentru a avea mai putine linii de cod, le am strans pe toate pentru a le verifica
{
    if (check_col(matrix,number,col)==1 && check_row(matrix,number,row)==1 && check_square(matrix,row,col,number)==1)
        return 1;
    else return 0;
}


/**Rezolva sudoku **/

int solve_sudoku (int **matrix, int row, int col)
{
    int i;
    if (row<9 && col<9)
    {
        if (matrix[row][col]!=0)
        {
            if ((col+1)<9) return solve_sudoku(matrix,row,col+1); //recursiv apele funtia in care ma aflu
            else if ((row+1)<9) return solve_sudoku(matrix,row+1,0);
            else return 1;
        }
        else
        {
            for (i=0;i<9;i++)
            {
                if (check_board(matrix,row,col,i+1)) //
                {
                    matrix[row][col]=i+1;
                    if ((col+1)<9)
                    {
                        if (solve_sudoku(matrix,row,col+1)) return 1; //daca e ok valoarea alea merge mai departe, daca nu imi cauata alta valoare
                        else matrix[row][col]=0;
                    }
                    else if ((row+1)<9)
                    {
                        if (solve_sudoku(matrix,row+1,0)) return 1;
                        else matrix[row][col]=0;
                    }
                    else return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}

int check_square_rows (int **matrix)
{
    int row,col,row_checker[9]={0}; // am folosit vector de frecventa
    row=0;
    while (row<9)
    {
    for (col=0;col<9;col++)
        row_checker[matrix[row][col]-1]++;
    for (col=0;col<9;col++)
        if (row_checker[col]!=1) return 0;
    row++;
    for (col=0;col<9;col++)
        row_checker[col]=0;
    }
    return 1;
}

int check_square_cols (int **matrix)
{
    int row,col,col_checker[9]={0};
    col=0;
    while (col<9)
    {
    for (row=0;row<9;row++) //nr de aparitii
        col_checker[matrix[row][col]-1]++;
    for (row=0;row<9;row++) //verific vectorul de frecventa sa aibe o singura aparitie
        if (col_checker[row]!=1) return 0;
    col++;
    for (row=0;row<9;row++)
        col_checker[row]=0;
    }
    return 1; //daca a fost totul ok, se pune 0 pe vectorul de fecventa ca sa pregatesc pt urmatoarea verficare
}
