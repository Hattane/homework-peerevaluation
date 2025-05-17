#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct JobPosting {
    int id;
    char title[50];
    char postingDate[11]; // YYYY-MM-DD + null
    char deadline[11];
    int numHires;
    char jobField[50];
    char *qualifications; // dynamically allocated
    struct JobPosting *next;
} JobPosting;

JobPosting *head = NULL;
int nextID = 1;

void createJobPosting() {
    JobPosting *newNode = malloc(sizeof(JobPosting));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->id = nextID++;

    printf("Enter job title (max 49 chars): ");
    fgets(newNode->title, sizeof(newNode->title), stdin);
    newNode->title[strcspn(newNode->title, "\n")] = '\0';

    printf("Enter posting date (YYYY-MM-DD): ");
    fgets(newNode->postingDate, sizeof(newNode->postingDate), stdin);
    newNode->postingDate[strcspn(newNode->postingDate, "\n")] = '\0';

    printf("Enter deadline (YYYY-MM-DD): ");
    fgets(newNode->deadline, sizeof(newNode->deadline), stdin);
    newNode->deadline[strcspn(newNode->deadline, "\n")] = '\0';

    printf("Enter number of hires: ");
    scanf("%d", &newNode->numHires);
    getchar(); // consume newline after scanf

    printf("Enter job field (max 49 chars): ");
    fgets(newNode->jobField, sizeof(newNode->jobField), stdin);
    newNode->jobField[strcspn(newNode->jobField, "\n")] = '\0';

    // Qualifications input as a dynamic string
    char buffer[256];
    printf("Enter qualifications: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    newNode->qualifications = malloc(strlen(buffer) + 1);
    if (!newNode->qualifications) {
        printf("Memory allocation failed\n");
        free(newNode);
        return;
    }
    strcpy(newNode->qualifications, buffer);

    newNode->next = head;
    head = newNode;

    printf("Job posting created with ID %d\n", newNode->id);
}

int main() {
    createJobPosting();
    // You can extend to add menus and other functions as needed.
    return 0;
}
