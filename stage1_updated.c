#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MEMBERS 4
#define NUM_TESTS 7

// Store member names and nicknames
char *milliways_members[NUM_MEMBERS][2] = {
    {"Goeun Kim", "goeun"},
    {"Woncheol Park", "woncheol"},
    {"Youngjin Lee", "youngjin"},
    {"Hyekyung Choi", "hyekyung"}
};

// Store fitness scores (nicknames + fitness data)
float health_scores[NUM_MEMBERS][NUM_TESTS + 1]; // +1 for nickname index

// Function to parse fitness data from a comma-separated input
void parseFitnessInput(char *input, int memberIndex) {
    char *token;
    int i = 0;

    token = strtok(input, ",");
    while (token != NULL && i < NUM_TESTS) {
        health_scores[memberIndex][i + 1] = atof(token); // Store the fitness test results
        token = strtok(NULL, ",");
        i++;
    }
}

// Function to get fitness data of a member
void getHealth() {
    int option;
    char nickname[50];

    printf("\n1. View All Fitness Data\n");
    printf("2. View One Member's Fitness Data\n");
    printf("3. View One Fitness Test Result for a Member\n");
    printf("Select option: ");
    scanf("%d", &option);

    if (option == 1) {
        for (int i = 0; i < NUM_MEMBERS; i++) {
            printf("\nName: %s\n", milliways_members[i][0]);
            printf("Nickname: %s\n", milliways_members[i][1]);
            printf("1-Mile Run: %.2f\n", health_scores[i][1]);
            printf("Speed Sprint: %.2f\n", health_scores[i][2]);
            printf("Push-ups: %.2f\n", health_scores[i][3]);
            printf("Squats: %.2f\n", health_scores[i][4]);
            printf("Arm Strength: %.2f\n", health_scores[i][5]);
            printf("Swimming: %.2f\n", health_scores[i][6]);
            printf("Weightlifting: %.2f\n", health_scores[i][7]);
        }
    } else if (option == 2) {
        printf("Enter nickname: ");
        scanf("%s", nickname);

        for (int i = 0; i < NUM_MEMBERS; i++) {
            if (strcmp(nickname, milliways_members[i][1]) == 0) {
                printf("\nName: %s\n", milliways_members[i][0]);
                printf("Nickname: %s\n", milliways_members[i][1]);
                printf("1-Mile Run: %.2f\n", health_scores[i][1]);
                printf("Speed Sprint: %.2f\n", health_scores[i][2]);
                printf("Push-ups: %.2f\n", health_scores[i][3]);
                printf("Squats: %.2f\n", health_scores[i][4]);
                printf("Arm Strength: %.2f\n", health_scores[i][5]);
                printf("Swimming: %.2f\n", health_scores[i][6]);
                printf("Weightlifting: %.2f\n", health_scores[i][7]);
                return;
            }
        }
        printf("Nickname not found!\n");
    } else if (option == 3) {
        printf("Enter nickname: ");
        scanf("%s", nickname);
        printf("Enter test number (1 to 7): ");
        int testNum;
        scanf("%d", &testNum);

        for (int i = 0; i < NUM_MEMBERS; i++) {
            if (strcmp(nickname, milliways_members[i][1]) == 0) {
                if (testNum >= 1 && testNum <= 7) {
                    printf("Test result for %s (%s): %.2f\n", milliways_members[i][0], milliways_members[i][1], health_scores[i][testNum]);
                } else {
                    printf("Invalid test number!\n");
                }
                return;
            }
        }
        printf("Nickname not found!\n");
    } else {
        printf("Invalid option.\n");
    }
}

// Function to enter fitness data
void setHealth() {
    char input[200];
    char nickname[50];

    printf("Enter nickname: ");
    scanf("%s", nickname);

    int memberIndex = -1;
    for (int i = 0; i < NUM_MEMBERS; i++) {
        if (strcmp(nickname, milliways_members[i][1]) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Nickname not found!\n");
        return;
    }

    printf("Enter 7 fitness values (comma-separated):\n");
    printf("1-Mile Run, Speed Sprint, Push-ups, Squats, Arm Strength, Swimming, Weightlifting\n");
    scanf(" %[^\n]", input);  // Accept the entire line of input

    parseFitnessInput(input, memberIndex);
    printf("Fitness data saved for %s!\n", milliways_members[memberIndex][0]);
}

// Main menu loop
void mainMenu() {
    int option;

    while (1) {
        printf("\nMain Menu:\n");
        printf("1. Audition Management\n");
        printf("2. Training\n");
        printf("3. Debut\n");
        printf("Select option (0 to exit): ");
        scanf("%d", &option);

        if (option == 0) {
            break;
        }

        switch (option) {
            case 1:
                // Audition Management (Not implemented in this example)
                break;
            case 2:
                {
                    int trainingOption;
                    while (1) {
                        printf("\nTraining Menu:\n");
                        printf("1. Physical Strength & Knowledge\n");
                        printf("Select option: ");
                        scanf("%d", &trainingOption);

                        if (trainingOption == 1) {
                            printf("\n1. Physical Strength & Knowledge\n");
                            printf("A. Enter Fitness Data\n");
                            printf("B. View Fitness Data\n");
                            printf("Select an option: ");
                            char subOption;
                            scanf(" %c", &subOption);

                            if (subOption == 'A' || subOption == 'a') {
                                setHealth();
                            } else if (subOption == 'B' || subOption == 'b') {
                                getHealth();
                            } else {
                                printf("Invalid option.\n");
                            }
                        }
                    }
                    break;
                }
            case 3:
                // Debut (Not implemented in this example)
                break;
            default:
                printf("Invalid option.\n");
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
