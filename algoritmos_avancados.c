#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do cômodo (Nó da Árvore Binária)
// Renomeado de 'No' para 'Sala' para maior clareza no contexto do jogo.
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda; // Caminho para a esquerda
    struct Sala* direita;  // Caminho para a direita
} Sala;

/*
Função criarSala

Aloca dinamicamente um novo cômodo (nó), define o nome
e inicializa os ponteiros dos caminhos (filhos) como NULL.
*/
Sala* criarSala(const char* nome) {
    Sala* novo = (Sala*)malloc(sizeof(Sala)); // Alocação dinâmica de memória
    if (novo == NULL) {
        printf("Erro ao alocar memoria para a sala %s!\n", nome);
        exit(1); // Encerra o programa em caso de erro de memória
    }
    strcpy(novo->nome, nome); // Copia o nome da sala
    novo->esquerda = NULL; // Inicializa o caminho da esquerda como NULL
    novo->direita = NULL;  // Inicializa o caminho da direita como NULL
    return novo;
}

/*
Função montarMapa

Monta o mapa fixo da mansão (a Árvore Binária) de forma manual.
Esta função utiliza a alocação dinâmica e define a estrutura da mansão.
*/
Sala* montarMapa() {
    // Nível 0: Raiz da Árvore
    Sala* hall_entrada = criarSala("Hall de Entrada");

    // Nível 1
    hall_entrada->esquerda = criarSala("Sala de Estar");
    hall_entrada->direita = criarSala("Cozinha");

    // Nível 2 - Subárvore esquerda (Sala de Estar)
    hall_entrada->esquerda->esquerda = criarSala("Biblioteca"); // Nó folha
    hall_entrada->esquerda->direita = criarSala("Quarto Principal");

    // Nível 2 - Subárvore direita (Cozinha)
    hall_entrada->direita->esquerda = criarSala("Sala de Jantar");
    hall_entrada->direita->direita = criarSala("Jardim"); // Nó folha

    // Nível 3 - Subárvore esquerda (Quarto Principal)
    hall_entrada->esquerda->direita->esquerda = criarSala("Banheiro"); // Nó folha
    hall_entrada->esquerda->direita->direita = criarSala("Closet");    // Nó folha

    // Nível 3 - Subárvore direita (Sala de Jantar)
    hall_entrada->direita->esquerda->esquerda = criarSala("Adega"); // Nó folha
    // Sem caminho para a direita na Sala de Jantar

    return hall_entrada; // O nó raiz (Hall de Entrada)
}


/*
Função explorarSalas

Permite a navegação interativa do jogador pela árvore (mapa).
Continua a exploração até que o jogador atinja um nó-folha.
*/
void explorarSalas(Sala* salaAtual) {
    char escolha;

    // Loop de exploração contínua
    while (salaAtual != NULL) {
        printf("\nVoce esta em: **%s**\n", salaAtual->nome);

        // Verifica se é um nó-folha (sem caminhos para esquerda ou direita)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\n**Fim da linha!** Este comodo nao possui mais caminhos.\n");
            break; // Sai do loop (fim da exploracao)
        }

        printf("Para onde voce deseja ir?\n");
        
        // Exibe opções de navegação baseadas nos caminhos disponíveis
        if (salaAtual->esquerda != NULL) {
            printf("  [e] Esquerda -> %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [d] Direita -> %s\n", salaAtual->direita->nome);
        }
        printf("  [s] Sair do Jogo\n");

        printf("Escolha: ");
        scanf(" %c", &escolha); // Lê a escolha do jogador (o espaço antes do %c ignora whitespaces)

        // Lógica de navegação
        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("Caminho para a esquerda indisponivel. Escolha novamente.\n");
            }
        } else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("Caminho para a direita indisponivel. Escolha novamente.\n");
            }
        } else if (escolha == 's' || escolha == 'S') {
            printf("\nSaindo do jogo. Ate a proxima!\n");
            break; // Sai do loop
        } else {
            printf("Opcao invalida. Por favor, escolha 'e', 'd' ou 's'.\n");
        }
    }
}

/*
Função liberar

Libera recursivamente toda a memória alocada para a árvore (mapa).
Essencial para evitar vazamento de memória (memory leak).
*/
void liberar(Sala* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz); // Libera o nó atual
    }
}

/*
Função principal: main

Monta o mapa inicial da mansão e inicia o processo de exploração.
*/
int main() {
    Sala* raiz = NULL; // Inicializa a raiz do mapa

    printf("Bem-vindo a Detective Quest: Exploracao da Mansao \n");
    printf("-----------------------------------------------------------\n");

    // 1. Monta a arvore binaria (mapa)
    raiz = montarMapa();

    // 2. Inicia a exploracao a partir da raiz (Hall de Entrada)
    explorarSalas(raiz);

    // 3. Libera toda a memoria alocada para a arvore
    liberar(raiz);

    return 0;
}