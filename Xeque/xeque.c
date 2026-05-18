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

void verificaXeque(){}//chama todas as preves

int main(){
    //recebe a string e passa para a verifica que chama o forsyth e as preves, ela printa o resultado tbm
    return 0;
}