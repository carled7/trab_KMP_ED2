#include <stdio.h>
#include <iostream>
#include <list>
#include <string.h>
#include <cstring>

#define TAM 1000

using namespace std;

typedef struct nome{
    char fullName[40], invertedName[40];
} NOME;

void printList(NOME nomes[], int us){

    char buffer;
    if(!us){
        for(int i = 0; i < TAM; i++){
            printf("%d -  %s\n", i + 1, nomes[i].fullName);
        }
    }else{
        for(int i = 0; i < TAM; i++){
            printf("%d -  %s\n", i + 1, nomes[i].invertedName);
        }
    }
    printf("\nAperte qualquer tecla para voltar\n");
    cin >> buffer;

}

void pushToList(NOME nomes[], char nome[], int row, int check){

    if(check){
        strcpy(nomes[row].fullName, nome);
    }else{
        strcpy(nomes[row].invertedName, nome);
    }
}


void mergeA (NOME nomes[], int s, int m, int e){

    NOME tmp[(e - s) + 1];
    int i = s, j = m + 1, k = 0;

    while(i <= m && j <= e){

        if(strcmp(nomes[i].fullName, nomes[j].fullName) < 0)
            strcpy(tmp[k++].fullName, nomes[i++].fullName);

        else
            strcpy(tmp[k++].fullName, nomes[j++].fullName);
    }

    for(; i <= m; i++, k++)
        strcpy(tmp[k].fullName, nomes[i].fullName);


    for(; j <= e; j++, k++)
        strcpy(tmp[k].fullName, nomes[j].fullName);


    for(i = s, k = 0; i <= e; i++, k++)
        strcpy(nomes[i].fullName, tmp[k].fullName);

}

void mergeSort(NOME nomes[], int start, int theEnd){
    if (start < theEnd) {
        int middle = (start + theEnd) / 2;
        mergeSort(nomes, start, middle);
        mergeSort(nomes, middle +1, theEnd);

        mergeA(nomes, start, middle, theEnd);
       
    }
}

int hub(NOME nomes[]){

    int option, sorted, sortedUS;

    system("cls");
    printf("\n[1] - Ordem alfabetica\n");
    printf("[2] - Imprimir lista\n");
    printf("[0] - Encerrar programa\n");
    scanf(" %d", &option);

    switch(option){
    case 1:
        if(sorted != 1){
            mergeSort(nomes, 0, TAM);
            sorted = 1;
        }
        printList(nomes, 0);
        return option;
        break;
    case 2:
        printList(nomes, 0);
        return option;
        break;
    case 0:
        printf("\nPrograma encerrado...");
        return option;
        break;
    default:
        printf("\nInválido.");
        return -1;
        break;
    }

}


void readFile(NOME nomes[]){

    FILE* nome = fopen("nomes.txt", "r");
    char buffer[40];
    int row = 0;
    while(row < TAM){

        fscanf(nome,"%[^\n]\n", buffer);
        strcat(buffer, "\0");
        pushToList(nomes, buffer, row, 1);

        row++;
    }

    fclose(nome);

}

int main (){

    NOME nomes[TAM];

    readFile(nomes);
    int op = hub(nomes);

    while(op != 0){
        op = hub(nomes);
    }

    return 0;
}
