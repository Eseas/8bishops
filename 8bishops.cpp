#include "API_8bishops.h"

int debug; // Global
int iniR;
int iniC;

int main()
{
        int bishopsLeft = 4;
        int board[T][T] = {};

        for(int r = 0; r < T; r++)      // Set cell for beginning here!
                for(int c = r % 2; c < T; c += 2)
                {
                        iniR = r; iniC = c;
                        putFourBishops(bishopsLeft, r, c, board);
                        for(int r = 0; r < T; r++)             // Cleaning array.
                                for(int c = r % 2; c < T; c += 2)
                                        board[r][c] = 0;
                }
        cout << "No sets exist." << endl;
        return 0;
}

int putFourBishops(int bishopsLeft, int r, int c, int board[T][T]) {
        printf("%d\n", debug++);
// Problem is solved! //
        if (bishopsLeft == 0) {
                if (isSuccess(board) == 1) {
                        int continueButton;
                        cout << "SUCCESS. Starting position was: (" << iniR << "; "<<  iniC << ")" <<
                                 "\nPress any numbwer key to search for another set." << endl;
                        cin >> continueButton;
                        debug = 0;
                        return 1;
                } else {
                        return 0;
                }
        }

// Putting bishop in a cell! //
        board[r][c] = 1;

// Diving deep! //
        for (int j = c + 2; j < T; j += 2) {
                if (putFourBishops(bishopsLeft - 1, r, j, board) == 1) return 1;
                board[r][j] = 0;
        }
        for(int i = r + 1; i < T; i++)
                for (int j = r % 2; j < T; j += 2) {
                        if (putFourBishops(bishopsLeft - 1, i, j, board) == 1) return 1;
                        board[i][j] = 0;
                }

        return -2;
}

int isSuccess(int board[T][T]) {
// Here I'll check cells that are occupied by given bishops!

        // Making a copy of board[][] to mark occupied cells. + // Getting coordinates of every bishop
        int copiedBoard[T][T];
        for(int c = 0; c < T; c++)
                for(int r = 0; r < T; r++)
                        copiedBoard[c][r] = board[c][r];

        // Marking occupied cells by bishops
        for(int r = 0; r < T; r++)
                for(int c = 0; c < T; c++)
                        if(board[r][c] == 1) {
                                markByFigure(r, c, copiedBoard);
                        }

        // Checking if all blacks cells of copiedBoard are occupied!
        for (int r = 0; r < T; ) {
                for (int c = 0; c < T; c += 2)
                        if (copiedBoard[r][c] == 0) return -1;
                r++;
                for (int c = 1; c < T; c += 2)
                        if (copiedBoard[r][c] == 0) return -1;
                r++;
        }

        // If we get here, all black cells are occupied! //
        cout << "Symmetry" << endl;

        for(int r = 0; r < T; r++)
                for(int c = 0; c < T; c++)
                        if(copiedBoard[r][c] == 1) {
                                copiedBoard[(T - 1) - r][c] = 3;
                                markByFigure(T - 1 - r, c, copiedBoard);
                                displayBoard(copiedBoard);
                               cout << endl;
                        }
        return 1;

}

void markByFigure(int r, int c, int copiedBoard[T][T]) {
        int tr = r, tc = c;     // temporary r and c
        while (tr >= 0 && tr < 7 && tc > 0 && tc <= 7) {        // Top left marking

                tc -= 1; tr += 1;
                if(copiedBoard[tr][tc] == 0) copiedBoard[tr][tc] = 2;
        }

        tr = r; tc = c;         // resetting r and c
        while (tr >= 0 && tr < 7 && tc >= 0 && tc < 7) {        // Top right marking
                tr += 1; tc += 1;
                if(copiedBoard[tr][tc] == 0) copiedBoard[tr][tc] = 2;
        }

        tr = r; tc = c;         // resetting r and c
        while (tr > 0 && tr <= 7 && tc > 0 && tc <= 7) {        // Bottom left marking
                tr -= 1; tc -= 1;
                if(copiedBoard[tr][tc] == 0) copiedBoard[tr][tc] = 2;
        }

        tr = r; tc = c;         // resetting r and c
        while (tr > 0 && tr <= 7 && tc >= 0 && tc < 7) {        // Bottom right marking
                tr -= 1; tc += 1;
                if(copiedBoard[tr][tc] == 0) copiedBoard[tr][tc] = 2;
        }
}

void displayBoard(int board[T][T]) {
        for(int r = (T - 1); r >= 0; r--) {
                for (int c = 0; c < T; c++) {
                        if (board[r][c] == 0) cout << '-' << "   ";
                        if (board[r][c] == 1) cout << 'B' << "   ";
                        if (board[r][c] == 2) cout << '*' << "   ";
                        if (board[r][c] == 3) cout << 'W' << "   ";
                }
                cout << endl;
        }
}
