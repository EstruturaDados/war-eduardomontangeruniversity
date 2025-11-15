#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território no jogo
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército controlador
    int tropas;        // Número de tropas presentes
};

// Estrutura que representa um jogador
struct Jogador {
    char nome[20];     // Nome do jogador
    char cor[10];      // Cor do exército do jogador
    char* missao;      // Missão atribuída ao jogador
};

// Declaração do vetor de missões disponíveis
char* missoesPredefinidas[] = {
    "Conquistar 4 territórios consecutivos",
    "Eliminar todas as tropas vermelhas do mapa", 
    "Controlar pelo menos 60% dos territórios",
    "Acumular mais de 30 tropas em um único território",
    "Conquistar territórios de 3 cores diferentes",
    "Dominar todos os territórios com nome iniciado em 'A'",
    "Manter controle de 5 territórios por 3 turnos consecutivos"
};

// Função para cadastrar territórios no mapa
void cadastrarTerritorios(struct Territorio* mapa, int quantidade) {
    int i;
    
    printf("=== CONFIGURAÇÃO DO MAPA ===\n\n");
    
    for (i = 0; i < quantidade; i++) {
        printf("--- TERRITÓRIO %d ---\n", i + 1);
        
        printf("Nome do território: ");
        scanf(" %29s", (mapa + i)->nome);
        
        printf("Cor inicial do exército: ");
        scanf(" %9s", (mapa + i)->cor);
        
        printf("Tropas iniciais: ");
        scanf("%d", &(mapa + i)->tropas);
        
        printf("\n");
    }
}

// Função para configurar jogadores
void configurarJogadores(struct Jogador* jogadores, int numJogadores) {
    int i;
    
    printf("=== CONFIGURAÇÃO DOS JOGADORES ===\n\n");
    
    for (i = 0; i < numJogadores; i++) {
        printf("--- JOGADOR %d ---\n", i + 1);
        
        printf("Nome do jogador: ");
        scanf(" %19s", jogadores[i].nome);
        
        printf("Cor do seu exército: ");
        scanf(" %9s", jogadores[i].cor);
        
        printf("\n");
    }
}

// Função que atribui uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceAleatorio = rand() % totalMissoes;
    
    // Aloca memória para a missão do jogador
    destino = (char*)malloc(strlen(missoes[indiceAleatorio]) + 1);
    
    if (destino != NULL) {
        strcpy(destino, missoes[indiceAleatorio]);
    }
}

// Função que sorteia missões para todos os jogadores
void sortearMissoes(struct Jogador* jogadores, int numJogadores) {
    int i;
    int totalMissoes = sizeof(missoesPredefinidas) / sizeof(missoesPredefinidas[0]);
    
    for (i = 0; i < numJogadores; i++) {
        int indiceAleatorio = rand() % totalMissoes;
        
        // Aloca memória para a missão
        jogadores[i].missao = (char*)malloc(strlen(missoesPredefinidas[indiceAleatorio]) + 1);
        
        if (jogadores[i].missao != NULL) {
            strcpy(jogadores[i].missao, missoesPredefinidas[indiceAleatorio]);
        }
    }
}

// Função que exibe a missão de um jogador (passagem por valor)
void exibirMissao(char missao[]) {
    if (missao != NULL) {
        printf("Sua missão: %s\n", missao);
    }
}

// Função que conta territórios controlados por uma cor
int contarTerritoriosCor(struct Territorio* mapa, int tamanho, char* cor) {
    int contador = 0;
    int i;
    
    for (i = 0; i < tamanho; i++) {
        if (strcmp((mapa + i)->cor, cor) == 0) {
            contador++;
        }
    }
    
    return contador;
}

