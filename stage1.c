#include <stdio.h>
#include <string.h>

#define STAGE_COUNT 8

const char *trainingStages[STAGE_COUNT] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

char results[STAGE_COUNT] = { 'N','N','N','N','N','N','N','N' };

void showMainMenu();
void showTrainingMenu();
void handleStage(int index);
void printTrainingStatus();
int checkStageAccess(int index);

int main() {
    showMainMenu();
    return 0;
}

void showMainMenu() {
    char input[10];

    while (1) {
        printf("\n==== MAGRATHEA MAIN MENU ====\n");
        printf("1. Audition Management\n");
        printf("2. Training\n");
        printf("3. Debut\n");
        printf("Enter your choice (0 or Q to quit): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == 'q' || input[0] == 'Q' || input[0] == '\n') {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        if (input[0] == '1') {
            printf("\n[Audition Management Placeholder]\n");
        } else if (input[0] == '2') {
            showTrainingMenu();
        } else if (input[0] == '3') {
            printf("\n[Debut Placeholder]\n");
        } else {
            printf("Invalid option. Try again.\n");
        }
    }
}

void showTrainingMenu() {
    char input[10];

    while (1) {
        printf("\n==== TRAINING MENU ====\n");
        printTrainingStatus();

        printf("Select a stage to train (1-8) or 0/Q to go back: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == 'q' || input[0] == 'Q' || input[0] == '\n') {
            printf("Returning to main menu.\n");
            break;
        }

        int stage = input[0] - '1';

        if (stage >= 0 && stage < STAGE_COUNT) {
            if (checkStageAccess(stage)) {
                handleStage(stage);
            }
        } else {
            printf("Invalid stage number. Try again.\n");
        }
    }
}

void printTrainingStatus() {
    for (int i = 0; i < STAGE_COUNT; i++) {
        printf("%s\t[Status: %c]\n", trainingStages[i], results[i]);
    }
}

void handleStage(int index) {
    char input[10];

    if (results[index] == 'P') {
        printf("You already passed this stage. You can't retake it.\n");
        return;
    }

    printf("Would you like to enter the evaluation result for %s? (Y/N): ", trainingStages[index]);
    fgets(input, sizeof(input), stdin);

    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Did you pass the training? (Y/N): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Y' || input[0] == 'y') {
            results[index] = 'P';
            printf("Stage %d marked as PASSED.\n", index + 1);
        } else {
            results[index] = 'F';
            printf("Stage %d marked as FAILED.\n", index + 1);
        }
    } else {
        printf("No evaluation entered. Returning to training menu.\n");
    }
}

int checkStageAccess(int index) {
    if (index == 0) return 1;
    if (index == 1 && results[0] != 'P') {
        printf("You must complete Stage 1 before Stage 2.\n");
        return 0;
    }
    if (index >= 2 && (results[0] != 'P' || results[1] != 'P')) {
        printf("You must complete Stages 1 and 2 before accessing this stage.\n");
        return 0;
    }
    return 1;
}
