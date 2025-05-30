#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants for the game board
#define ROWS 3
#define COLS 3
#define EMPTY ' '
#define PLAYER_X 'X'
#define PLAYER_O 'O'

// Function to initialize the game board
void initializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Function to print the game board
void printBoard(const char board[ROWS][COLS]) {
    printf("-------------\n");
    for (int i = 0; i < ROWS; i++) {
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
        printf("-------------\n");
    }
}

// Function to check if a move is valid
int isValidMove(const char board[ROWS][COLS], int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] == EMPTY);
}

// Function to make a move
void makeMove(char board[ROWS][COLS], int row, int col, char player) {
    board[row][col] = player;
}

// Function to check if a player has won
char checkWin(const char board[ROWS][COLS]) {
    // Check rows
    for (int i = 0; i < ROWS; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
            return board[i][0];
        }
    }
    // Check columns
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != EMPTY) {
            return board[0][j];
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
        return board[0][2];
    }
    return EMPTY; // No winner
}

// Function to check if the board is full
int isBoardFull(const char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == EMPTY) {
                return 0; // Board is not full
            }
        }
    }
    return 1; // Board is full
}

int main() {
    char board[ROWS][COLS];
    char currentPlayer = PLAYER_X;
    int row, col;
    char winner = EMPTY;

    initializeBoard(board);

    printf("Welcome to Tic-Tac-Toe!\n");

    while (winner == EMPTY && !isBoardFull(board)) {
        printBoard(board);
        printf("Player %c's turn. Enter row (0-2) and column (0-2): ", currentPlayer);
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input. Please enter two numbers.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (isValidMove(board, row, col)) {
            makeMove(board, row, col, currentPlayer);
            winner = checkWin(board);
            if (winner == EMPTY) {
                currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
            }
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    printBoard(board);

    if (winner != EMPTY) {
        printf("Player %c wins!\n", winner);
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}#include <stdio.h>   // Required for input/output functions like printf, scanf
#include <stdlib.h>  // Required for rand(), srand(), and exit()
#include <time.h>    // Required for time() to seed the random number generator

// Function to play the guessing game
void play_guessing_game() {
    printf("--------------------------------------------------\n");
    printf("Welcome to the Ultimate Guessing Game!\n");
    printf("--------------------------------------------------\n");

    // Define the range for the secret number
    const int MIN_NUM = 1;
    const int MAX_NUM = 100;

    // Seed the random number generator using current time
    srand((unsigned int)time(NULL));
    // Generate a random integer within the specified range
    int secret_number = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
    
    // Define the maximum number of attempts the player gets
    const int MAX_ATTEMPTS = 7;
    int attempts_taken = 0;
    int guess; // Variable to store the player's guess

    printf("I'm thinking of a number between %d and %d.\n", MIN_NUM, MAX_NUM);
    printf("You have %d attempts to guess it.\n", MAX_ATTEMPTS);
    printf("\nLet the guessing begin!\n");

    // Game loop: Continues until the player guesses correctly or runs out of attempts.
    while (attempts_taken < MAX_ATTEMPTS) {
        attempts_taken++; // Increment attempt counter

        printf("Attempt %d/%d: Enter your guess (or 0 to quit): ", attempts_taken, MAX_ATTEMPTS);
        
        // Read the integer input from the user
        // scanf returns the number of items successfully read. Check for errors.
        if (scanf("%d", &guess) != 1) {
            printf("Invalid input. Please enter a whole number.\n");
            // Clear the invalid input from the buffer to prevent infinite loop
            while (getchar() != '\n'); 
            attempts_taken--; // Don't count this as a valid attempt
            continue; // Skip to the next iteration
        }

        // Check if the user wants to quit (using 0 as a sentinel value)
        if (guess == 0) {
            printf("\nExiting game. Thanks for playing!\n");
            exit(0); // Exit the program
        }

        // Check if the guess is within the valid range
        if (guess < MIN_NUM || guess > MAX_NUM) {
            printf("Oops! Please guess a number between %d and %d.\n", MIN_NUM, MAX_NUM);
            attempts_taken--; // Don't count this as a valid attempt
            continue; // Skip to the next iteration
        }

        // Provide hints
        if (guess < secret_number) {
            printf("Too low! Try a higher number.\n");
        } else if (guess > secret_number) {
            printf("Too high! Aim a little lower.\n");
        } else {
            // Correct guess!
            printf("\n🎉 Congratulations! You guessed the number %d correctly!\n", secret_number);
            printf("It took you %d attempts.\n", attempts_taken);
            break; // Exit the loop as the game is won
        }
    }

    // This block executes if the loop finishes because attempts ran out (no 'break')
    if (guess != secret_number) {
        printf("\n--------------------------------------------------\n");
        printf("Game Over! You've run out of attempts.\n");
        printf("The secret number was: %d\n", secret_number);
        printf("Better luck next time!\n");
        printf("--------------------------------------------------\n");
    }

    // Ask to play again (simplified for 100 lines, no recursive call)
    printf("\nPress Enter to exit.\n");
    while (getchar() != '\n'); // Consume remaining newline characters
    getchar(); // Wait for user to press Enter
}

// Main function where program execution begins
int main() {
    play_guessing_game(); // Call the game function
    return 0;             // Indicate successful program execution
}

