# N-Queens Problem Solver

This project provides a C implementation to solve the classic N-Queens problem. The goal is to place N queens on an N×N chessboard such that no two queens threaten each other (i.e., no two queens share the same row, column, or diagonal).

## Features

- **Board Initialization**: The chessboard is initialized with all positions set to zero (no queens placed).
- **Safe Position Check**: Determines if a queen can be safely placed at a given position without threatening others.
- **Threat Calculation**: Calculates the number of threatened cells if a queen is placed at a specific position.
- **Position Sorting**: Valid positions for placing queens are sorted based on their threat values to optimize the search.
- **Solution Finding**: Uses backtracking to find all possible solutions and displays them.

## Usage

Compile and run the C code. The program will find and display all valid solutions for an 8×8 chessboard.

```bash
gcc -o nqueens nqueens.c
./nqueens
Solution #1:
Q . . . . . . . 
. . . . Q . . . 
. . . . . . . Q 
. . . . . Q . . 
. . Q . . . . . 
. . . . . . Q . 
. Q . . . . . . 
. . . Q . . . . 

Total solutions: 92
