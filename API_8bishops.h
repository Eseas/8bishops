#ifndef API_8BISHOPS_H_INCLUDED
#define API_8BISHOPS_H_INCLUDED

#include <iostream>
#include <stdio.h>
using namespace std;

#define T 8

int pB(int b[T][T], int bL, int r, int c);

int isSuccess(int board[T][T]);

void displayBoard(int board[T][T]);

void markByFigure(int c, int r, int copiedBoard[T][T]);

#endif // API_8BISHOPS_H_INCLUDED
