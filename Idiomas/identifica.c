/* A entrada é via teclado de uma frase em um dos três idiomas.
 A saída é o idioma da frase de entrada.
*/

// Carolina Hiroko Yamada / RA: 10741647
// Catarina Silva e Meirelles / RA: 10239324
// João Pedro Mazzante Alvarez / RA: 10723837

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // para strlen

void verificaQnt(char frase[], int freq[]) {
    // Inicializa o vetor com zeros
    for (int i = 0; i < 26; i++) freq[i] = 0;

    for (int i = 0; frase[i] != '\0'; i++) {
        // Se o bit mais significativo for 1, é um caractere especial (UTF-8), mas estamos trabalhando apenas com os 26 da ASCII
        //ignora qualquer caractere que não esteja na tabela ASCII padrão (que vai de 0 a 127).(ou seja, todos os caracteres acentuados)
        if ((unsigned char)frase[i] > 127) {
            continue; 
        }

        char letra = tolower(frase[i]);
        if (letra >= 'a' && letra <= 'z') {
            freq[letra - 'a']++;
        //Como os caracteres na tabela ASCII são sequenciais:
        //Se a letra for 'a': 'a' - 'a' = $97 - 97 = 0$ (Índice 0)
        //Se a letra for 'b': 'b' - 'a' = $98 - 97 = 1$ (Índice 1)
        //Se a letra for 'z': 'z' - 'a' = $122 - 97 = 25$ (Índice 25)
        }
   }
}

 int compara(int freq[], int tamanho, float taxaErro, char frase[]) {
    if (tamanho == 0) return -1;
    
    float freqN[26];
    for (int i = 0; i < 26; i++) {
        freqN[i] = (float)freq[i] / tamanho;
    }

    // Vetor de probabilidade de cada letra em Português
    float probPort[26] = {0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0128, 0.0618, 0.0040, 0.0002, 0.0278, 0.0474, 0.0505, 0.1073, 0.0252, 0.0120, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167, 0.0001, 0.0021, 0.0001, 0.0047};
    // Vetor de probabilidade de cada letra em Inglês
    float probIng[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};    
    // Vetor de probabilidade de cada letra em Esperanto
    float probEsp[26] = {0.1212, 0.0092, 0.0078, 0.0304, 0.0899, 0.0103, 0.0117, 0.0037, 0.1001, 0.0350, 0.0416, 0.0614, 0.0299, 0.0796, 0.0878, 0.0274, 0.00, 0.0591, 0.0609, 0.0527, 0.0318, 0.0190, 0.00, 0.00, 0.00, 0.0050};
    
    // Variáveis para contar quantas letras estão dentro da taxa de erro para cada idioma
    int pt = 0, ing = 0, esp = 0;

    for (int i = 0; i < 26; i++) {
        // Verifficação de qual idioma tem a frequência mais próxima da frase
        // Se a frequência da letra serve para os três, os três ganham ponto.
        
        if (freqN[i] >= probPort[i] - taxaErro && freqN[i] <= probPort[i] + taxaErro) {
            pt++;
        } 
        if (freqN[i] >= probIng[i] - taxaErro && freqN[i] <= probIng[i] + taxaErro) {
            ing++;
        } 
        if (freqN[i] >= probEsp[i] - taxaErro && freqN[i] <= probEsp[i] + taxaErro) {
            esp++;
        }

        // Regra de exclusão (se a letra existe na frase mas não no alfabeto do idioma)
        // -200 para não influenciar na contagem de pontos, mas garantir que o idioma seja desconsiderado.
        if (probPort[i] == 0 && freqN[i] != 0)
            pt = -200;
        if (probIng[i] == 0 && freqN[i] != 0)
            ing = -200;
        if (probEsp[i] == 0 && freqN[i] != 0)
            esp = -200;
    }

    // Retorno do idioma com mais pontos, ou mensagem de erro se nenhum for identificado
    if (pt > ing && pt > esp) {
        return 1;
    }
    if (ing > pt && ing > esp) {
        return 2;
    }
    if (esp > pt && esp > ing) {
        return 3;
    }

    return -1; // Nenhum idioma identificado
}

int main () {
    char frase[256];
    int freq[26];
    printf("Digite uma frase (em inglês, português ou esperanto): ");
    scanf("%[^\n]", frase); // Lê a frase até a quebra de linha

    // Para contar apenas as letras válidas de A até Z
    int tamanho = 0;
    for (int i = 0; frase[i] != '\0'; i++) {
        if ((unsigned char)frase[i] <= 127) {
            char c = tolower(frase[i]);
            if (c >= 'a' && c <= 'z') {
                tamanho++;
            }
        }
    }

    // Calcula a taxa de erro
    // Diminui de acordo com a quantidade de letras
 
    float taxaErro;
 
    if (tamanho > 0 && tamanho <= 10) taxaErro = 0.15; // Menos letras = maior taxa
    if (tamanho > 10 && tamanho <= 40) taxaErro = 0.1;
    if (tamanho > 40) taxaErro = 0.05; // Mais letras = menor taxa
 
    verificaQnt(frase, freq); // Chamada da função para contar a quantidade de vezes que cada letra aparece na frase
 
    int resultado = compara(freq, tamanho, taxaErro, frase); // Chamada da função que identifica o idioma da frase

    printf("Frase: %s\n", frase);
 
    printf("O idioma da frase é: ...\n");

    // Switch case para decidir o que será printado de acordo com o retorno
    switch (resultado) {
        case 1:
            printf("Português.\n");
            break;
        case 2:
            printf("Inglês.\n");
            break;
        case 3:
            printf("Esperanto.\n");
            break;
        case -1:
        default:
            printf("Erro! Idioma não identificado.\n");
            break;
    }
  
    return 0;
}
