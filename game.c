#include <stdio.h>   // Required for input/output functions like printf, scanf
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

