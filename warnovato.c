// Bibliotecas necessárias para entrada/saída (printf, scanf) e manipulação de strings.

#include <stdio.h>
#include <string.h>

// --- Definição da Estrutura (Struct) ---
// Criando o "molde" para um Territorio.
// Qualquer variável do tipo 'struct Territorio' terá esses três campos.
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Função Principal ---
// O programa começa a ser executado aqui.
int main() {
    // --- Declaração do Vetor de Structs ---
    // Criando nosso "mapa" que pode guardar 5 territórios.
    struct Territorio mapa[5];

    // --- Entrada dos Dados (Cadastro) ---
    printf("--- CADASTRO DE TERRITORIOS DO WAR ---\n");

    // Laço para repetir o cadastro 5 vezes (para i = 0, 1, 2, 3, 4)
    for (int i = 0; i < 5; i++) {
        
        // Usamos 'i + 1' para que a contagem para o usuário seja de 1 a 5.
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Digite o nome: ");
        // Lê o nome e armazena no campo 'nome' da struct na posição 'i' do vetor 'mapa'.
        scanf("%s", mapa[i].nome);
        limparBufferEntrada(); //limpa o '\n' deixado pelo scanf.

        printf("Digite a cor do exercito: ");
        // Lê a cor e armazena no campo 'cor' da struct na posição 'i'.
        scanf("%s", mapa[i].cor);
        limparBufferEntrada(); //limpa o '\n' deixado pelo scanf.

        printf("Digite a quantidade de tropas: ");
        // Lê o número de tropas e armazena no campo 'tropas' da struct na posição 'i'.
        // O '&' é crucial para tipos numéricos com scanf.
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada(); //limpa o '\n' deixado pelo scanf.
    }

    // --- Exibição dos Dados ---
    printf("\n\n--- MAPA DE TERRITORIOS CADASTRADOS ---\n");

    // Outro laço 'for' para percorrer o vetor e mostrar os dados que acabamos de cadastrar.
    for (int i = 0; i < 5; i++) {
        printf("\n---------------------------\n");
        printf(" Territorio: %s\n", mapa[i].nome);
        printf(" Cor do Exercito: %s\n", mapa[i].cor);
        printf(" Quantidade de Tropas: %d\n", mapa[i].tropas);
    }
    printf("---------------------------\n");


    // Indica que o programa terminou com sucesso.
    return 0;
}