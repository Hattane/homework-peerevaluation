#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 10
#define QUIZ_QUESTIONS 5
#define MAX_TRAINEES 4
#define PASS_SCORE 80

// Structs to hold questions and trainee info
typedef struct {
    int id;
    char question[100];
    char correctAnswer[100];
} KoreanQuestion;

typedef struct {
    char name[50];
    char nickname[20];
    char nationality[30];
    int quizScore;
    int passed; // 1 = pass, 0 = fail
} Trainee;

typedef struct {
    int questionID;
    char correctness; // 'O' for correct, 'X' for wrong
} QuizAnswer;

// Questions database
KoreanQuestion questionBank[MAX_QUESTIONS] = {
    {1, "What is the Korean word for 'Hello'?", "안녕하세요"},
    {2, "How do you say 'Thank you' in Korean?", "감사합니다"},
    {3, "What is the Korean word for 'Friend'?", "친구"},
    {4, "How do you say 'Goodbye' in Korean?", "안녕히 가세요"},
    {5, "What is the Korean word for 'Yes'?", "네"},
    {6, "How do you say 'No' in Korean?", "아니요"},
    {7, "What is the Korean word for 'Love'?", "사랑"},
    {8, "How do you say 'Food' in Korean?", "음식"},
    {9, "What is the Korean word for 'School'?", "학교"},
    {10, "How do you say 'Teacher' in Korean?", "선생님"}
};

// Trainees database
Trainee trainees[MAX_TRAINEES] = {
    {"Jiyeon Park", "Jiyeon", "South Korea", 0, 0},
    {"Ethan Smith", "Ethan", "USA", 0, 0},
    {"Helena Silva", "Helena", "Brazil", 0, 0},
    {"Liam Wilson", "Liam", "Australia", 0, 0}
};

QuizAnswer answers[QUIZ_QUESTIONS];

// Function declarations
int selectRandomTaker();
void serveRandomQuiz(int takerIndex);
void isAnswer(int questionID, char *userAnswer, int index);
void testKoreanLang();

// Simple delay function (waits approx seconds)
void delay(int seconds) {
    time_t start = time(NULL);
    while (time(NULL) - start < seconds);
}

int main() {
    srand((unsigned int)time(NULL));  // Seed random
    printf("=== Millieways Korean Language Quiz ===\n\n");

    testKoreanLang();

    return 0;
}

// Select random trainee who is NOT Korean
int selectRandomTaker() {
    int candidates[MAX_TRAINEES];
    int count = 0;

    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(trainees[i].nationality, "South Korea") != 0) {
            candidates[count++] = i;
        }
    }

    if (count == 0) return -1; // No eligible trainee found

    int randomIndex = rand() % count;
    return candidates[randomIndex];
}

// Conduct the quiz for the selected trainee
void serveRandomQuiz(int takerIndex) {
    printf("Welcome, %s, to the Korean quiz session!\n", trainees[takerIndex].name);
    printf("Quiz will start in 3 seconds. Get ready...\n");
    delay(3);

    printf("Quiz started!\n\n");

    int askedQuestions[QUIZ_QUESTIONS];
    for (int i = 0; i < QUIZ_QUESTIONS; i++) {
        askedQuestions[i] = -1;  // Initialize to -1 (no question)
    }

    for (int i = 0; i < QUIZ_QUESTIONS; i++) {
        int qIndex;

        // Pick a question index that wasn't asked before
        do {
            qIndex = rand() % MAX_QUESTIONS;
            int duplicate = 0;
            for (int j = 0; j < i; j++) {
                if (askedQuestions[j] == qIndex) {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) break;
        } while (1);

        askedQuestions[i] = qIndex;

        printf("Q%d: %s\nYour answer: ", i + 1, questionBank[qIndex].question);
        char userAnswer[100];
        fgets(userAnswer, sizeof(userAnswer), stdin);
        userAnswer[strcspn(userAnswer, "\n")] = 0;  // Remove newline

        isAnswer(questionBank[qIndex].id, userAnswer, i);
    }

    // Calculate total score
    int totalScore = 0;
    for (int i = 0; i < QUIZ_QUESTIONS; i++) {
        if (answers[i].correctness == 'O') {
            totalScore += 20;  // each correct = 20 points
        }
    }

    trainees[takerIndex].quizScore = totalScore;
    trainees[takerIndex].passed = (totalScore >= PASS_SCORE) ? 1 : 0;

    // Show results
    printf("\n=== Quiz Results for %s ===\n", trainees[takerIndex].name);
    for (int i = 0; i < QUIZ_QUESTIONS; i++) {
        printf("Question ID %d: %c\n", answers[i].questionID, answers[i].correctness);
    }
    printf("Total Score: %d\n", totalScore);
    printf("Pass Status: %s\n", trainees[takerIndex].passed ? "PASS" : "FAIL");
}

// Check if answer is correct or not
void isAnswer(int questionID, char *userAnswer, int index) {
    char *correctAns = NULL;
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        if (questionBank[i].id == questionID) {
            correctAns = questionBank[i].correctAnswer;
            break;
        }
    }

    answers[index].questionID = questionID;

    // Simple case-sensitive check: answer must exactly match
    if (correctAns != NULL && strcmp(userAnswer, correctAns) == 0) {
        answers[index].correctness = 'O';
    } else {
        answers[index].correctness = 'X';
    }
}

// Main quiz logic
void testKoreanLang() {
    int taker = selectRandomTaker();
    if (taker == -1) {
        printf("No eligible trainee found for the Korean quiz.\n");
        return;
    }
    serveRandomQuiz(taker);
}

