#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANDIDATES 6

// Candidate data arrays
char candidate_names[CANDIDATES][50];
char candidate_dobs[CANDIDATES][11];
char candidate_genders[CANDIDATES];
char candidate_emails[CANDIDATES][50];
char candidate_nationalities[CANDIDATES][30];
float candidate_bmis[CANDIDATES];
char candidate_primary_skills[CANDIDATES][30];
char candidate_secondary_skills[CANDIDATES][50];
int candidate_topik_levels[CANDIDATES];
char candidate_mbtis[CANDIDATES][5];
char candidate_intros[CANDIDATES][256];

// Function to calculate age from DOB (yyyy/mm/dd)
int calculate_age(const char *dob) {
    int birth_year;
    sscanf(dob, "%4d", &birth_year);
    return 2025 - birth_year;
}

// Function to clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char group_name[50];

    // Input group name
    printf("Enter the audition group name: ");
    fgets(group_name, sizeof(group_name), stdin);
    group_name[strcspn(group_name, "\n")] = 0; // Remove newline character

    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Entry\n", group_name);
    printf("####################################\n\n");

    // Input candidate details
    for (int i = 0; i < CANDIDATES; i++) {
        printf("Entering information for candidate %d:\n", i + 1);
        printf("1. Name: ");
        fgets(candidate_names[i], sizeof(candidate_names[i]), stdin);
        candidate_names[i][strcspn(candidate_names[i], "\n")] = 0; // Remove newline

        printf("2. Date of Birth (YYYY/MM/DD): ");
        scanf("%10s", candidate_dobs[i]);

        printf("3. Gender (M/F): ");
        scanf(" %c", &candidate_genders[i]);

        printf("4. Email: ");
        scanf("%49s", candidate_emails[i]);

        clear_input_buffer(); // Clear newline

        printf("5. Nationality: ");
        fgets(candidate_nationalities[i], sizeof(candidate_nationalities[i]), stdin);
        candidate_nationalities[i][strcspn(candidate_nationalities[i], "\n")] = 0;

        printf("6. BMI: ");
        scanf("%f", &candidate_bmis[i]);

        clear_input_buffer();

        printf("7. Primary Skill: ");
        fgets(candidate_primary_skills[i], sizeof(candidate_primary_skills[i]), stdin);
        candidate_primary_skills[i][strcspn(candidate_primary_skills[i], "\n")] = 0;

        printf("8. Secondary Skill: ");
        fgets(candidate_secondary_skills[i], sizeof(candidate_secondary_skills[i]), stdin);
        candidate_secondary_skills[i][strcspn(candidate_secondary_skills[i], "\n")] = 0;

        printf("9. Korean Proficiency Level (TOPIK 0-6): ");
        scanf("%d", &candidate_topik_levels[i]);

        printf("10. MBTI: ");
        scanf("%4s", candidate_mbtis[i]);

        clear_input_buffer();

        printf("11. Introduction: ");
        fgets(candidate_intros[i], sizeof(candidate_intros[i]), stdin);
        candidate_intros[i][strcspn(candidate_intros[i], "\n")] = 0;

        printf("=================================\n");
    }

    // Display candidate details
    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("===============================================================================================\n");
    printf("Name (Age)        | DOB        | Gender | Email                 | Nationality   | BMI  | Primary Skill | Secondary Skill | TOPIK | MBTI  \n");
    printf("===============================================================================================\n");

    for (int i = 0; i < CANDIDATES; i++) {
        int age = calculate_age(candidate_dobs[i]);
        printf("%-16s (%d) | %-10s | %-6c | %-22s | %-12s | %-4.1f | %-14s | %-16s | %-5d | %-4s\n",
               candidate_names[i], age, candidate_dobs[i], candidate_genders[i], candidate_emails[i],
               candidate_nationalities[i], candidate_bmis[i], candidate_primary_skills[i],
               candidate_secondary_skills[i], candidate_topik_levels[i], candidate_mbtis[i]);
        printf("------------------------------------------------------------------------------------------------\n");
        printf("%s\n", candidate_intros[i]);
        printf("------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
