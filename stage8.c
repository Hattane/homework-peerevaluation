#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 100
#define MAX_ARTISTS 50

typedef struct {
    char name[MAX_STR];
    char nickname[MAX_STR];
    char dob[20];
    char gender[10];
    char education[MAX_STR];
    char phone[20];
    char email[MAX_STR];
    char nationality[MAX_STR];
    float height;
    float weight;
    char bloodType[10];
    char allergies[MAX_STR];
    char sns[MAX_STR];
} Artist;

void xorEncryptDecrypt(char *data, size_t len, char key) {
    for (size_t i = 0; i < len; i++) data[i] ^= key;
}

void protectMyData() {
    Artist artists[MAX_ARTISTS];
    int n, choice;
    char key;
    char input[MAX_STR];

    printf("Enter encryption key (single char): ");
    key = getchar();
    getchar(); // consume newline

    printf("Enter number of artists: ");
    scanf("%d", &n);
    getchar(); // consume newline

    for (int i = 0; i < n; i++) {
        Artist *a = &artists[i];
        printf("\nArtist %d:\n", i + 1);

        printf("Name: "); fgets(a->name, MAX_STR, stdin); a->name[strcspn(a->name, "\n")] = 0;
        printf("Nickname: "); fgets(a->nickname, MAX_STR, stdin); a->nickname[strcspn(a->nickname, "\n")] = 0;
        printf("Date of Birth: "); fgets(a->dob, sizeof(a->dob), stdin); a->dob[strcspn(a->dob, "\n")] = 0;
        printf("Gender: "); fgets(a->gender, sizeof(a->gender), stdin); a->gender[strcspn(a->gender, "\n")] = 0;
        printf("Education: "); fgets(a->education, MAX_STR, stdin); a->education[strcspn(a->education, "\n")] = 0;
        printf("Phone Number: "); fgets(a->phone, sizeof(a->phone), stdin); a->phone[strcspn(a->phone, "\n")] = 0;
        printf("Email: "); fgets(a->email, MAX_STR, stdin); a->email[strcspn(a->email, "\n")] = 0;
        printf("Nationality: "); fgets(a->nationality, MAX_STR, stdin); a->nationality[strcspn(a->nationality, "\n")] = 0;
        printf("Height: "); scanf("%f", &a->height); getchar();
        printf("Weight: "); scanf("%f", &a->weight); getchar();
        printf("Blood Type: "); fgets(a->bloodType, sizeof(a->bloodType), stdin); a->bloodType[strcspn(a->bloodType, "\n")] = 0;
        printf("Allergies: "); fgets(a->allergies, MAX_STR, stdin); a->allergies[strcspn(a->allergies, "\n")] = 0;
        printf("SNS: "); fgets(a->sns, MAX_STR, stdin); a->sns[strcspn(a->sns, "\n")] = 0;

        // Encrypt sensitive fields
        xorEncryptDecrypt(a->phone, strlen(a->phone), key);
        xorEncryptDecrypt(a->email, strlen(a->email), key);
        xorEncryptDecrypt(a->allergies, strlen(a->allergies), key);
    }

    while (1) {
        printf("\nArtists List:\n");
        for (int i = 0; i < n; i++)
            printf("%d: %s (%s)\n", i + 1, artists[i].name, artists[i].nickname);

        printf("Select artist by number to view details or 0 to exit: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 0) break;
        if (choice < 1 || choice > n) {
            printf("Invalid choice.\n");
            continue;
        }

        Artist *a = &artists[choice - 1];
        printf("\nName: %s\nNickname: %s\nDOB: %s\nGender: %s\nEducation: %s\nNationality: %s\nHeight: %.2f\nWeight: %.2f\nBlood Type: %s\nSNS: %s\n",
            a->name, a->nickname, a->dob, a->gender, a->education, a->nationality, a->height, a->weight, a->bloodType, a->sns);

        printf("Encrypted Phone: %s\nEncrypted Email: %s\nEncrypted Allergies: %s\n",
            a->phone, a->email, a->allergies);

        printf("Decrypt sensitive info? (y/n): ");
        if (fgets(input, sizeof(input), stdin) && (input[0] == 'y' || input[0] == 'Y')) {
            xorEncryptDecrypt(a->phone, strlen(a->phone), key);
            xorEncryptDecrypt(a->email, strlen(a->email), key);
            xorEncryptDecrypt(a->allergies, strlen(a->allergies), key);

            printf("Decrypted Phone: %s\nDecrypted Email: %s\nDecrypted Allergies: %s\n",
                a->phone, a->email, a->allergies);

            // Re-encrypt to keep data encrypted in memory
            xorEncryptDecrypt(a->phone, strlen(a->phone), key);
            xorEncryptDecrypt(a->email, strlen(a->email), key);
            xorEncryptDecrypt(a->allergies, strlen(a->allergies), key);
        }
    }
}

int main() {
    protectMyData();
    return 0;
}

