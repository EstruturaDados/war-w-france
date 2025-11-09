#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5 // Número fixo de territórios

// Estrutura que representa um território
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército dominante
    int tropas;        // Quantidade de tropas
};

// Função para cadastrar os territórios com entrada do usuário
void cadastrarTerritorios(struct Territorio *territorios) {
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Cadastro do território %d:\n", i + 1);

        // Leitura do nome
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o '\n'

        // Leitura da cor
        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Leitura do número de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o buffer
        printf("\n");
    }
}

// Função para exibir o estado atual do mapa
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
    // Gera valores aleatórios para ataque e defesa (simulando dados de 1 a 6)
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

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

    // Cadastro inicial dos territórios
    cadastrarTerritorios(territorios);

    int opcao;
    do {
        // Menu principal
        printf("\nMenu:\n1 - Atacar\n2 - Verificar Missão\n3 - Exibir Mapa\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        if (opcao == 1) {
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

        } else if (opcao == 3) {
            // Exibe o mapa atual
            exibirMapa(territorios);
        }

    } while (opcao != 0); // Continua até o jogador escolher sair

    // Libera a memória alocada
    free(territorios);
    return 0;
}