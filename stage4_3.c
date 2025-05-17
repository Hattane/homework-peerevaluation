#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char note;
    int octave;
} Note;

typedef struct {
    Note root;
    Note third;
    Note fifth;
} Chord;

int isValidNote(char note) {
    return note >= 'A' && note <= 'G';
}

int isValidOctave(int octave) {
    return octave >= 1 && octave <= 8;
}

int isSameOctave(Note a, Note b) {
    return a.octave == b.octave;
}

int isSameNote(Note a, Note b) {
    return a.note == b.note;
}

int getNoteValue(char note) {
    // Maps A-G to scale degree (A=0, B=1, ..., G=6)
    return note - 'A';
}

void printNote(Note n) {
    printf("%c%d", n.note, n.octave);
}

void checkHarmony(Chord chord) {
    int rootVal = getNoteValue(chord.root.note);
    int thirdVal = getNoteValue(chord.third.note);
    int fifthVal = getNoteValue(chord.fifth.note);

    int interval1 = (thirdVal - rootVal + 7) % 7;
    int interval2 = (fifthVal - rootVal + 7) % 7;

    if (interval1 == 2 && interval2 == 4)
        printf("Harmony: This is a major chord (pleasant harmony).\n");
    else if (interval1 == 2 && interval2 == 5)
        printf("Harmony: This is a suspended chord.\n");
    else if (interval1 == 1 && interval2 == 4)
        printf("Harmony: This is a minor chord.\n");
    else
        printf("Harmony: The chord is dissonant or unclassified.\n");
}

void learnMusicTheory() {
    Chord chord;
    printf("Enter Root Note (A-G) and Octave (1-8): ");
    scanf(" %c %d", &chord.root.note, &chord.root.octave);

    printf("Enter Third Note (A-G) and Octave (1-8): ");
    scanf(" %c %d", &chord.third.note, &chord.third.octave);

    printf("Enter Fifth Note (A-G) and Octave (1-8): ");
    scanf(" %c %d", &chord.fifth.note, &chord.fifth.octave);

    if (!isValidNote(chord.root.note) || !isValidNote(chord.third.note) || !isValidNote(chord.fifth.note)) {
        printf("Error: Invalid note input.\n");
        return;
    }

    if (!isValidOctave(chord.root.octave) || !isValidOctave(chord.third.octave) || !isValidOctave(chord.fifth.octave)) {
        printf("Error: Invalid octave input.\n");
        return;
    }

    if (!isSameOctave(chord.root, chord.third) || !isSameOctave(chord.root, chord.fifth)) {
        printf("Error: All notes must be in the same octave.\n");
        return;
    }

    if (isSameNote(chord.root, chord.third) || isSameNote(chord.root, chord.fifth) || isSameNote(chord.third, chord.fifth)) {
        printf("Error: Duplicate notes are not allowed.\n");
        return;
    }

    printf("\n--- Chord Information ---\n");
    printf("Root: "); printNote(chord.root); printf("\n");
    printf("Third: "); printNote(chord.third); printf("\n");
    printf("Fifth: "); printNote(chord.fifth); printf("\n");

    checkHarmony(chord);
}

int main() {
    learnMusicTheory();
    return 0;
}
