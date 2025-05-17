#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SENTENCES 10
#define MAX_TRAINEES 4
#define MAX_WORDS 20
#define QUESTIONS 5
#define MAX_NICKNAME_LEN 20

// Trainee info struct for storing nickname and scores
typedef struct {
    char nickname[MAX_NICKNAME_LEN];
    int totalScore;
    int attempted; // flag if trainee has attempted grammar test
} TraineeScore;

// Sentence pair struct
typedef struct {
    char english[200];
    char korean[200];
    char koreanWords[MAX_WORDS][20]; // to store split Korean words
    int wordCount;
} SentencePair;

// Millieways trainees
TraineeScore trainees[MAX_TRAINEES] = {
    {"Jiyeon", 0, 0},
    {"Ethan", 0, 0},
    {"Helena", 0, 0},
    {"Liam", 0, 0}
};

// Sample sentences
SentencePair sentenceBank[MAX_SENTENCES] = {
    {"I like to eat kimchi.", "나는 김치를 좋아해요.", {}, 0},
    {"He is reading a book.", "그는 책을 읽고 있어요.", {}, 0},
    {"We are going to school.", "우리는 학교에 가고 있어요.", {}, 0},
    {"She studies Korean every day.", "그녀는 매일 한국어를 공부해요.", {}, 0},
    {"They play soccer in the park.", "그들은 공원에서 축구를 해요.", {}, 0},
    {"The weather is very cold.", "날씨가 아주 추워요.", {}, 0},
    {"I want to learn Korean.", "나는 한국어를 배우고 싶어요.", {}, 0},
    {"My friend is very kind.", "내 친구는 아주 친절해요.", {}, 0},
    {"We watch movies on weekends.", "우리는 주말에 영화를 봐요.", {}, 0},
    {"The teacher is explaining the lesson.", "선생님이 수업을 설명하고 있어요.", {}, 0}
};

// Function to split Korean sentence into words (separated by spaces)
void splitKoreanWords(SentencePair *sentence) {
    char temp[200];
    strcpy(temp, sentence->korean);
    char *token = strtok(temp, " ");
    int count = 0;
    while (token != NULL && count < MAX_WORDS) {
        strcpy(sentence->koreanWords[count++], token);
        token = strtok(NULL, " ");
    }
    sentence->wordCount = count;
}

// Simple selection sort for words (to display sorted)
void selectionSortWords(char words[][20], int n) {
    int i, j, min_idx;
    char temp[20];
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (strcmp(words[j], words[min_idx]) < 0) {
                min_idx = j;
            }
        }
        // swap
        strcpy(temp, words[i]);
        strcpy(words[i], words[min_idx]);
        strcpy(words[min_idx], temp);
    }
}

// Shuffle the words in the Korean sentence
void shuffleWords(char words[][20], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[20];
        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
}

// Check nickname and return trainee index or -1 if not found
int findTraineeIndex(char *nickname) {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(trainees[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

// Compose Korean sentences quiz
void composeSentences(int traineeIndex) {
    int asked[QUESTIONS] = {-1, -1, -1, -1, -1};
    int score = 0;

    printf("Answer by arranging the Korean words to form the correct sentence.\n");

    for (int q = 0; q < QUESTIONS; q++) {
        int idx;
        do {
            idx = rand() % MAX_SENTENCES;
            int duplicate = 0;
            for (int k = 0; k < q; k++) {
                if (asked[k] == idx) duplicate = 1;
            }
            if (!duplicate) break;
        } while(1);
        asked[q] = idx;

        SentencePair *sentence = &sentenceBank[idx];
        if (sentence->wordCount == 0) {
            splitKoreanWords(sentence);
        }

        // Shuffle words for quiz
        shuffleWords(sentence->koreanWords, sentence->wordCount);

        // Sort words to display in order
        selectionSortWords(sentence->koreanWords, sentence->wordCount);

        printf("\nQ%d. English: %s\n", q + 1, sentence->english);
        printf("Arrange these Korean words in order to form the sentence:\n");
        for (int w = 0; w < sentence->wordCount; w++) {
            printf("%s ", sentence->koreanWords[w]);
        }
        printf("\nEnter the sentence: ");

        char userAnswer[250];
        fgets(userAnswer, sizeof(userAnswer), stdin);
        userAnswer[strcspn(userAnswer, "\n")] = 0;

        // Compare user answer with correct sentence ignoring spaces and case
        char userCmp[250] = {0}, correctCmp[250] = {0};
        int ui = 0, ci = 0;

        for (int i = 0; userAnswer[i]; i++)
            if (userAnswer[i] != ' ') userCmp[ui++] = userAnswer[i];
        userCmp[ui] = 0;

        for (int i = 0; sentence->korean[i]; i++)
            if (sentence->korean[i] != ' ') correctCmp[ci++] = sentence->korean[i];
        correctCmp[ci] = 0;

        if (strcmp(userCmp, correctCmp) == 0) {
            printf("Correct!\n");
            score += 20;
        } else {
            printf("Incorrect. Correct answer: %s\n", sentence->korean);
        }
    }

    trainees[traineeIndex].totalScore = score;
    trainees[traineeIndex].attempted = 1;

    printf("\n%s, your total score is: %d out of %d\n", trainees[traineeIndex].nickname, score, QUESTIONS * 20);
}

// Print all scores and ranking
void printScore() {
    // Sort trainees by score descending
    for (int i = 0; i < MAX_TRAINEES -1; i++) {
        for (int j = i + 1; j < MAX_TRAINEES; j++) {
            if (trainees[j].totalScore > trainees[i].totalScore) {
                TraineeScore temp = trainees[i];
                trainees[i] = trainees[j];
                trainees[j] = temp;
            }
        }
    }

    printf("\n=== Korean Grammar Scores ===\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (trainees[i].attempted) {
            printf("%d. %s - Score: %d\n", i+1, trainees[i].nickname, trainees[i].totalScore);
        } else {
            printf("%d. %s - No attempts yet\n", i+1, trainees[i].nickname);
        }
    }
}

// Main function for Korean grammar learning
void learnKoreanGrammar() {
    char nickname[MAX_NICKNAME_LEN];
    int tries = 3;
    int traineeIndex = -1;

    while (tries--) {
        printf("Enter your nickname (Jiyeon, Ethan, Helena, Liam): ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        traineeIndex = findTraineeIndex(nickname);
        if (traineeIndex != -1) break;

        printf("Nickname not found. Please try again.\n");
    }
    if (traineeIndex == -1) {
        printf("Failed to recognize nickname. Returning to menu.\n");
        return;
    }

    int choice;
    while (1) {
        printf("\nHello %s! Choose an option:\n", nickname);
        printf("1. Compose Korean Sentences\n");
        printf("2. Check Scores\n");
        printf("0. Exit\n");
        printf("Select: ");
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // clear invalid input
            choice = -1;
        }
        getchar(); // consume newline

        if (choice == 1) {
            composeSentences(traineeIndex);
        } else if (choice == 2) {
            if (trainees[traineeIndex].attempted == 0) {
                printf("You need to complete the sentence composition first.\n");
            } else {
                printScore();
            }
        } else if (choice == 0) {
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }
}

int main() {
    srand((unsigned int)time(NULL));
    learnKoreanGrammar();
    return 0;
}
