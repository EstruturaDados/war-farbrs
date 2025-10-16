#include <stdio.h>
#include <stdlib.h> // para malloc, free, rand, srand
#include <string.h> // para strcpy, strcmp
#include <time.h>   // para TIME

// --- Estrutura de Dados ---
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Protótipos das Funções ---
// Avisando ao compilador que essas funções existirão.
void cadastrarTerritorios(struct Territorio *mapa, int n);
void exibirTerritorios(struct Territorio *mapa, int n);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);

int main() {
    // Inicializa o gerador de números aleatórios.
    // Isso deve ser feito APENAS UMA VEZ no início do programa.
    srand(time(NULL));
    int numTerritorios;
    struct Territorio *mapa = NULL; // Ponteiro para nosso vetor de territórios. Boa prática inicializar com NULL.

    printf("--- BEM-VINDO AO WAR ESTRUTURADO ---\n");
    printf("Quantos territorios o mapa tera? ");
    scanf("%d", &numTerritorios);

    // --- ALOCAÇÃO DINÂMICA DE MEMÓRIA ---
    // Alocamos espaço para 'numTerritorios' structs do tipo Territorio.
    mapa = (struct Territorio *) malloc(numTerritorios * sizeof(struct Territorio));

    // --- VERIFICAÇÃO CRÍTICA ---
    // Sempre verifique se a alocação de memória funcionou!
    if (mapa == NULL) {
        printf("Erro: falha ao alocar memoria para o mapa!\n");
        return 1; //Retorna 1 para indicar o erro
    }
    // --- Fases do Jogo ---
    cadastrarTerritorios(mapa, numTerritorios);

    int opcao = -1;
    do {
        exibirTerritorios(mapa, numTerritorios);
        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("0 - Sair do Jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idAtacante, idDefensor;
            printf("Digite o ID do territorio ATACANTE: ");
            scanf("%d", &idAtacante);
            printf("Digite o ID do territorio DEFENSOR: ");
            scanf("%d", &idDefensor);

            // Validações
            if (idAtacante < 0 || idAtacante >= numTerritorios || idDefensor < 0 || idDefensor >= numTerritorios) {
                printf("ID invalido! Tente novamente.\n");
                continue; //pula para proxima itereção do laço
            }
            if (mapa[idAtacante].tropas < 2) {
                printf("Ataque invalido! O territorio atacante precisa de pelo menos 2 tropas.\n");
                continue;
            }
            if (strcmp(mapa[idAtacante].cor, mapa[idDefensor].cor) == 0) {
                printf("Ataque invalido! Voce nao pode atacar um territorio da sua propria cor.\n");
                continue;
            }
            // Se tudo estiver certo, chama a função de ataque
            // Passamos o ENDEREÇO (&) dos territórios específicos
            atacar(&mapa[idAtacante], &mapa[idDefensor]);
        }
    } while (opcao != 0);

    // <-- CORREÇÃO: Bloco de finalização movido para DENTRO da main, após o loop.
    liberarMemoria(mapa);
    printf("\nMemoria liberada. Fim do jogo!\n");

    return 0;
} // <-- FIM DA FUNÇÃO MAIN


// Função para cadastrar os territórios
void cadastrarTerritorios(struct Territorio *mapa, int n) {
    printf("\n--- FASE DE CADASTRO DE TERRITORIOS ---\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome); // A sintaxe de array mapa[i] funciona com ponteiros!
        printf("Cor do exercito (ex: Azul, Verde): ");
        scanf("%s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(struct Territorio *mapa, int n) {
    printf("\n\n--- SITUACAO ATUAL DO MAPA ---\n");
    for (int i = 0; i < n; i++) {
        printf("----------------------------------\n");
        printf("ID: %d | Territorio: %s\n", i, mapa[i].nome); // Mostramos o ID para o jogador escolher
        printf("      | Cor: %s | Tropas: %d\n", mapa[i].cor, mapa[i].tropas);
    }
    printf("----------------------------------\n");
}

// Função que simula o ataque
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n--- INICIO DA BATALHA: %s (%s) ataca %s (%s)! ---\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    // Simula a rolagem de dados (1 a 6)
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1; // <-- CORREÇÃO: Pequeno ajuste na chamada do rand()

    printf(">> ROLAGEM DE DADOS:\n");
    printf("   Atacante (%s) rolou: %d\n", atacante->nome, dadoAtaque);
    printf("   Defensor (%s) rolou: %d\n", defensor->nome, dadoDefesa);
    // Lógica do combate
    if (dadoAtaque > dadoDefesa) {
        printf(">> VITORIA DO ATACANTE! O territorio %s foi conquistado!\n", defensor->nome); // <-- CORREÇÃO: Faltava um ; aqui
        // O defensor muda de dono (cor)
        strcpy(defensor->cor, atacante->cor);
        // Metade das tropas do atacante (arredondado para baixo) se movem
        int tropasMovidas = atacante->tropas / 2;
        if (tropasMovidas < 1) tropasMovidas = 1; //garante que pelo menos 1 tropa se mova

        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;
    } else {
        printf(">> VITORIA DO DEFENSOR! O ataque foi repelido.\n");
        // O atacante perde 1 tropa se tiver mais de 1
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("   O atacante %s perdeu uma tropa.\n", atacante->nome);
        }
    }
}

void liberarMemoria(struct Territorio* mapa) {
    free(mapa); // Comando para liberar a memória alocada com malloc/calloc
}

