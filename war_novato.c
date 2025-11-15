#include <stdio.h>
#include <string.h>

// Definição da estrutura para representar um território
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército que ocupa o território
    int tropas;        // Quantidade de tropas no território
};

int main() {
    // Declaração do vetor para armazenar os 5 territórios
    struct Territorio territorios[5];
    int i;

    printf("=== SISTEMA DE CADASTRO DE TERRITÓRIOS ===\n\n");
    printf("Você irá cadastrar 5 territórios. Para cada um, informe:\n");
    printf("- Nome do território\n");
    printf("- Cor do exército\n");
    printf("- Número de tropas\n\n");

    // Loop para coletar dados dos 5 territórios
    for (i = 0; i < 5; i++) {
        printf("--- TERRITÓRIO %d ---\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do território: ");
        scanf(" %29s", territorios[i].nome);

        // Leitura da cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %9s", territorios[i].cor);

        // Leitura da quantidade de tropas
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("=== TERRITÓRIOS CADASTRADOS ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("TERRITÓRIO %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    // Cálculo e exibição do total de tropas
    int total_tropas = 0;
    for (i = 0; i < 5; i++) {
        total_tropas += territorios[i].tropas;
    }

    printf("\nTOTAL DE TROPAS EM TODOS OS TERRITÓRIOS: %d\n", total_tropas);

    return 0;
}