#include <stdio.h>
#include <stdlib.h> // Para system() e atoi()
#include "game.h"
#include "io.h"     

void main_clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int escolha_menu = 0;
    char buf[16];

    do {
        main_clear();
        printf("=== BATALHA NAVAL ===\n");
        printf("1) Novo jogo\n");
        printf("2) Configuracoes\n");
        printf("3) Sair\n");
        printf("> ");
        
        // Lê a opção do usuário
        if (fgets(buf, sizeof(buf), stdin)) {
            escolha_menu = atoi(buf);
        }

        switch (escolha_menu) {
            case 1:
                // Inicia o jogo (o fluxo de perguntas estará dentro do game_start)
                game_start(); 
                
                // Pausa quando o jogo acaba para o usuário ver o resultado
                printf("\nPressione Enter para voltar ao menu...");
                getchar();
                break;

            case 2:
                // Como o "Novo Jogo" agora pergunta tudo, Configurações é opcional,
                // mas vamos chamar a função para manter o requisito do menu.
                game_settings(); 
                break;

            case 3:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                // Pequena pausa para ler o erro
                printf("Pressione Enter...");
                getchar();
                break;
        }

    } while (escolha_menu != 3);

    return 0;
}