// Função que verifica o cumprimento da missão
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char* corJogador) {
    int i;
    
    // Verifica missão: Conquistar 4 territórios consecutivos
    if (strstr(missao, "4 territórios consecutivos") != NULL) {
        int consecutivos = 0;
        int maxConsecutivos = 0;
        
        for (i = 0; i < tamanho; i++) {
            if (strcmp((mapa + i)->cor, corJogador) == 0) {
                consecutivos++;
                if (consecutivos > maxConsecutivos) {
                    maxConsecutivos = consecutivos;
                }
            } else {
                consecutivos = 0;
            }
        }
        return maxConsecutivos >= 4;
    }
    
    // Verifica missão: Eliminar tropas vermelhas
    if (strstr(missao, "tropas vermelhas") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp((mapa + i)->cor, "vermelha") == 0) {
                return 0; // Ainda existe território vermelho
            }
        }
        return 1;
    }
    
    // Verifica missão: Controlar 60% dos territórios
    if (strstr(missao, "60%") != NULL) {
        int territoriosControlados = contarTerritoriosCor(mapa, tamanho, corJogador);
        return territoriosControlados >= (tamanho * 0.6);
    }
    
    // Verifica missão: Acumular mais de 30 tropas
    if (strstr(missao, "30 tropas") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp((mapa + i)->cor, corJogador) == 0 && (mapa + i)->tropas > 30) {
                return 1;
            }
        }
    }
    
    return 0; // Missão não cumprida
}

// Função que exibe o mapa atual
void mostrarTerritorios(struct Territorio* mapa, int quantidade) {
    int i;
    
    printf("\n=== SITUAÇÃO ATUAL DO MAPA ===\n");
    
    for (i = 0; i < quantidade; i++) {
        printf("%d. %s [%s] - %d tropas\n", 
               i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("\n");
}

// Função que simula batalha entre territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtacante, dadoDefensor;
    
    dadoAtacante = rand() % 6 + 1;
    dadoDefensor = rand() % 6 + 1;
    
    printf("\n--- RESOLUÇÃO DA BATALHA ---\n");
    printf("Exército %s (atacante) rolou: %d\n", atacante->cor, dadoAtacante);
    printf("Exército %s (defensor) rolou: %d\n", defensor->cor, dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        printf("VITÓRIA para o atacante!\n");
        
        strcpy(defensor->cor, atacante->cor);
        
        int tropasEnviadas = atacante->tropas / 2;
        defensor->tropas = tropasEnviadas;
        atacante->tropas -= tropasEnviadas;
        
        printf("Território %s conquistado pelo exército %s!\n", 
               defensor->nome, defensor->cor);
    } else {
        printf("RESISTÊNCIA bem sucedida!\n");
        
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
        
        printf("Território %s mantém-se sob controle %s!\n", 
               defensor->nome, defensor->cor);
    }
    
    printf("Situação pós-batalha - Atacante: %d tropas, Defensor: %d tropas\n\n", 
           atacante->tropas, defensor->tropas);
}

// Função que valida se o ataque pode ser realizado
int validarAtaque(struct Territorio* atacante, struct Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Não é possível atacar território aliado!\n");
        return 0;
    }
    
    if (atacante->tropas < 2) {
        printf("Erro: Território atacante precisa ter pelo menos 2 tropas!\n");
        return 0;
    }
    
    return 1;
}

// Função que verifica se algum jogador venceu
int verificarVitoria(struct Jogador* jogadores, int numJogadores, 
                     struct Territorio* mapa, int numTerritorios) {
    int i;
    
    for (i = 0; i < numJogadores; i++) {
        if (verificarMissao(jogadores[i].missao, mapa, numTerritorios, jogadores[i].cor)) {
            printf("\n=== VITÓRIA! ===\n");
            printf("Jogador %s (%s) completou sua missão!\n", 
                   jogadores[i].nome, jogadores[i].cor);
            exibirMissao(jogadores[i].missao);
            return 1;
        }
    }
    
    return 0;
}

