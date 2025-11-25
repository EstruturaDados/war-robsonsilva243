#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --------------------------------------------
// STRUCT DO TERRITÓRIO
// --------------------------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --------------------------------------------
// FUNÇÃO: Exibir todos os territórios
// --------------------------------------------
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d) %s - Cor: %s - Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// --------------------------------------------
// FUNÇÃO: Atribuir Missão a um jogador
// --------------------------------------------
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// --------------------------------------------
// FUNÇÃO: Exibir missão do jogador
// --------------------------------------------
void exibirMissao(char* missao) {
    printf("\nSua missão é: %s\n", missao);
}

// --------------------------------------------
// FUNÇÃO: Verificar se missão foi cumprida
// (lógica simples para exemplo didático)
// --------------------------------------------
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo 1: "Conquistar 3 territórios"
    if (strstr(missao, "3 territorios") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) {
                count++;
            }
        }
        if (count >= 3) return 1;
    }

    // Exemplo 2: "Eliminar cor vermelha"
    if (strstr(missao, "vermelha") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0) {
                return 0;  // ainda existe inimigo vermelho
            }
        }
        return 1;
    }

    return 0;
}

// --------------------------------------------
// FUNÇÃO: Ataque entre territórios
// --------------------------------------------
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("ERRO: Você não pode atacar seu próprio território!\n");
        return;
    }

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nAtaque iniciado!\n");
    printf("%s (%s) lança: %d\n", atacante->nome, atacante->cor, dadoA);
    printf("%s (%s) lança: %d\n", defensor->nome, defensor->cor, dadoD);

    if (dadoA > dadoD) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf("O defensor resistiu! Atacante perde 1 tropa.\n");
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// --------------------------------------------
// FUNÇÃO: Liberar memória alocada
// --------------------------------------------
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}

// --------------------------------------------
// FUNÇÃO PRINCIPAL
// --------------------------------------------
int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) malloc(qtd * sizeof(Territorio));

    // Cadastro dos territórios
    for (int i = 0; i < qtd; i++) {
        printf("\nNome do território %d: ", i);
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // --------------------------------------------
    // SISTEMA DE MISSÕES
    // --------------------------------------------
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar cor vermelha",
        "Ter 5 territorios",
        "Manter 2 territorios com mais de 10 tropas",
        "Controlar todos os territorios azuis"
    };
    int totalMissoes = 5;

    char* missao1 = (char*) malloc(150);
    char* missao2 = (char*) malloc(150);

    atribuirMissao(missao1, missoes, totalMissoes);
    atribuirMissao(missao2, missoes, totalMissoes);

    printf("\n=== Jogador 1 ===");
    exibirMissao(missao1);

    printf("\n=== Jogador 2 ===");
    exibirMissao(missao2);

    // --------------------------------------------
    // LOOP DO JOGO
    // --------------------------------------------
    int turno = 1;

    while (1) {
        printf("\n=== TURNO %d ===\n", turno);
        exibirMapa(mapa, qtd);

        int a, d;
        printf("\nEscolha território atacante: ");
        scanf("%d", &a);

        printf("Escolha território defensor: ");
        scanf("%d", &d);

        atacar(&mapa[a], &mapa[d]);

        // Verificação de vitória dos jogadores
        if (verificarMissao(missao1, mapa, qtd)) {
            printf("\n🎉 JOGADOR 1 VENCEU SUA MISSÃO!\n");
            break;
        }
        if (verificarMissao(missao2, mapa, qtd)) {
            printf("\n🎉 JOGADOR 2 VENCEU SUA MISSÃO!\n");
            break;
        }

        turno++;
    }

    liberarMemoria(mapa, missao1, missao2);

    return 0;
}
