/* A entrada é via teclado de uma frase em um dos dois idiomas.
 A saída é o idioma da frase de entrada.
 Comente e idente seu programa.
*/

// Carol Hiroko Yamada / RA: 10741647
// Catarina Silva e Meirelles / RA: 10239324
//João Pedro Mazzante Alvarez / RA: 10723837

#include <stdio.h>
#include <stdlib.h>

int verificaQnt(char frase[]) {
    // Vai separar a frase em vetor e contar a quantidade de palavras
    // com return de freq[], que é o vetor que vai dar ser: freq[0] = qntd de a ...
    // até freq[25] = qntd de z
}

int compara(char frase[], int freq[], int tamanho, float taxaErro) {
    // Pega a frequência de cada letra e divide por 'n' ou tamanho
    int freqN[26];
    for (int i = 0; i < 26; i++) {
        freqN[i] = freq[i] / tamanho;
    }
    // Vetor de probabilidade de cada letra em Português
    int probPort[26] = {0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0128, 0.0618, 0.0040, 0.0002, 0.0278, 0.0474, 0.0505, 0.1073, 0.0252, 0.0120, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167, 0.0001, 0.0021, 0.0001, 0.0047}; 
    // Vetor de probabilidade de cada letra em Inglês
    int probIng[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};
    // Vetor de probabilidade de cada letra em Esperanto
    int probEsp[26] = {0.1212, 0.0092, 0.0078, 0.0304, 0.0899, 0.0103, 0.0117, 0.0037, 0.1001, 0.0350, 0.0416, 0.0614, 0.0299, 0.0796, 0.0878, 0.0274, 0.00, 0.0591, 0.0609, 0.0527, 0.0318, 0.0190, 0.00, 0.00, 0.00, 0.0050};
    // Variáveis para contar quantas letras estão dentro da taxa de erro para cada idioma
    int pt = 0; 
    int ing = 0;
    int esp = 0;
    int nem = 0;
    // Variáveis para a conta de comparação da frequência com a probabilidade, para cada idioma
    int diff1, diff2, diff3;

    for (int i = 0; i < 26; i++) {
        // Verifficação de qual idioma tem a frequência mais próxima da frase
        if (freqN[i] >= probPort[i] - taxaErro && freqN[i] <= probPort[i] + taxaErro) {
            pt++;
        } else if (freqN[i] >= probIng[i] - taxaErro && freqN[i] <= probIng[i] + taxaErro) {
            ing++;
        } else if (freqN[i] >= probEsp[i] - taxaErro && freqN[i] <= probEsp[i] + taxaErro) {
            esp++;
        } else {
            nem++;
        }
        // Retirada do idioma caso a probabilidade seja 0 e a frequência da letra seja diferente de 0
        // ou seja, a letra existe na frase mas não existe no idioma
        if (probPort[i] == 0 && freqN[i] != 0) 
            pt = 0;
        if (probIng[i] == 0 && freqN[i] != 0)
            ing = 0;
        if (probEsp[i] == 0 && freqN[i] != 0)
            esp = 0;
    }
    if (pt > ing && pt > esp) {
        return "Portugues";
    } else if (ing > pt && ing > esp) {
        return "Ingles";
    } else if (esp > pt && esp > ing) {
        return "Esperanto";
    } else {
        return "Nenhum idioma identificado / Erro";
    }
}

int main () {
    printf("Digite uma frase(em inglês, português ou esperanto): ");
    char frase[100];
    scanf("%[^\n]", frase); // Lê a frase até a quebra de linha

    int tamanho = 0;
    for (int i = 0; frase[i] != '\0'; i++) {
        if (frase[i] == ' ') {
            tamanho++;
        }
    }
    tamanho++; // Adiciona 1 para contar a última palavra

    printf("Digite a taxa de erro que quer pode existir (quanto maior, mais provável): ");
    float taxaErro;
    scanf("%f", &taxaErro);

    //aqui vamos voltar pra fazer o codigo

    printf("Frase: %s\n", frase);
    printf("O idioma da frase é: ...\n"); // Aqui deve ser a lógica para identificar o idioma
    return 0;
}