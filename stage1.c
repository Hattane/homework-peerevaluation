#include <stdio.h>
#include <stdlib.h>  // For atoi()
#include <string.h>
#include <ctype.h>

#define MAX_STAGES 8
#define MENU_ROWS 3
#define MENU_COLS 40  // Increased to avoid string length warnings

// Simulate 2D arrays using 1D array of strings
char mainMenu[MENU_ROWS][MENU_COLS] = {
    "I. Audition Management",
    "II. Training",
    "III. Debut"
};

char trainingMenu[MAX_STAGES][MENU_COLS] = {
    "1. Physical & Knowledge",
    "2. Self & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage",
    "8. Fan Communication"
};

char trainingResult[MAX_STAGES] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Function to check if training stage is unlocked
int isUnlocked(int stage) {
    if (stage == 0) return 1;
    if (stage == 1) return trainingResult[0] == 'P';
    return trainingResult[0] == 'P' && trainingResult[1] == 'P';
}

// Display main menu
void showMainMenu() {
    printf("\n--- Main Menu ---\n");
    for (int i = 0; i < MENU_ROWS; i++) {
        printf("%d. %s\n", i + 1, mainMenu[i]);
    }
    printf("Enter choice (0/Q/q to quit): ");
}

// Display training menu
void showTrainingMenu() {
    printf("\n--- Training Menu ---\n");
    for (int i = 0; i < MAX_STAGES; i++) {
        printf("%d. %s", i + 1, trainingMenu[i]);
        if (trainingResult[i] == 'P') printf(" [Completed]");
        else if (trainingResult[i] == 'F') printf(" [Failed]");
        printf("\n");
    }
    printf("Enter training stage (0 to return): ");
}

// Handle evaluation logic
void handleTraining(int index) {
    if (!isUnlocked(index)) {
        printf("You must pass previous stages to access this one.\n");
        return;
    }
    if (trainingResult[index] == 'P') {
        printf("This stage is already completed.\n");
        return;
    }

    char input;
    printf("Would you like to enter the evaluation result? (Y/N): ");
    scanf(" %c", &input);
    if (toupper(input) == 'Y') {
        printf("Did you complete the training and pass the certification? (P/F): ");
        scanf(" %c", &input);
        if (toupper(input) == 'P' || toupper(input) == 'F') {
            trainingResult[index] = toupper(input);
        } else {
            printf("Invalid input. Returning to menu.\n");
        }
    }
}

int main() {
    char input[10];

    while (1) {
        showMainMenu();
        scanf("%s", input);

        if (strcmp(input, "0") == 0 || toupper(input[0]) == 'Q') break;

        int choice = atoi(input);

        switch (choice) {
            case 1:
                printf("Audition Management selected.\n");
                break;
            case 2:
                while (1) {
                    showTrainingMenu();
                    int stage;
                    scanf("%d", &stage);
                    if (stage == 0) break;
                    if (stage >= 1 && stage <= MAX_STAGES) {
                        handleTraining(stage - 1);
                    } else {
                        printf("Invalid training stage.\n");
                    }
                }
                break;
            case 3:
                printf("Debut selected.\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    printf("Program exited.\n");
    return 0;
}
