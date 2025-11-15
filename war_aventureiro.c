#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território no mapa
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército controlador
    int tropas;        // Número de tropas presentes
};

// Função para cadastrar os territórios no sistema
void cadastrarTerritorios(struct Territorio* mapa, int quantidade) {
    int i;

    printf("=== CADASTRO DE TERRITÓRIOS ===\n\n");

    for (i = 0; i < quantidade; i++) {
        printf("--- TERRITÓRIO %d ---\n", i + 1);

        printf("Nome do território: ");
        scanf(" %29s", (mapa + i)->nome);

        printf("Cor do exército: ");
        scanf(" %9s", (mapa + i)->cor);

        printf("Número de tropas: ");
        scanf("%d", &(mapa + i)->tropas);

        printf("\n");
    }
}

// Função que exibe todos os territórios cadastrados
void mostrarTerritorios(struct Territorio* mapa, int quantidade) {
    int i;

    printf("\n=== MAPA ATUAL ===\n");

    for (i = 0; i < quantidade; i++) {
        printf("%d. %s (Exército %s) - %d tropas\n",
               i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("\n");
}

// Função que simula uma batalha entre dois territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante, dadoDefensor;

    // Simula os dados de batalha (1 a 6)
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;

    printf("\n--- BATALHA EM CURSO ---\n");
    printf("Atacante (%s) rolou: %d\n", atacante->cor, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->cor, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITÓRIA do atacante!\n");

        // O território muda de dono
        strcpy(defensor->cor, atacante->cor);

        // Transfere metade das tropas do atacante
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        printf("O território %s agora pertence ao exército %s!\n",
               defensor->nome, defensor->cor);
    } else {
        printf("VITÓRIA do defensor!\n");

        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }

        printf("O território %s resiste ao ataque!\n", defensor->nome);
    }

    printf("Tropas restantes - Atacante: %d, Defensor: %d\n\n",
           atacante->tropas, defensor->tropas);
}

// Função para validar se o ataque é permitido
int validarAtaque(struct Territorio* atacante, struct Territorio* defensor) {
    // Não pode atacar território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Não é possível atacar um território da própria cor!\n");
        return 0;
    }

    // Atacante deve ter pelo menos 2 tropas
    if (atacante->tropas < 2) {
        printf("Erro: O atacante precisa ter pelo menos 2 tropas!\n");
        return 0;
    }

    return 1;
}

// Função para liberar a memória alocada
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    struct Territorio* territorios;
    int numTerritorios, opcao;
    int indiceAtacante, indiceDefensor;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("=== SISTEMA DE GUERRA TERRITORIAL ===\n\n");

    // Solicita o número de territórios
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &numTerritorios);

    // Aloca memória dinamicamente para os territórios
    territorios = (struct Territorio*)calloc(numTerritorios, sizeof(struct Territorio));

    if (territorios == NULL) {
        printf("Erro: Não foi possível alocar memória!\n");
        return 1;
    }

    // Cadastra os territórios
    cadastrarTerritorios(territorios, numTerritorios);

    // Loop principal do jogo
    do {
        mostrarTerritorios(territorios, numTerritorios);

        printf("=== MENU DE AÇÕES ===\n");
        printf("1. Realizar ataque\n");
        printf("2. Ver mapa atual\n");
        printf("0. Sair do jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nEscolha o território atacante (1-%d): ", numTerritorios);
                scanf("%d", &indiceAtacante);
                indiceAtacante--; // Ajusta para índice do array

                printf("Escolha o território defensor (1-%d): ", numTerritorios);
                scanf("%d", &indiceDefensor);
                indiceDefensor--; // Ajusta para índice do array

                // Valida os índices
                if (indiceAtacante < 0