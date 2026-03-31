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

char* compara(int freq[], int tamanho, float taxaErro, char frase[]) {
    if (tamanho == 0)
        return "Erro: Frase vazia";
    
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

        // Regra de inclusão (para letras duplas que só tem em uma língua, como o "ll" do inglês, ou o "rr" do português)
        // Transforma para minúsculo para facilitar a busca
        char c1 = tolower(frase[i]);
        char c2 = tolower(frase[i+1]);

        // Inglês:  "ll", "th", "wh", "sh", "ee", "oo", "ck" (duplas mais frequentes no inglês)
        if (c1 == 'l' && c2 == 'l' || c1 == 't' && c2 == 'h' || c1 == 'w' && c2 == 'h' || c1 == 's' && c2 == 'h' || c1 == 'e' && c2 == 'e' || c1 == 'o' && c2 == 'o' || c1 == 'c' && c2 == 'k') {
            ing += 2; // Dá um bônus de 2 pontos para o Inglês
        }

        // Português: "lh", "nh", "qu", "rr", "ss" (duplas mais frequentes no português)
        if ((c1 == 'l' && c2 == 'h') || (c1 == 'n' && c2 == 'h') || (c1 == 'q' && c2 == 'u') || (c1 == 'r' && c2 == 'r') || (c1 == 's' && c2 == 's')) {
            pt += 2;
        }

        // Esperanto: "kv", "oj", "aj", "uj", "sc", "gv" (duplas mais frequentes no esperanto)
        if (c1 == 'k' && c2 == 'v' || c1 == 'o' && c2 == 'j' || c1 == 'a' && c2 == 'j' || c1 == 'u' && c2 == 'j' || c1 == 's' && c2 == 'c' || c1 == 'g' && c2 == 'v') {
            esp += 2;
        }    
    }

    // Retorno do idioma com mais pontos, ou mensagem de erro se nenhum for identificado
    if (pt > ing && pt > esp) {
        return "Portugues";
    }
    if (ing > pt && ing > esp) {
        return "Ingles";
    }
    if (esp > pt && esp > ing) {
        return "Esperanto";
    }

    return "Nenhum idioma identificado / Erro";
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

    //Coloca taxa de erro em 0.15 para 15%, para não ocorrer erros em frases curtas

    //aqui vamos voltar pra fazer o codigo

    printf("Frase: %s\n", frase);
    printf("O idioma da frase é: ...\n"); // Aqui deve ser a lógica para identificar o idioma
    return 0;
}