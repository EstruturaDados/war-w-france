#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
// Representa um território com nome, cor do exército e número de tropas
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército dominante
    int tropas;        // Quantidade de tropas no território
};

int main() {
    // Declaração de um vetor estático para armazenar 5 territórios
    struct Territorio territorios[5];

    // Loop para cadastrar os dados de cada território
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do território %d:\n", i + 1);

        // Leitura do nome do território usando fgets
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o '\n' do final

        // Leitura da cor do exército usando fgets
        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // Remove o '\n' do final

        // Leitura do número de tropas usando scanf
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        getchar(); // Limpa o buffer do teclado após scanf
        printf("\n"); // Espaço entre os cadastros
    }

    // Exibição organizada dos dados de todos os territórios
    printf("=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0; // Fim do programa
}