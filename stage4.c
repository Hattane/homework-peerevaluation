#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 4
#define MAX_MIDI_NOTES 12
#define MIN_MIDI_NOTES 6
#define MAX_FEEDBACK_LEN 51
#define MAX_NAME_LEN 20

typedef struct {
    char name[MAX_NAME_LEN];
    int vocalRange;     // highest MIDI note (0-127)
    int midiNotesCount; // number of random MIDI notes generated (6 to 12)
    int midiValues[MAX_MIDI_NOTES]; // unique MIDI values (0 to vocalRange)
    double vocalStability;
    char feedback[MAX_FEEDBACK_LEN];
    int evaluated;      // flag if evaluation done
} TraineeVocalEval;

// Millieways trainees initialized
TraineeVocalEval trainees[MAX_TRAINEES] = {
    {"Jiyeon", 0, 0, {0}, 0.0, "", 0},
    {"Ethan", 0, 0, {0}, 0.0, "", 0},
    {"Helena", 0, 0, {0}, 0.0, "", 0},
    {"Liam", 0, 0, {0}, 0.0, "", 0}
};

// Find trainee by name
int findTraineeIndex(const char *name) {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(trainees[i].name, name) == 0)
            return i;
    }
    return -1;
}

// Check if a value exists in an array
int contains(int *arr, int len, int val) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}

// Generate unique random MIDI notes between 0 and vocalRange
// count = number of notes to generate (6-12)
void generateUniqueMIDINotes(int *arr, int count, int vocalRange) {
    int generated = 0;
    while (generated < count) {
        int val = rand() % (vocalRange + 1);
        if (!contains(arr, generated, val)) {
            arr[generated++] = val;
        }
    }
}

// Calculate vocal stability = average of absolute differences between consecutive notes
double calculateVocalStability(int *arr, int count) {
    int sumDifferences = 0;
    for (int i = 1; i < count; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff < 0) diff = -diff;
        sumDifferences += diff;
    }
    return (double)sumDifferences / (count - 1);
}

// Provide feedback based on vocal stability and vocal range
void provideFeedback(TraineeVocalEval *t) {
    if (t->vocalStability < 5.0) {
        snprintf(t->feedback, MAX_FEEDBACK_LEN, "Excellent stability, keep up the good work!");
    } else if (t->vocalStability < 10.0) {
        snprintf(t->feedback, MAX_FEEDBACK_LEN, "Good vocal stability, some room for improvement.");
    } else {
        snprintf(t->feedback, MAX_FEEDBACK_LEN, "Try exercises to improve your vocal stability.");
    }
}

// Print all vocal evaluations sorted by vocal stability (lowest first)
void printVocalInfo() {
    // Copy array to sort so original order not disturbed
    TraineeVocalEval sorted[MAX_TRAINEES];
    memcpy(sorted, trainees, sizeof(trainees));

    // Simple selection sort ascending by vocalStability
    for (int i = 0; i < MAX_TRAINEES - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < MAX_TRAINEES; j++) {
            if (!sorted[j].evaluated) continue; // skip non-evaluated
            if (!sorted[min_idx].evaluated || sorted[j].vocalStability < sorted[min_idx].vocalStability) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            TraineeVocalEval tmp = sorted[i];
            sorted[i] = sorted[min_idx];
            sorted[min_idx] = tmp;
        }
    }

    printf("\n=== Millieways Vocal Evaluation Results ===\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (sorted[i].evaluated) {
            printf("%d. %s\n", i + 1, sorted[i].name);
            printf("   Vocal Range (highest MIDI note): %d\n", sorted[i].vocalRange);
            printf("   Vocal Stability: %.2f\n", sorted[i].vocalStability);
            printf("   Feedback: %s\n", sorted[i].feedback);
        }
    }
    printf("\n");
}

// Measure vocal evaluation for one trainee
void measure(int traineeIndex) {
    TraineeVocalEval *t = &trainees[traineeIndex];

    int vocalRange, noteCount;
    printf("Enter vocal range (0-127): ");
    while (scanf("%d", &vocalRange) != 1 || vocalRange < 0 || vocalRange > 127) {
        printf("Invalid input. Enter vocal range (0-127): ");
        while (getchar() != '\n'); // clear input buffer
    }

    printf("Enter number of MIDI notes to generate (6 to 12): ");
    while (scanf("%d", &noteCount) != 1 || noteCount < MIN_MIDI_NOTES || noteCount > MAX_MIDI_NOTES || noteCount > vocalRange + 1) {
        printf("Invalid input. Enter number of MIDI notes (6 to 12) not exceeding vocal range+1: ");
        while (getchar() != '\n'); // clear input buffer
    }
    while (getchar() != '\n'); // clear newline

    t->vocalRange = vocalRange;
    t->midiNotesCount = noteCount;

    generateUniqueMIDINotes(t->midiValues, noteCount, vocalRange);

    // Sort midiValues ascending for stability calculation
    // Simple selection sort
    for (int i = 0; i < noteCount - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < noteCount; j++) {
            if (t->midiValues[j] < t->midiValues[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int tmp = t->midiValues[i];
            t->midiValues[i] = t->midiValues[min_idx];
            t->midiValues[min_idx] = tmp;
        }
    }

    t->vocalStability = calculateVocalStability(t->midiValues, noteCount);

    provideFeedback(t);

    t->evaluated = 1;

    printf("\nEvaluation Complete for %s!\n", t->name);
    printf("Vocal Stability: %.2f\n", t->vocalStability);
    printf("Feedback: %s\n\n", t->feedback);
}

// The vocal evaluation main menu function
void evalVocal() {
    char name[MAX_NAME_LEN];
    int tries = 3;
    int traineeIndex = -1;

    while (tries--) {
        printf("Enter Millieways trainee name to evaluate (Jiyeon, Ethan, Helena, Liam): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        traineeIndex = findTraineeIndex(name);
        if (traineeIndex != -1) break;

        printf("Trainee not found. Try again.\n");
    }

    if (traineeIndex == -1) {
        printf("Failed to find trainee. Returning to menu.\n");
        return;
    }

    measure(traineeIndex);

    printf("All evaluations completed. Sorted results:\n");
    printVocalInfo();
}

int main() {
    srand((unsigned int)time(NULL));

    // For demonstration, just call the evalVocal function:
    evalVocal();

    return 0;
}
