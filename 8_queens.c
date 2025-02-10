#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 8  // Chessboard dimensions (8x8)
#define MAX_POSITIONS (N * N)

// Structure to define a board position with elimination value (threatened cells count)
typedef struct {
    int row;
    int col;
    int elimination;
} Position;

// Function prototypes for board setup and solution logic
void initializeBoard(int board[N][N]);
void printBoard(int board[N][N]);
bool isSafe(int board[N][N], int row, int col);
int calculateElimination(int board[N][N], int row, int col);
void getPositionsForColumn(int board[N][N], int col, Position positions[], int* count);
int comparePositions(const void* a, const void* b);
void solveNQueens(int board[N][N], int col, int* solutionCount);
void printEliminationBoard(int board[N][N]);

// Set all board positions to zero (indicating no queens placed)
void initializeBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }
}

// Display the board layout with 'Q' for queens and '.' for empty spaces
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

// Show elimination values, indicating how many cells would be threatened by placing a queen
void printEliminationBoard(int board[N][N]) {
    printf("Displaying elimination values for current board state:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j]) {
                printf("Q  "); // Display 'Q' for queen positions
            } else {
                int elim = calculateElimination(board, i, j);
                printf("%-2d ", elim); // Print elimination value for empty positions
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Verify if a queen can be safely placed at the specified row and column
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check horizontally along the current row (to the left only)
    for (j = 0; j < col; j++) {
        if (board[row][j]) return false; // Queen in same row is a threat
    }

    // Check upper-left diagonal for threats
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }

    // Check lower-left diagonal for threats
    for (i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }

    return true; // Safe position for queen
}

// Calculate the number of threatened cells if a queen is placed at (row, col)
int calculateElimination(int board[N][N], int row, int col) {
    int count = 0;
    bool threatened[N][N] = {false};

    // Mark threatened cells along the row and column
    for (int i = 0; i < N; i++) {
        threatened[row][i] = true;  // Same row
        threatened[i][col] = true;  // Same column
    }

    // Mark diagonals as threatened
    // Upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        threatened[i][j] = true;
    }
    // Lower-right diagonal
    for (int i = row, j = col; i < N && j < N; i++, j++) {
        threatened[i][j] = true;
    }
    // Upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        threatened[i][j] = true;
    }
    // Lower-left diagonal
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        threatened[i][j] = true;
    }

    // Count all threatened cells that do not already contain a queen
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (threatened[i][j] && board[i][j] == 0) {
                count++;
            }
        }
    }

    return count;
}

// Sorting function to arrange positions based on elimination values in ascending order
int comparePositions(const void* a, const void* b) {
    return ((Position*)a)->elimination - ((Position*)b)->elimination;
}

// Find all safe positions for a given column and sort them by elimination values
void getPositionsForColumn(int board[N][N], int col, Position positions[], int* count) {
    *count = 0;
    for (int row = 0; row < N; row++) {
        if (isSafe(board, row, col)) {
            positions[*count].row = row;
            positions[*count].col = col;
            positions[*count].elimination = calculateElimination(board, row, col);
            (*count)++;
        }
    }
    // Sort positions based on elimination values
    qsort(positions, *count, sizeof(Position), comparePositions);
}

// Recursive function to attempt to place queens in each column
void solveNQueens(int board[N][N], int col, int* solutionCount) {
    if (col >= N) { // All queens are successfully placed
        (*solutionCount)++;
        printf("Solution #%d:\n", *solutionCount);
        printBoard(board);
        return;
    }

    Position positions[N];
    int posCount;
    
    // Obtain sorted valid positions for the current column
    getPositionsForColumn(board, col, positions, &posCount);

    // Try each position based on increasing elimination values
    for (int i = 0; i < posCount; i++) {
        int row = positions[i].row;
        
        // Place a queen in the current position
        board[row][col] = 1;
        
        // Recursively try to place queens in subsequent columns
        solveNQueens(board, col + 1, solutionCount);
        
        // Remove the queen and backtrack to previous state
        board[row][col] = 0;
    }
}

int main() {
    int board[N][N];
    int solutionCount = 0;
    
    // Initialize the chessboard with no queens
    initializeBoard(board);
    
    printf("Searching for all possible solutions to the %d-Queens problem...\n\n", N);
    
    // Show initial elimination values on an empty board
    printf("Elimination values for the empty board:\n");
    printEliminationBoard(board);
    
    // Start solving from the first column
    solveNQueens(board, 0, &solutionCount);
    
    printf("Total number of solutions: %d\n", solutionCount);
    
    return 0;
}
