#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[20];
    char gender; // 'M' or 'F'
} Member;

typedef struct {
    float frequency;
    float amplitude;
    float jitter;
    int G, R, B, A, S; // GRBAS scale 0-3
} VoiceCharacteristics;

// Millieways members
Member members[] = {
    {"Jiyeon", 'F'},
    {"Ethan", 'M'},
    {"Helena", 'F'},
    {"Liam", 'M'}
};
const int memberCount = sizeof(members) / sizeof(members[0]);

// Gender-specific ranges
typedef struct {
    float freqMin, freqMax;
    float ampMin, ampMax;
    float jitterMin, jitterMax;
} GenderRanges;

GenderRanges rangesM = {85.0f, 180.0f, 2.5f, 3.6f, 0.2f, 0.6f};
GenderRanges rangesF = {165.0f, 255.0f, 3.5f, 4.7f, 0.3f, 1.0f};

// Utility random float generator in range [min, max]
float randFloat(float min, float max) {
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

// Random int in [min, max]
int randInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Find member index by name
int findMemberIndex(const char* name) {
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(name, members[i].name) == 0)
            return i;
    }
    return -1;
}

// Get random voice characteristics based on gender
VoiceCharacteristics getMyVoiceFromHeaven(char gender) {
    GenderRanges* r = (gender == 'M') ? &rangesM : &rangesF;
    VoiceCharacteristics v;
    v.frequency = randFloat(r->freqMin, r->freqMax);
    v.amplitude = randFloat(r->ampMin, r->ampMax);
    v.jitter = randFloat(r->jitterMin, r->jitterMax);
    // Random GRBAS 0-3 for bonus
    v.G = randInt(0, 3);
    v.R = randInt(0, 3);
    v.B = randInt(0, 3);
    v.A = randInt(0, 3);
    v.S = randInt(0, 3);
    return v;
}

// Up-and-down guessing game helper
int guessValue(float target, float min, float max, const char* prompt) {
    int attempts = 3;
    float guess;
    printf("Guess the %s (range %.2f - %.2f). You have %d attempts.\n", prompt, min, max, attempts);
    for (int i = 0; i < attempts; i++) {
        printf("Attempt %d: ", i + 1);
        if (scanf("%f", &guess) != 1) {
            while(getchar() != '\n'); // clear invalid input
            printf("Invalid input. Try again.\n");
            i--;
            continue;
        }
        if (guess == target) {
            printf("Correct! You found the %s.\n", prompt);
            return 1;
        } else if (guess < target) {
            printf("Too low.\n");
        } else {
            printf("Too high.\n");
        }
    }
    printf("Sorry, you didn't find the %s. The correct value was %.2f\n", prompt, target);
    return 0;
}

// GRBAS guessing game (0-3)
int guessGRBAS(const char* param, int target) {
    int attempts = 3;
    int guess;
    printf("Guess the %s (0 to 3). You have %d attempts.\n", param, attempts);
    for (int i = 0; i < attempts; i++) {
        printf("Attempt %d: ", i + 1);
        if (scanf("%d", &guess) != 1 || guess < 0 || guess > 3) {
            while(getchar() != '\n');
            printf("Invalid input. Please enter 0, 1, 2, or 3.\n");
            i--;
            continue;
        }
        if (guess == target) {
            printf("Correct! You found the %s.\n", param);
            return 1;
        } else if (guess < target) {
            printf("Too low.\n");
        } else {
            printf("Too high.\n");
        }
    }
    printf("Sorry, the correct %s was %d\n", param, target);
    return 0;
}

// Main function for findMyVoice
void findMyVoice() {
    char name[20];
    printf("Enter your Millieways member nickname (Jiyeon, Ethan, Helena, Liam): ");
    scanf("%19s", name);

    int idx = findMemberIndex(name);
    if (idx == -1) {
        printf("No such member found.\n");
        return;
    }

    Member* m = &members[idx];
    VoiceCharacteristics voice = getMyVoiceFromHeaven(m->gender);

    printf("\nLet's find your voice characteristics!\n");

    // Function pointers for guessing frequency, amplitude, jitter
    int freqFound = guessValue(voice.frequency, 
                               (m->gender == 'M') ? rangesM.freqMin : rangesF.freqMin,
                               (m->gender == 'M') ? rangesM.freqMax : rangesF.freqMax,
                               "frequency (Hz)");

    int ampFound = guessValue(voice.amplitude,
                             (m->gender == 'M') ? rangesM.ampMin : rangesF.ampMin,
                             (m->gender == 'M') ? rangesM.ampMax : rangesF.ampMax,
                             "amplitude (dB)");

    int jitterFound = guessValue(voice.jitter,
                                (m->gender == 'M') ? rangesM.jitterMin : rangesF.jitterMin,
                                (m->gender == 'M') ? rangesM.jitterMax : rangesF.jitterMax,
                                "voice pulse jitter (%)");

    printf("\nNow let's guess your GRBAS scale values:\n");
    guessGRBAS("G (Grade - overall evaluation)", voice.G);
    guessGRBAS("R (Roughness)", voice.R);
    guessGRBAS("B (Breathiness)", voice.B);
    guessGRBAS("A (Asthenia - weakness)", voice.A);
    guessGRBAS("S (Strain)", voice.S);

    if (freqFound && ampFound && jitterFound) {
        printf("\nCongratulations, %s! You found your vocal characteristics!\n", m->name);
    } else {
        printf("\nKeep practicing, %s! Try to find your voice next time.\n", m->name);
    }
}

int main() {
    srand((unsigned int)time(NULL));
    findMyVoice();
    return 0;
}
