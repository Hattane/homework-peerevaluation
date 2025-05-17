#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_Q 5
#define MAX_A 3
#define NAME_LEN 30
#define MAX_R 20

typedef struct {
    char hangul[4], engAlpha[3], engPron[10];
    int isConsonant;
} Jamo;

typedef struct {
    char name[NAME_LEN], challenge[3];
    int score, attempts;
} Result;

Jamo consonants[] = {
    {"ㄱ","g","giyeok",1},{"ㄴ","n","nieun",1},{"ㄷ","d","digeut",1},
    {"ㄹ","r","rieul",1},{"ㅁ","m","mieum",1},{"ㅂ","b","bieup",1},
    {"ㅅ","s","siot",1},{"ㅇ","ng","ieung",1},{"ㅈ","j","jieut",1},
    {"ㅊ","ch","chieut",1},{"ㅋ","k","kieuk",1},{"ㅌ","t","tieut",1},
    {"ㅍ","p","pieup",1},{"ㅎ","h","hieut",1}
};

Jamo vowels[] = {
    {"ㅏ","a","a",0},{"ㅑ","ya","ya",0},{"ㅓ","eo","eo",0},
    {"ㅕ","yeo","yeo",0},{"ㅗ","o","o",0},{"ㅛ","yo","yo",0},
    {"ㅜ","u","u",0},{"ㅠ","yu","yu",0},{"ㅡ","eu","eu",0},{"ㅣ","i","i",0}
};

Result results[MAX_R];
int resCount=0;

void clearBuf() { while(getchar()!='\n'); }

void selectQ(int *sel,int max) {
    int c=0;
    while(c<MAX_Q){
        int r=rand()%max, dup=0;
        for(int i=0;i<c;i++) if(sel[i]==r) dup=1;
        if(!dup) sel[c++]=r;
    }
}

void updateResult(char *name,char *type,int score){
    for(int i=0;i<resCount;i++)
        if(!strcmp(results[i].name,name)&&!strcmp(results[i].challenge,type)){
            if(results[i].attempts<MAX_A){
                results[i].score+=score; results[i].attempts++;
                return;
            }
            printf("Max attempts reached for this challenge.\n");
            return;
        }
    if(resCount<MAX_R){
        strcpy(results[resCount].name,name);
        strcpy(results[resCount].challenge,type);
        results[resCount].score=score;
        results[resCount].attempts=1;
        resCount++;
    }
}

void quizKor2Eng(Jamo *jamos,int size,char *name){
    int sel[MAX_Q], score=0;
    selectQ(sel,size);
    printf("\nHangul to English Quiz\n");
    for(int i=0;i<MAX_Q;i++){
        printf("Q%d: '%s'? (alphabet,pronunciation): ",i+1,jamos[sel[i]].hangul);
        char input[50]; fgets(input,sizeof(input),stdin);
        char *alpha=strtok(input,","), *pron=strtok(NULL,",");
        if(alpha && pron){
            while(*alpha==' ') alpha++;
            while(*pron==' ') pron++;
            if(strcasecmp(alpha,jamos[sel[i]].engAlpha)==0 && strcasecmp(pron,jamos[sel[i]].engPron)==0){
                printf("Correct!\n"); score+=10;
            } else printf("Wrong! Correct: %s,%s\n",jamos[sel[i]].engAlpha,jamos[sel[i]].engPron);
        } else printf("Invalid input! Correct: %s,%s\n",jamos[sel[i]].engAlpha,jamos[sel[i]].engPron);
    }
    printf("Score: %d/50\n\n",score);
    updateResult(name,"KE",score);
}

void quizEng2Kor(Jamo *jamos,int size,char *name){
    int sel[MAX_Q], score=0;
    selectQ(sel,size);
    printf("\nEnglish to Hangul Quiz\n");
    for(int i=0;i<MAX_Q;i++){
        printf("Q%d: '%s,%s'? (Hangul): ",i+1,jamos[sel[i]].engAlpha,jamos[sel[i]].engPron);
        char input[10]; fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")]=0;
        if(strcmp(input,jamos[sel[i]].hangul)==0){
            printf("Correct!\n"); score+=10;
        } else printf("Wrong! Correct: %s\n",jamos[sel[i]].hangul);
    }
    printf("Score: %d/50\n\n",score);
    updateResult(name,"EK",score);
}

void showResults(){
    if(resCount==0){printf("\nNo results.\n\n");return;}
    // Sort by challenge then name
    for(int i=0;i<resCount-1;i++)
        for(int j=0;j<resCount-1-i;j++){
            if(strcmp(results[j].challenge,results[j+1].challenge)>0 ||
               (strcmp(results[j].challenge,results[j+1].challenge)==0 &&
                strcmp(results[j].name,results[j+1].name)>0)){
                Result tmp=results[j]; results[j]=results[j+1]; results[j+1]=tmp;
            }
        }
    printf("\nName            Type  AvgScore Attempts\n");
    for(int i=0;i<resCount;i++){
        int avg = results[i].attempts ? results[i].score/results[i].attempts : 0;
        printf("%-15s %-5s %-8d %-8d\n", results[i].name, results[i].challenge, avg, results[i].attempts);
    }
    printf("\n");
}

void learnHangul(){
    char name[NAME_LEN];
    printf("Enter your name: ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")]=0;
    if(strlen(name)==0) {printf("No name entered.\n"); return;}

    while(1){
        printf("\n1.Hangul->English  2.English->Hangul  3.View Results  0.Exit\nChoice: ");
        int ch, cv=0;
        if(scanf("%d",&ch)!=1){clearBuf(); break;}
        clearBuf();
        if(ch==0) break;
        if(ch==1||ch==2){
            printf("1.Consonants  2.Vowels  0.Cancel\nChoice: ");
            if(scanf("%d",&cv)!=1){clearBuf(); break;}
            clearBuf();
            if(cv==0) continue;
            if(cv!=1 && cv!=2) {printf("Invalid.\n"); continue;}
        }
        switch(ch){
            case 1:
                if(cv==1) quizKor2Eng(consonants,sizeof(consonants)/sizeof(Jamo),name);
                else if(cv==2) quizKor2Eng(vowels,sizeof(vowels)/sizeof(Jamo),name);
                break;
            case 2:
                if(cv==1) quizEng2Kor(consonants,sizeof(consonants)/sizeof(Jamo),name);
                else if(cv==2) quizEng2Kor(vowels,sizeof(vowels)/sizeof(Jamo),name);
                break;
            case 3: showResults(); break;
            default: printf("Invalid.\n"); break;
        }
    }
}

int main(){
    srand(time(NULL));
    printf("=== Millieways Hangul Learning ===\n");
    while(1){
        printf("\nMain Menu:\n1.Language Training\n0.Exit\nChoice: ");
        int m;
        if(scanf("%d",&m)!=1){clearBuf(); break;}
        clearBuf();
        if(m==0) break;
        if(m==1) learnHangul();
        else printf("Invalid.\n");
    }
    printf("Bye!\n");
    return 0;
}
