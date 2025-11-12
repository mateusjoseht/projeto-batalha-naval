#include "game.h" // <--- INCLUA O game.h
#include "io.h"     

/**
 * Ponto de entrada principal do programa.
 */
int main() {
    
    int escolha_menu;

    do {
        // (Funções do P1/P2)
        // io_clear_screen();
        // escolha_menu = io_show_menu(); 
        
        // ---- APENAS PARA TESTE ----
        // Vamos forçar a escolha "1. Novo Jogo"
        printf("DEBUG: Forçando 'Novo Jogo'...\n");
        escolha_menu = 1;
        // -------------------------

        switch (escolha_menu) {
            case 1:
                // Inicia um novo jogo
                game_start(); // <--- FUNÇÃO SENDO CHAMADA AQUI
                
                escolha_menu = 3; // Força a saída após o jogo
                break;
            case 2:
                // Mostrar configurações
                printf("Configurações (não implementado)...\n"); 
                escolha_menu = 3; 
                break;
            case 3:
                // Sair do jogo
                printf("Obrigado por jogar! Saindo...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n"); 
                break;
        }

    } while (escolha_menu != 3);

    return 0;
    
} // <-- A chave final correta