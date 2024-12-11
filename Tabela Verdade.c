// Guilherme Henrique Yamaguchi Davelli
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;  // Número de variáveis
    int linhas;  // Número de linhas na tabela verdade
    char variaveis[7][2];  // Array para armazenar os nomes das variáveis
    char saidas[128];  // Array para armazenar as saídas (0 ou 1)

    // Passo 1: Determinar o número de variáveis (2 a 7)
    do {
        printf("Digite o número de variáveis (2 a 7): ");
        scanf("%d", &n);
    } while (n < 2 || n > 7);  // Garantir que o número de variáveis esteja entre 2 e 7

    // Número de linhas da tabela é 2 elevado a N
    linhas = (int)pow(2, n);

    // Exibir o número de linhas da tabela
    printf("Número de linhas da tabela verdade: %d\n", linhas);

    // Passo 2: Determinar os nomes das variáveis
    printf("\nDigite o nome das variáveis (A, B, C, etc.):\n");
    for (int i = 0; i < n; i++) {
        printf("Digite o nome da variável %d: ", i + 1);
        scanf(" %c", &variaveis[i][0]);  // Armazenar o nome da variável
    }

    // Passo 3: Inserção ou geração aleatória das saídas
    char escolha;
    printf("\nDeseja inserir as saídas manualmente? (S para sim, N para não): ");
    scanf(" %c", &escolha);

    if (escolha == 'S' || escolha == 's') {
        // Solicitar as saídas (0 ou 1)
        printf("\nDigite as saídas (0 ou 1) para cada linha da tabela verdade:\n");
        for (int i = 0; i < linhas; i++) {
            do {
                printf("Saída para linha %d: ", i + 1);
                scanf(" %c", &saidas[i]);  // Armazenar a saída
            } while (saidas[i] != '0' && saidas[i] != '1');  // Garantir que a saída seja 0 ou 1
        }
    } else {
        // Gerar saídas aleatórias
        srand(time(NULL));  // Inicializa o gerador de números aleatórios
        for (int i = 0; i < linhas; i++) {
            saidas[i] = (rand() % 2) + '0';  // Gera aleatoriamente '0' ou '1'
        }
    }

    // Passo 7: Exibir a tabela verdade completa
    printf("\nTabela Verdade Completa\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t", variaveis[i][0]);
    }
    printf("Saída\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < linhas; i++) {
        // Exibir valores das variáveis em binário para cada linha
        for (int j = 0; j < n; j++) {
            int valor = (i >> (n - j - 1)) & 1;  // Calcula o valor binário da variável
            printf("%d\t", valor);
        }
        printf("%c\n", saidas[i]);  // Exibir a saída correspondente
    }

    // Função para contar operações AND, OR e NOT
    void contar_operacoes(int minTermosCount, int maxTermosCount) {
        printf("\nContagem de operações:\n");
        printf("Total de AND: %d\n", minTermosCount * n + maxTermosCount * n);  // Mintermos e Maxtermos, operações de AND
        printf("Total de OR: %d\n", minTermosCount - 1 + maxTermosCount - 1);  // Operações de OR
        printf("Total de NOT: %d\n", minTermosCount * n + maxTermosCount * n);  // Operações de NOT
    }

    // Passo 5: Mintermos (Soma de Produtos)
    int minTermosCount = 0;
    for (int i = 0; i < linhas; i++) {
        if (saidas[i] == '1') {
            minTermosCount++;
        }
    }

    // Passo 4: Maxtermos (Produto de Somas)
    int maxTermosCount = 0;
    for (int i = 0; i < linhas; i++) {
        if (saidas[i] == '0') {
            maxTermosCount++;
        }
    }

    // Exibir a função canônica - Mintermos
    printf("\nFunção Canônica - Soma de Produtos (Mintermos):\n");
    printf("Y = ");
    for (int i = 0; i < linhas; i++) {
        if (saidas[i] == '1') {
            if (minTermosCount > 1) {
                printf(" + ");
            }

            int binario = i;
            printf("(");
            for (int j = 0; j < n; j++) {
                if ((binario & (1 << (n - j - 1))) == 0) {
                    printf("%c'", variaveis[j][0]);
                    if (j != n - 1) printf("*");
                } else {
                    printf("%c", variaveis[j][0]);
                    if (j != n - 1) printf("*");
                }
            }
            printf(")");
            minTermosCount--;
        }
    }

    printf("\n");

    // Exibir a função canônica - Maxtermos
    printf("\nFunção Canônica - Produto de Somas (Maxtermos):\n");
    printf("Y = ");
    for (int i = 0; i < linhas; i++) {
        if (saidas[i] == '0') {
            if (maxTermosCount > 1) {
                printf(" * ");
            }

            int binario = i;
            printf("(");
            for (int j = 0; j < n; j++) {
                if ((binario & (1 << (n - j - 1))) == 0) {
                    printf("%c", variaveis[j][0]);
                    if (j != n - 1) printf("+");
                } else {
                    printf("%c'", variaveis[j][0]);
                    if (j != n - 1) printf("+");
                }
            }
            printf(")");
            maxTermosCount--;
        }
    }

    printf("\n");

    // Comparar o número de operações entre Mintermos e Maxtermos
    printf("\nComparação entre Mintermos e Maxtermos:\n");
    printf("Operações para Mintermos:\n");
    contar_operacoes(minTermosCount, maxTermosCount);

    printf("\nEscolha a melhor função com base no número de operações.\n");

    return 0;
}
