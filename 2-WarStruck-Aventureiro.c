#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura Territorio
// Representa um território com nome, cor do exército e número de tropas
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército dominante
    int tropas;        // Quantidade de tropas no território
};

// Função que simula uma batalha entre dois territórios
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    // Gera valores aleatórios para ataque e defesa (simulando dados de 1 a 6)
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    // Exibe os dados sorteados e informações dos territórios envolvidos
    printf("Ataque: %s (%d tropas) - Dado: %d\n", atacante->nome, atacante->tropas, dadoAtaque);
    printf("Defesa: %s (%d tropas) - Dado: %d\n", defensor->nome, defensor->tropas, dadoDefesa);

    // Lógica de combate
    if (dadoAtaque >= dadoDefesa) {
        defensor->tropas--; // Defensor perde 1 tropa
        printf("Defensor perdeu 1 tropa!\n");

        // Se o defensor perder todas as tropas, o território é conquistado
        if (defensor->tropas <= 0) {
            printf("Território %s foi conquistado por %s!\n", defensor->nome, atacante->nome);
            strcpy(defensor->cor, atacante->cor); // Cor do exército é atualizada
            defensor->tropas = 1; // Tropas mínimas atribuídas ao novo dono
        }
    } else {
        printf("Defensor resistiu ao ataque!\n");
    }
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Alocação dinâmica de memória para 5 territórios
    struct Territorio *territorios = calloc(5, sizeof(struct Territorio));

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do território %d:\n", i + 1);

        // Leitura do nome do território
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o '\n'

        // Leitura da cor do exército
        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // Remove o '\n'

        // Leitura do número de tropas
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // Limpa o buffer após scanf
        printf("\n");
    }

    // Fase de ataque interativa
    int opcao;
    do {
        int a, d;

        // Escolha dos territórios para ataque
        printf("Escolha o território atacante (1-5): ");
        scanf("%d", &a);
        printf("Escolha o território defensor (1-5): ");
        scanf("%d", &d);
        getchar(); // Limpa o buffer

        // Executa a simulação de ataque
        simularAtaque(&territorios[a-1], &territorios[d-1]);

        // Pergunta se o jogador deseja continuar atacando
        printf("Deseja continuar atacando? (1-Sim / 0-Não): ");
        scanf("%d", &opcao);
    } while (opcao); // Repete enquanto o jogador quiser continuar

    // Libera a memória alocada dinamicamente
    free(territorios);
    return 0;
}