#include <stdio.h>
#include <stdlib.h>

struct s_pair{
    int num;
    int den;
};
typedef struct s_pair pair;

void semplificazione(int *a, int *b);

int contaZeri(pair* v, int length);

void insSort(int* zeri, pair** A, int aSize);

void riduzioneMat(pair** A, int *zeri, int m, int n);

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
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            semplificazione(&A[i][j].num, &A[i][j].den);

    for(int i=0;i<m;i++)
        nZeri[i]=contaZeri(A[i], n);

    insSort(nZeri, A, m);
    
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
    //riduzioneMat(A, nZeri, m, n);


    return 0;
}

void semplificazione(int *a, int *b){
    for(int t=2;t<=*a && t<=*b;t++)
        if(*a%t==0 && *b%t==0){
            *a/=t;
            *b/=t;
            t=1;
        }
}

int contaZeri(pair* v, int length){
    int x=0;
    for(int i=0;v[i].num==0;i++)
        x=i+1;
    return x;
};

void insSort(int* zeri, pair** A, int aSize){
    int t1, minNum;
    pair* t2;
    for(int i=0;i<aSize;i++){
        minNum=aSize;
        for(int j=i;j<aSize;j++){
            if(zeri[minNum]>zeri[j]){
                minNum=j;
            }
        }
        t1=zeri[minNum];
        zeri[minNum]=zeri[i];
        zeri[i]=t1;
        t2=A[minNum];
        A[minNum]=A[i];
        A[i]=t2;
    }
}

void riduzioneMat(pair** A, int *zeri, int m, int n){//la posizione del primo zero equivale a n_zeri-1
    int x,y;
    x=y=0;
    while(x<n && y<m){
        if(A[y][x].num==0){
            x++;
            continue;
        }
        if(A[y][x].num!=A[y][x].den){
            for(int j=0;j<n;j++){
                A[y][j].num*=A[y][x].den;
                A[y][j].den*=A[y][x].num;
                semplificazione(&A[y][j].den, &A[y][j].num);
            }
        }
        if(A[y][x].num==1){
            for(int i=y+1;i<m;i++){
                if(A[i][x].num>0)
                    for(int j=x;j<n;j++){
                        
                    }
            }
        }
    }
}