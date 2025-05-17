#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATTERNS 10
#define MAX_SONGS 4
#define MAX_DESC 256
#define MAX_NAME 64

typedef struct Pattern {
    char name[MAX_NAME];
    char description[MAX_DESC];
} Pattern;

typedef struct TreeNode {
    char name[MAX_NAME];
    struct TreeNode *next;
} TreeNode;

typedef struct SongTree {
    char title[MAX_NAME];
    TreeNode *head;
} SongTree;

Pattern patterns[MAX_PATTERNS];
int patternCount = 0;
SongTree songs[MAX_SONGS];
int songCount = 0;

// Utility
void clearBuffer() {
    while (getchar() != '\n');
}

// File Loaders
void loadPatterns() {
    FILE *fp = fopen("dance_pattern.txt", "r");
    if (!fp) {
        printf("Failed to open dance_pattern.txt\n");
        return;
    }
    patternCount = 0;
    while (fscanf(fp, "%[^:]: %[^\n]\n", patterns[patternCount].name, patterns[patternCount].description) == 2) {
        patternCount++;
    }
    fclose(fp);
}

void loadSongChoreo() {
    FILE *fp = fopen("analyz_dance-pattern.csv", "r");
    if (!fp) {
        printf("Failed to open analyz_dance-pattern.csv\n");
        return;
    }
    char line[512];
    songCount = 0;
    while (fgets(line, sizeof(line), fp) && songCount < MAX_SONGS) {
        TreeNode *last = NULL;
        songs[songCount].head = NULL;

        char *token = strtok(line, ",\n");
        if (!token) continue;

        strncpy(songs[songCount].title, token, MAX_NAME);
        token = strtok(NULL, ",\n");

        while (token) {
            TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
            strncpy(node->name, token, MAX_NAME);
            node->next = NULL;

            if (!songs[songCount].head) {
                songs[songCount].head = node;
                last = node;
            } else {
                last->next = node;
                last = node;
            }

            token = strtok(NULL, ",\n");
        }
        songCount++;
    }
    fclose(fp);
}

// Quiz logic
void descriptionQuiz() {
    int correct = 0;
    srand(time(NULL));

    for (int i = 0; i < 4; i++) {
        int idx = rand() % patternCount;
        char userInput[MAX_NAME];
        char snippet[11] = {0};

        int descLen = strlen(patterns[idx].description);
        int start = rand() % (descLen - 10);
        strncpy(snippet, patterns[idx].description + start, 10);

        printf("\n[Quiz %d] Description snippet: %.10s\n", i + 1, snippet);
        printf("Enter pattern name: ");
        scanf("%s", userInput);

        if (strcmp(userInput, patterns[idx].name) == 0) {
            printf("Correct!\n");
            correct++;
        } else {
            printf("Incorrect. Answer: %s\n", patterns[idx].name);
        }
    }

    if (correct < 3) {
        printf("Less than 3 correct. Returning to menu.\n");
        return;
    }

    loadSongChoreo();
    for (int i = 0; i < songCount; i++) {
        printf("\n[Song: %s]\n", songs[i].title);
        TreeNode *curr = songs[i].head;
        while (curr) {
            printf(" -> %s", curr->name);
            curr = curr->next;
        }
        printf("\n");
    }

    // Bonus Mode
    printf("\nSelect a song number to guess patterns (1-%d), or 0 to exit: ", songCount);
    int sel;
    scanf("%d", &sel);
    if (sel < 1 || sel > songCount) return;

    TreeNode *curr = songs[sel - 1].head;
    printf("First Pattern: %s\n", curr->name);
    curr = curr->next;

    while (curr) {
        char guess[MAX_NAME];
        printf("Next Pattern: ");
        scanf("%s", guess);

        if (strcmp(guess, curr->name) != 0) {
            printf("Wrong! The correct was: %s\n", curr->name);
            return;
        }
        curr = curr->next;
    }

    printf("Congratulations! You guessed all patterns correctly!\n");
}

// Entry
void learnDancePattern() {
    loadPatterns();
    descriptionQuiz();
}

// MAIN
int main() {
    learnDancePattern();
    return 0;
}
