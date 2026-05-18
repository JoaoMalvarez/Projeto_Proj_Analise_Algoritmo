/*
Nome: Catarina Silva e Meirelles, RA:10239324
Nome: João Pedro Mazzante Alvarez, RA:10723837
Nome: Lívia Calado de Carvalho Dias, RA: 10737709
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // para strlen

void vetorizarForsyth(char forsyth[]){
    const char quebra[] = "-";
    char destino[8][8];
    char *parte = strtok(forsyth, quebra);
    int i = 0;
    
    while(parte != NULL && i < 8){
        int j = 0; // Controla a coluna atual do tabuleiro
        
        for (int k = 0; parte[k] != '\0' && j < 8; k++){
            if(isdigit(parte[k])){
                int casas_vazias = parte[k] - '0';
                
                for(int v = 0; v < casas_vazias && j < 8; v++){
                    destino[i][j] = '_';
                    j++; 
                }
            }
            else{
                destino[i][j] = parte[k];
                j++;
            }
        }
        
        i++;
        parte = strtok(NULL, quebra);
    }
    
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            printf("%c ,", destino[i][j]);
        }
        printf("\n");
    }
}


void preveDama(){}
void preveCavalo(){}
void preveBispo(){}
void preveTorre(){}
void prevePeao(){}

void imprimirTabuleiro() {
    printf("\nTabuleiro:\n");
    printf("  a b c d e f g h\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", 8 - i); // linhas do xadrez: 8 até 1
        for (int j = 0; j < 8; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}

bool verificaXeque(char rei) {
    return preveDama() || preveCavalo() || preveBispo()  || preveTorre()  || prevePeao();
}
int main(){
    char forsyth[72];
    printf("Escreva a notação do tabuleiro em Forsyth: ");
    scanf("%71s", forsyth);

    vetorizarForsyth(forsyth);
    imprimirTabuleiro();

    // Verifica xeque para ambos os reis
    bool xequeBranco = verificaXeque('K'); // rei branco
    bool xequePreto  = verificaXeque('k'); // rei preto

    // Resposta
    if(xequeBranco || xequePreto == true) { 
        printf("TRUE");
    else { 
        printf("FALSE");
        
    return 0;
}
