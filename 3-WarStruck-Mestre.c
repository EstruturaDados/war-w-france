#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5 // Número fixo de territórios

// Estrutura que representa um território no mapa
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército dominante
    int tropas;        // Quantidade de tropas no território
};

// Função que inicializa os territórios com nomes, cores e tropas aleatórias
void inicializarTerritorios(struct Territorio *territorios) {
    const char *nomes[] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo"};
    const char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Preto"};

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);         // Define nome
        strcpy(territorios[i].cor, cores[i]);          // Define cor
        territorios[i].tropas = rand() % 5 + 3;        // Tropas entre 3 e 7
    }
}

// Função que exibe o estado atual do mapa com todos os territórios
void exibirMapa(const struct Territorio *territorios) {
    printf("=== Mapa Atual ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", i+1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }
    printf("------------------\n");
}

// Função que simula uma batalha entre dois territórios
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    int dadoAtaque = rand() % 6 + 1; // Simula dado de ataque (1 a 6)
    int dadoDefesa = rand() % 6 + 1; // Simula dado de defesa (1 a 6)

    // Exibe os dados sorteados
    printf("Ataque: %s (%d tropas) - Dado: %d\n", atacante->nome, atacante->tropas, dadoAtaque);
    printf("Defesa: %s (%d tropas) - Dado: %d\n", defensor->nome, defensor->tropas, dadoDefesa);

    // Lógica de combate
    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas--; // Defensor perde 1 tropa
        if (defensor->tropas <= 0) {
            // Território conquistado: cor muda e tropas mínimas são atribuídas
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
            printf("Território conquistado!\n");
        } else {
            printf("Defensor perdeu 1 tropa!\n");
        }
    } else {
        printf("Defensor resistiu ao ataque!\n");
    }
}

// Função que verifica se a missão foi cumprida
// Missão: conquistar 3 territórios que não sejam da cor Verde
int verificarMissao(const struct Territorio *territorios) {
    int conquistados = 0;
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(territorios[i].cor, "Verde") != 0) {
            conquistados++;
        }
    }
    return conquistados >= 3; // Retorna verdadeiro se missão foi cumprida
}

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    // Alocação dinâmica dos territórios
    struct Territorio *territorios = calloc(NUM_TERRITORIOS, sizeof(struct Territorio));

    // Inicializa os dados dos territórios
    inicializarTerritorios(territorios);

    int opcao;
    do {
        // Menu principal
        printf("Menu:\n1 - Atacar\n2 - Verificar Missão\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        if (opcao == 1) {
            // Exibe o mapa antes do ataque
            exibirMapa(territorios);

            // Escolha dos territórios para ataque
            int a, d;
            printf("Escolha atacante (1-5): ");
            scanf("%d", &a);
            printf("Escolha defensor (1-5): ");
            scanf("%d", &d);
            getchar();

            // Executa a simulação de ataque
            simularAtaque(&territorios[a-1], &territorios[d-1]);

        } else if (opcao == 2) {
            // Verifica se a missão foi cumprida
            if (verificarMissao(territorios)) {
                printf("Missão cumprida: Conquistou 3 territórios que não são verdes!\n");
            } else {
                printf("Missão ainda não cumprida.\n");
            }
        }
    } while (opcao != 0); // Continua até o jogador escolher sair

    // Libera a memória alocada
    free(territorios);
    return 0;
}