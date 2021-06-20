/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku() {
    this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lan�a excep��o IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9]) {
    this->initialize();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (nums[i][j] != 0) {
                int n = nums[i][j];
                numbers[i][j] = n;
                lineHasNumber[i][n] = true;
                columnHasNumber[j][n] = true;
                block3x3HasNumber[i / 3][j / 3][n] = true;
                countFilled++;
            }
        }
    }
}

void Sudoku::initialize() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int n = 0; n < 10; n++) {
                numbers[i][j] = 0;
                lineHasNumber[i][n] = false;
                columnHasNumber[j][n] = false;
                block3x3HasNumber[i / 3][j / 3][n] = false;
            }
        }
    }

    this->countFilled = 0;
}

/**
 * Obtem o conte�do actual (s� para leitura!).
 */
int **Sudoku::getNumbers() {
    int **ret = new int *[9];

    for (int i = 0; i < 9; i++) {
        ret[i] = new int[9];

        for (int a = 0; a < 9; a++)
            ret[i][a] = numbers[i][a];
    }

    return ret;
}

/**
 * Verifica se o Sudoku j� est� completamente resolvido
 */
bool Sudoku::isComplete() {
    return countFilled == 9 * 9;
}


/**
 * Resolve o Sudoku.
 * Retorna indica��o de sucesso ou insucesso (sudoku imposs�vel).
 */
bool Sudoku::solve() {
    //check column and line with less numbers

    return auxSolve(0, 0);
}

bool Sudoku::auxSolve(int x, int y) {
    if (isComplete()) return true;
    if (x > 9) return false;                    //end of the sudoku and didn't finished
    if (y >= 9) return auxSolve(x + 1, 0);      //next line
    if (numbers[x][y] != 0) return auxSolve(x, y + 1);  //nothing to do

    for (int i = 1; i < 10; i++) {
        if (checkValue(x, y, i)) numbers[x][y] = i; //checknumber
        else continue;                              //not valid number
        if (auxSolve(x, y + 1)) return true;
        else {                                       //new try
            lineHasNumber[x][i] = false;
            columnHasNumber[y][i] = false;
            block3x3HasNumber[x / 3][y / 3][i] = false;
            numbers[x][y] = 0;
            countFilled--;
        }
    }

    return false;
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print() {
    for (int i = 0; i < 9; i++) {
        for (int a = 0; a < 9; a++)
            cout << this->numbers[i][a] << " ";

        cout << endl;
    }
}

int Sudoku::checkValue(int x, int y, int n) {
    if (!columnHasNumber[y][n] && !lineHasNumber[x][n] && !block3x3HasNumber[x / 3][y / 3][n]) {
        columnHasNumber[y][n] = true;
        lineHasNumber[x][n] = true;
        block3x3HasNumber[x / 3][y / 3][n] = true;
        countFilled++;
        return true;
    }

    return false;   //no value was found
}


