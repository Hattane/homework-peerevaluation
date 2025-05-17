#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_MEMBERS 10
#define MAX_STEPS 10
#define STEP_LEN 50
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    char nickname[NAME_LEN];
    int danceScore;
} Member;

typedef struct {
    char krName[NAME_LEN];
    char enName[NAME_LEN];
    char steps[MAX_STEPS][STEP_LEN];
    int stepCount;
} Dance;

Member members[MAX_MEMBERS] = {
    {"Ariel", "lioness", 0},
    {"Arthur", "hitchhiker", 0},
    {"Hye-kyung", "lightwalker", 0},
    {"Young-jin", "yjay", 0},
    {"Hyun-woo", "drumbeat", 0},
    {"Soo-min", "spectrum", 0}
};

Dance dances[6];

void shuffleSteps(char arr[MAX_STEPS][STEP_LEN], int count) {
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[STEP_LEN];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

void clearScreen() {
    printf("\033[2J\033[H"); // ANSI escape to clear terminal
}

void initializeDances() {
    FILE *file = fopen("dance_step.txt", "r");
    if (!file) {
        printf("Error: Cannot open dance_step.txt\n");
        exit(1);
    }

    int idx = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) && idx < 6) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        char *token = strtok(line, ":");
        strcpy(dances[idx].krName, token);

        char *steps = strtok(NULL, ":");
        int stepIdx = 0;
        token = strtok(steps, ",");
        while (token) {
            strcpy(dances[idx].steps[stepIdx++], token);
            token = strtok(NULL, ",");
        }
        dances[idx].stepCount = stepIdx;
        snprintf(dances[idx].enName, NAME_LEN, "Dance%d", idx + 1);
        idx++;
    }

    fclose(file);
}

int getMemberIndexByNickname(const char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(nickname, members[i].nickname) == 0)
            return i;
    }
    return -1;
}

void learnDanceStep() {
    char nickname[NAME_LEN];
    int attempts = 0, idx = -1;
    while (attempts < 3 && idx == -1) {
        printf("Enter your nickname: ");
        scanf("%s", nickname);
        idx = getMemberIndexByNickname(nickname);
        if (idx == -1) {
            printf("Nickname not found. Try again.\n");
            attempts++;
        }
    }
    if (idx == -1) {
        printf("Returning to previous menu...\n");
        return;
    }

    initializeDances();

    srand(time(NULL));
    int danceIndex = rand() % 6;

    printf("Dance Name: %s\n", dances[danceIndex].krName);
    printf("Steps (remember order):\n");
    for (int i = 0; i < dances[danceIndex].stepCount; i++) {
        printf("%s ", dances[danceIndex].steps[i]);
    }
    printf("\nShowing for 10 seconds...\n");
    sleep(10);
    clearScreen();

    char input[MAX_STEPS][STEP_LEN];
    printf("Enter the %d steps in order:\n", dances[danceIndex].stepCount);
    for (int i = 0; i < dances[danceIndex].stepCount; i++) {
        printf("Step %d: ", i + 1);
        scanf("%s", input[i]);
    }

    // Evaluation
    int correctInOrder = 1, correctOutOfOrder = 1, atLeastOneCorrect = 0;
    for (int i = 0; i < dances[danceIndex].stepCount; i++) {
        if (strcmp(input[i], dances[danceIndex].steps[i]) != 0) {
            correctInOrder = 0;
        }
    }

    int matched[MAX_STEPS] = {0};
    for (int i = 0; i < dances[danceIndex].stepCount; i++) {
        for (int j = 0; j < dances[danceIndex].stepCount; j++) {
            if (!matched[j] && strcmp(input[i], dances[danceIndex].steps[j]) == 0) {
                matched[j] = 1;
                atLeastOneCorrect = 1;
                break;
            }
        }
    }

    if (correctInOrder)
        members[idx].danceScore = 100;
    else if (atLeastOneCorrect && correctOutOfOrder)
        members[idx].danceScore = 50;
    else if (atLeastOneCorrect)
        members[idx].danceScore = 20;
    else
        members[idx].danceScore = 0;

    printf("\nCorrect steps: ");
    for (int i = 0; i < dances[danceIndex].stepCount; i++) {
        printf("%s ", dances[danceIndex].steps[i]);
    }
    printf("\nYour input: ");
    for (int i = 0; i < dances[danceIndex].stepCount; i++) {
        printf("%s ", input[i]);
    }

    printf("\nScore: %d\n", members[idx].danceScore);
}

int main() {
    int choice;
    while (1) {
        printf("\n[II. Training > 5. Dance Training]\n");
        printf("1. Learn Basic Dance Steps\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                learnDanceStep();
                break;
            case 0:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

