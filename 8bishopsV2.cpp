#include "API_8bishops.h"

int debug; // Global
int successfulSets;

/** Notes:
*       bL - bishopsLeft
*       b - board
*       r - row
*       c - column
*       pB - putBishops
*/

int main() {
        int bL = 4;
        int b[T][T] = {};
        pB(b, 4, 0, 0);
        cout << "All possible sets checked..." << endl;
        return 0;
}

int pB(int b[T][T], int bL, int r, int c) {
        debug++;

        if (bL == 4) {
                bool under = false;
                if (c == 8) return 0;

                if (b[r][c] == 1) under = true;
                else b[r][c] = 1;

                pB(b, 3, 2, 0);

                if (under == true) b[r][c] = 1;         /* Backtracked */
                else b[r][c] = 0;

                pB(b, 4, r+1, c+1);
        }

        if (bL == 3) {
                bool under = false;
                if (c == 8) return 0;

                if (b[r][c] == 1) under = true;
                else b[r][c] = 1;

                pB(b, 2, 4, 0);

                if (under == true) b[r][c] = 1;         /* Backtracked */
                else b[r][c] = 0;

                if (c+1 <= 2) pB(b, 3, r-1, c+1);
                else pB(b, 3, r+1, c+1);
        }

        if (bL == 2) {
                bool under = false;
                if (c == 8) return 0;

                if (b[r][c] == 1) under = true;
                else b[r][c] = 1;

                pB(b, 1, 6, 0);

                if (under == true) b[r][c] = 1;         /* Backtracked */
                else b[r][c] = 0;

                if (c+1 <= 4) pB(b, 2, r-1, c+1);
                else pB(b, 2, r+1, c+1);
        }

        if (bL == 1) {
                bool under = false;
                if (c == 8) return 0;

                if (b[r][c] == 1) under = true;
                else b[r][c] = 1;

                if (isSuccess(b) == 0) {                // if success, shows results
                        if (under == true) b[r][c] = 1;         /* Backtracked */
                        else b[r][c] = 0;

                        if (c+1 <= 6) pB(b, 1, r-1, c+1);
                        else pB(b, 1, r+1, c+1);
                }
                else {                                           // Continuing with next search
                        if (under == true) b[r][c] = 1;
                        else b[r][c] = 0;
                        cout << endl <<"Enter any char to continue... ";
                        char con;
                        cin >> con;
                        cout << endl;

                        if (c+1 <= 6) pB(b, 1, r-1, c+1);
                        else pB(b, 1, r+1, c+1);
                }
        }
}

int isSuccess(int board[T][T]) {
// Here I'll check cells that are occupied by given bishops!

        // Making a copy of board[][] to mark occupied cells. + // Getting coordinates of every bishop
        int copiedBoard[T][T];
        for(int c = 0; c < T; c++)
                for(int r = 0; r < T; r++)
                        copiedBoard[c][r] = board[c][r];bool under = false;

        // Marking occupied cells by bishops
        for(int r = 0; r < T; r++)
                for(int c = 0; c < T; c++)
                        if(board[r][c] == 1) {
                                markByFigure(r, c, copiedBoard);
                        }

        // Checking if all blacks cells of copiedBoard are occupied!
        for (int r = 0; r < T; ) {
                for (int c = 0; c < T; c += 2)
                        if (copiedBoard[r][c] == 0) return 0;
                r++;
                for (int c = 1; c < T; c += 2)
                        if (copiedBoard[r][c] == 0) return 0;
                r++;
        }

        // If we get here, all black cells are occupied! //
        cout << "Step: " << debug << ". Successful sets: " << ++successfulSets << endl << endl;
        displayBoard(copiedBoard);
        for(int r = 0; r < T; r++)
                for(int c = 0; c < T; c++)
                        if(copiedBoard[r][c] == 1) {
                                copiedBoard[(T - 1) - r][c] = 3;        // 3 -> 'W'
                                markByFigure(T - 1 - r, c, copiedBoard);
                        }
        cout << endl;
        displayBoard(copiedBoard);
        return 1;

}

void markByFigure(int r, int c, int copiedBoard[T][T]) {
        int tr = r, tc = c;     // temporary r and c
        while (tr >= 0 && tr < 7 && tc > 0 && tc <= 7) {        // Top left marking

                tc -= 1; tr += 1;
                if(copiedBoard[tr][tc] == 0) copiedBoard[tr][tc] = 2;           // 2 -> '*'
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