// Função para liberar toda a memória alocada
void liberarMemoria(struct Territorio* mapa, struct Jogador* jogadores, int numJogadores) {
    int i;
    
    // Libera as missões dos jogadores
    for (i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao != NULL) {
            free(jogadores[i].missao);
        }
    }
    
    // Libera o vetor de jogadores
    free(jogadores);
    
    // Libera o mapa
    free(mapa);
}

int main() {
    struct Territorio* territorios;
    struct Jogador* jogadores;
    int numTerritorios, numJogadores;
    int opcao, turnoAtual = 1;
    int indiceAtacante, indiceDefensor;
    
    srand(time(NULL));
    
    printf("=== GUERRA ESTRATÉGICA COM MISSÕES ===\n\n");
    
    // Configuração inicial
    printf("Número de territórios: ");
    scanf("%d", &numTerritorios);
    
    printf("Número de jogadores: ");
    scanf("%d", &numJogadores);
    
    // Aloca memória para territórios e jogadores
    territorios = (struct Territorio*)calloc(numTerritorios, sizeof(struct Territorio));
    jogadores = (struct Jogador*)calloc(numJogadores, sizeof(struct Jogador));
    
    if (territorios == NULL || jogadores == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        return 1;
    }
    
    // Configuração do jogo
    cadastrarTerritorios(territorios, numTerritorios);
    configurarJogadores(jogadores, numJogadores);
    sortearMissoes(jogadores, numJogadores);
    
    // Exibe as missões para cada jogador
    printf("\n=== MISSÕES ATRIBUÍDAS ===\n");
    for (int i = 0; i < numJogadores; i++) {
        printf("\n%s (%s):\n", jogadores[i].nome, jogadores[i].cor);
        exibirMissao(jogadores[i].missao);
    }
    printf("\n");
    
    // Loop principal do jogo
    do {
        printf("\n--- TURNO %d ---\n", turnoAtual);
        mostrarTerritorios(territorios, numTerritorios);
        
        printf("=== AÇÕES DISPONÍVEIS ===\n");
        printf("1. Executar ataque\n");
        printf("2. Consultar mapa\n");
        printf("3. Ver missões dos jogadores\n");
        printf("0. Finalizar jogo\n");
        printf("Sua escolha: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("\nTerritório atacante (1-%d): ", numTerritorios);
                scanf("%d", &indiceAtacante);
                indiceAtacante--;
                
                printf("Território defensor (1-%d): ", numTerritorios);
                scanf("%d", &indiceDefensor);
                indiceDefensor--;
                
                if (indiceAtacante < 0 || indiceAtacante >= numTerritorios ||
                    indiceDefensor < 0 || indiceDefensor >= numTerritorios) {
                    printf("Erro: Índices de território inválidos!\n");
                    break;
                }
                
                if (validarAtaque(&territorios[indiceAtacante], &territorios[indiceDefensor])) {
                    atacar(&territorios[indiceAtacante], &territorios[indiceDefensor]);
                    turnoAtual++;
                    
                    // Verifica condições de vitória após cada ataque
                    if (verificarVitoria(jogadores, numJogadores, territorios, numTerritorios)) {
                        opcao = 0; // Finaliza o jogo
                    }
                }
                break;
                
            case 2:
                // Mapa já é exibido no início de cada turno
                break;
                
            case 3:
                printf("\n=== MISSÕES EM ANDAMENTO ===\n");
                for (int i = 0; i < numJogadores; i++) {
                    printf("\n%s (%s):\n", jogadores[i].nome, jogadores[i].cor);
                    exibirMissao(jogadores[i].missao);
                }
                printf("\n");
                break;
                
            case 0:
                printf("Encerrando partida...\n");
                break;
                
            default:
                printf("Opção não reconhecida!\n");
        }
        
    } while (opcao != 0);
    
    // Limpa a memória antes de finalizar
    liberarMemoria(territorios, jogadores, numJogadores);
    
    printf("Memória liberada. Jogo finalizado.\n");
    
    return 0;
}