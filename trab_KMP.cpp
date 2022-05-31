#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <string.h>  
//#include <cstring>

#define TAM 1000

using namespace std;

typedef struct nome{
    char fullName[40], invertedName[40];
} NOME;

void calcPrefix(char p[], int lps[]) {
    lps[0] = 0;
    int i = 0, j = 1;
    while (j < strlen(p)) {
        if (p[i] == p[j]) {
            lps[j] = i + 1;
            i++;
            j++;
        } else if (p[i] != p[j] && i != 0) {
            i = lps[i - 1];
        } else if (p[i] != p[j]) {
            lps[j] = 0;
            j++;
        }
    }
}

int kmp(char t[], char p[]) {

    int lps[strlen(p)];
    calcPrefix(p, lps);

    int i = 0, j = 0, k, l = 0;

    while (i <= strlen(t)) {
        int r = i - j;
        k = j;
        for (l = i; j < strlen(p); j++, l++) {
            if (t[l] == p[j]) {
                k++;
            } else {
                break;
            }
        }
        if (k == strlen(p)) {
            return r;
        }
        if (lps[j - 1] == 0) {
            i = l + 1;
        } else {
            i = l;
        }
        j = lps[j - 1];
    }

    return -1;
}

int stringMatching(char t[], char p[]) { // O(|T| * |P|)
    int i, j, k, l;
    for (i = 0; i <= strlen(t) - strlen(p); i++) {
        k = 0;
        for (j = 0, l = i; j < strlen(p); j++, l++) {
            if (t[l] == p[j]) {
                k++;
            } else {
                break;
            }
        }
        if (k == strlen(p)) {
            return i;
        }
    }
    return -1;
}

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

void search(NOME nomes[]){

    char pattern[30];
    int kmpResult;

    system("clear");
    printf("\nDigite o nome que \ndeseja pesquisar: ");
    cin >> pattern;

    printf("\nRESULTADOS\n");
    for (int i = 0; i < TAM; i++)
    {
        kmpResult = kmp(nomes[i].fullName, pattern);
        if(kmpResult != -1){
            printf("- %s\n", nomes[i].fullName);
        }
    }
    
}

int hub(NOME nomes[]){

    int option;

    system("clear");
    printf("\n[1] - Pesquisar nome\n");
    printf("[2] - Imprimir lista\n");
    printf("[0] - Encerrar programa\n");
    scanf(" %d", &option);

    switch(option){
    case 1:
        search(nomes);
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
