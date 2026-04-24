#include <stdio.h>

// Function to print the chessboard
void printBoard(int board[8][8]) {
    char piece_symbols[] = ".PNBQK";  // Symbols for pieces
    char color_symbols[] = " wb";     // Symbols for colors

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            int piece_type = board[i][j] / 10;  // Get the first digit (piece type)
            int color = board[i][j] % 10;       // Get the second digit (color)

            char piece_symbol = piece_symbols[piece_type];
            char color_symbol = color_symbols[color];

            // Use uppercase for white pieces and lowercase for black pieces
            if (color == 2) {
                piece_symbol += 32; // Convert to lowercase
            }

            printf("%c ", piece_symbol);
        }
        printf("\n");
    }
}

int main() {
    int board[8][8] = {
        {22, 32, 42, 52, 62, 42, 32, 22},
        {12, 12, 12, 12, 12, 12, 12, 12},
        {00, 00, 00, 00, 00, 00, 00, 00},
        {00, 00, 00, 00, 00, 00, 00, 00},
        {00, 00, 00, 00, 00, 00, 00, 00},
        {00, 00, 00, 00, 00, 00, 00, 00},
        {11, 11, 11, 11, 11, 11, 11, 11},
        {21, 31, 41, 51, 61, 41, 31, 21}
    };

    // Call the function to print the chessboard
    printBoard(board);

    return 0;
}
