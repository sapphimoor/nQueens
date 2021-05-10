#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int bor=1;
int num=1;
int n;
int** Q;


void checkOptions(int, char**);
void sort(char**, int, int);
char* mid(char*, char*, char*);
void init();
void term();
void putQ(int);
void makeAnser();


int main(int argc, char** argv) {
    checkOptions(argc, argv);
    
    printf("Input PROBLEM SIZE: n = ");
    scanf("%d", &n);

    init();
    putQ(1);
    term();

    return 0;
}



void checkOptions(int argc, char** argv) {
    int argi=0, opti=0, optc=4, tmp, i;
    char* opt[] = {"--board", "--number", "-b", "-n"};
    char** myargv;

    if(argc == 1) return;

    myargv = (char**) malloc(sizeof(char*) * argc);
    for(i=0; i<argc; i++) {
        myargv[i] = (char*) malloc(sizeof(char) * 20);
        strcpy(myargv[i], argv[i]);
    }

    sort(myargv, 0, argc-1);

    bor = 0; num = 0;
    while((argi<argc) && (opti<optc)) {
        tmp = strcmp(myargv[argi], opt[opti]);
        if(!tmp) {
            switch (opti) {
            case 0:
            case 2:
                bor = 1;
                break;
            
            case 1:
            case 3:
                num = 1;
                break;
            }
            argi++; opti++;
        }
        else if(tmp < 0) argi++;
        else opti++;
    }
}


void sort(char** s, int  left, int right) {
    if(left < right) {
        int i=left, j=right;
        char tmp[20];
        char* pivot=mid(s[i], s[i + (j-i)/2], s[j]);

        while(1) {
            while(strcmp(s[i], pivot) < 0) i++;
            while(strcmp(pivot, s[j]) < 0) j--;
            if(i>= j) break;

            strcpy(tmp, s[i]);
            strcpy(s[i], s[j]);
            strcpy(s[j], tmp);

            i++; j--;
        }
        sort(s, left, i-1);
        sort(s, j+1, right);
    }
}


char* mid(char* s1, char* s2, char* s3) {
    if(strcmp(s1, s2) < 0) {
        if(strcmp(s2, s3) < 0) return s2;
        else if(strcmp(s1, s3) < 0) return s3;
        else return s1;
    }
    else {
        if(strcmp(s2, s3) > 0) return s2;
        else if(strcmp(s1, s3) > 0) return s3;
        else return s1;
    }
}


void init() {
    int i, j;
    Q = (int**) malloc(sizeof(int*) * (n+2));
    for(i=0; i<=n+1; i++) {
        Q[i] = (int*) malloc(sizeof(int) * (n+2));
        for(j=0; j<=n+1; j++) Q[i][j] = 0;
    }
}


void term() {
    int i;
    for(i=0; i<=n+1; i++) free(Q[i]);
    free(Q);
}


void putQ(int i) {
    int j, k, i2, j2;

    for(j=1; j<=n; j++) {
        for(i2=i-1; i2<=i+1; i2++) {
            for(j2=j-1; j2<=j+1; j2++)
                if(Q[i2][j2]) break;
            if(j2 != j+2) break;
        }
        
        if((i2==i+2) && (j2==j+2)) {
            for(k=1; k<=n; k++)
                if(Q[k][j]) break;

            if(k==n+1) {
                Q[i][j] = 1;
                if(i==n) {
                    makeAnser();
                    Q[i][j] = 0;
                    return;
                }

                putQ(i+1);
                Q[i][j] = 0;
            }
        }
    }
}


void makeAnser() {
    int i, j;

    if(num) {
        for(i=1; i<n; i++)
            for(j=1; j<=n; j++)
                if(Q[i][j]) {
                    printf("(%d, %d), ", i, j);
                    break;
                }
        for(j=1; j<=n; j++)
            if(Q[i][j]) {
                    printf("(%d, %d)\n", i, j);
                    break;
                }
    }

    if(bor) {
        for(i=1; i<=n; i++) {
            for(j=0; j<n; j++) printf("+-");
            printf("+\n");
            for(j=1; j<=n; j++)
                Q[i][j] ? printf("|o") : printf("| ");
            printf("|\n");
        }
        for(j=0; j<n; j++) printf("+-");
        printf("+\n\n");
    }
}