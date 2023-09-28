#include <stdio.h>
#include <stdlib.h>

struct s_pair{
    int num;
    int den;
};
typedef struct s_pair pair;

int contaZeri(pair* v, int length);

int compareRows(){};

int main(){
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    pair** A;
    int* nZeri;
    int m,n,t;
    int flag;
    char diviso;

    printf("inserisci '1' per leggere da file o '0' per leggere da terminale: ");
    scanf("%d", &flag);

    if(flag==1){
        fscanf(inputFile, "%d*%d", &m, &n);
    }else{
        printf("inserisci le dimensioni della matrice completa nel formato m*n: ");
        scanf("%d*%d", &m, &n);
    }

    A=(pair**)malloc(m*sizeof(pair*));
    nZeri=(int*)malloc(m*sizeof(int));
    for(int i=0;i<m;i++){
        A[i]=(pair*)malloc(n*sizeof(pair));
        for(int j=0;j<n;j++){
            A[i][j].den=1;
        }
    }

    if(flag){
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                fscanf(inputFile, "%d%c", &A[i][j].num, &diviso);
                if(diviso=='/')
                    fscanf(inputFile,"%d", &A[i][j].den);
            }
        }
    }else{
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                printf("inserisci l'elemento A[%d][%d]", i+1,j+1);
                scanf("%d%c", &A[i][j].num, &diviso);
                if(diviso=='/')
                    scanf("%d", &A[i][j].den);
            }
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            for(int t=2;t<=A[i][j].den && t<=A[i][j].num;t++){
                if(A[i][j].den%t==0 && A[i][j].num%t==0){
                    A[i][j].den/=t;
                    A[i][j].num/=t;
                    t=1;
                }
            }
        }
    }
    if(flag){
        for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    if(A[i][j].den>1)
                        fprintf(outputFile, "%d/%d\t", A[i][j].num, A[i][j].den);
                    else
                        fprintf(outputFile, "%d\t", A[i][j].num);
                }
            fprintf(outputFile, "\n");
        }
    }else{
        for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    printf("%d/%d\t", A[i][j].num, A[i][j].den);
                }
            printf("\n");
        }
    }

    for(int i=0;i<m;i++)
        nZeri[i]=contaZeri(A[i], n);

    qsort(A, m, sizeof(pair), compareRows);
    

    return 0;

}

int contaZeri(pair* v, int length){
    int x=0;
    for(int i=0;i<length;i++)
        if(v[i].num==0)
            x++;
    return x;
};