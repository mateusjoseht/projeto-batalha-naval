/**
 * @file game.c
 * @brief Implementação da lógica central do jogo (Fluxo, Turnos, Regras).
 * [cite_start]Atende aos requisitos de controle de fluxo e modularização[cite: 155].
 */

#include "game.h"
#include "io.h"
#include "board.h"
#include "fleet.h"
#include "rnd.h"
#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>

// Configurações padrão (Persistem durante a execução)
static int CURRENT_SIZE = 10;
static char CURRENT_MODE = 'A';

/**
 * Limpa o terminal para manter a interface limpa.
 */
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// --- Funções Auxiliares de Input ---

Orientation ask_orientation() {
    char buf[32];
    while (1) {
        printf("Orientacao (H)orizontal ou (V)ertical? ");
        if (fgets(buf, sizeof(buf), stdin)) {
            char c = toupper(buf[0]);
            if (c == 'H') return ORIENT_H;
            if (c == 'V') return ORIENT_V;
        }
    }
}

/**
 * Gerencia o posicionamento manual de navios.
 * Garante que o jogador posicione todos os navios da frota sem colisão.
 */
bool place_ships_manually(Player *p) {
    printf("\n--- POSICIONAMENTO MANUAL PARA %s ---\n", p->nickname);
    board_print(p->board, true); 

    for (int i = 0; i < p->fleet.count; i++) {
        Ship *ship = &p->fleet.ships[i];
        bool placed = false;
        while (!placed) {
            printf("\nPosicionando: %s (Tamanho: %d)\n", ship->name, ship->length);
            
            int r, c;
            // Se o usuário tentar sair no setup, cancelamos o manual
            if (!prompt_coord_loop(p->board->rows, p->board->cols, &r, &c)) {
                printf("Cancelando manual... completando com automatico.\n");
                return false; 
            }
            
            Orientation orient = ask_orientation();
            
            // Validação de regras de posicionamento
            if (board_can_place(p->board, r, c, orient, ship->length)) {
                board_place_ship(p->board, r, c, orient, ship->length, i);
                ship->placed = 1;
                placed = true;
                printf("Navio posicionado!\n");
                board_print(p->board, true);
            } else {
                printf("ERRO: Posicao invalida ou colisao. Tente novamente.\n");
            }
        }
    }
    return true;
}

/**
 * Configura os recursos (Board e Fleet) de um jogador.
 * Realiza alocação de memória e posicionamento inicial.
 */
bool setup_player_resources(Player *p, int rows, int cols, char mode) {
    // 1. Cria Tabuleiro (Alocação Dinâmica - Malloc)
    p->board = board_create(rows, cols);
    if (!p->board) return false;

    // 2. Cria Frota
    fleet_init(&p->fleet);

    // 3. Posiciona Navios
    bool placed_ok = false;
    if (mode == 'A' || mode == 'a') {
        placed_ok = fleet_place_randomly(&p->fleet, p->board);
    } else {
        if (!place_ships_manually(p)) {
            // Fallback para automático se manual falhar/cancelar
            placed_ok = fleet_place_randomly(&p->fleet, p->board);
        } else {
            placed_ok = true;
        }
    }
    return placed_ok;
}

void game_settings() {
    int opcao = 0;
    char buf[10];
    do {
        clear_screen();
        printf("=== CONFIGURACOES ===\n");
        printf("1. Tamanho do Tabuleiro (Atual: %dx%d)\n", CURRENT_SIZE, CURRENT_SIZE);
        printf("2. Modo de Posicionamento (Atual: %c)\n", CURRENT_MODE);
        printf("3. Voltar\n");
        printf("Escolha: ");
        if (fgets(buf, sizeof(buf), stdin)) opcao = atoi(buf);

        switch (opcao) {
            case 1: CURRENT_SIZE = ask_board_size(6, 26); break;
            case 2: CURRENT_MODE = ask_placement_mode(); break;
            case 3: break;
            default: printf("Opcao invalida.\n"); break;
        }
    } while (opcao != 3);
}

bool game_init(Game *game) {
    rnd_init(); 
    clear_screen();
    
    printf("=== INICIANDO NOVA PARTIDA ===\n");
    printf("Configuracao: %dx%d | Modo %s\n", 
           CURRENT_SIZE, CURRENT_SIZE, (CURRENT_MODE == 'A' ? "Automatico" : "Manual"));

    // Input de nomes centralizado via IO.c
    printf("\n--- Jogador 1 ---\n");
    ask_nickname(game->p1.nickname, sizeof(game->p1.nickname));

    printf("\n--- Jogador 2 ---\n");
    ask_nickname(game->p2.nickname, sizeof(game->p2.nickname));

    // Inicialização de recursos e validação de memória
    if (!setup_player_resources(&game->p1, CURRENT_SIZE, CURRENT_SIZE, CURRENT_MODE)) return false;
    if (!setup_player_resources(&game->p2, CURRENT_SIZE, CURRENT_SIZE, CURRENT_MODE)) return false;

    if (CURRENT_MODE == 'A') printf("\n[Frotas posicionadas automaticamente]\n");

    game->current_player = 1;
    game->game_over = 0;
    
    printf("\nPressione Enter para comecar...");
    getchar(); 
    return true;
}

/**
 * Exibe o estado atual dos tabuleiros para o jogador da vez.
 */
void render_turn(Player *attacker, Player *defender) {
    clear_screen();
    printf("\n-- Turno de %s --\n", attacker->nickname);
    printf("(Digite 'SAIR' para encerrar)\n\n");
    
    printf("Tabuleiro inimigo (%s):\n", defender->nickname);
    board_print(defender->board, false); // False = Esconde navios (Fog of War)

    printf("\nSeu tabuleiro (%s):\n", attacker->nickname);
    board_print(attacker->board, true);  // True = Mostra navios
}

/**
 * Processa o tiro: atualiza tabuleiro e verifica danos na frota.
 * Retorna true se o jogo deve continuar, false se acabou ou erro.
 */
void execute_shot(Player *defender, int r, int c, int *total_hits) {
    int hit_ship_id = -1;
    int result = board_shoot(defender->board, r, c, &hit_ship_id);

    printf("\nRESULTADO: ");
    if (result == 0) {
        printf("AGUA.\n");
    } 
    else if (result == 1) {
        char *ship_name = defender->fleet.ships[hit_ship_id].name;
        bool sunk = fleet_update_hit(&defender->fleet, hit_ship_id);
        
        if (sunk) printf("AFUNDOU %s!\n", ship_name);
        else printf("ACERTOU no %s!\n", ship_name);
        
        (*total_hits)++;
    } 
    else {
        printf("Tiro invalido ou repetido.\n");
        // Pequena pausa para o usuário ler o erro
        printf("Pressione Enter..."); 
        getchar();
    }
}

/**
 * Exibe a tela de vitória e estatísticas finais.
 [cite_start]* [cite: 73, 97-99]
 */
void show_victory_screen(Player *winner, Player *loser, int shots, int hits) {
    printf("\n*** FIM DE JOGO ***\n");
    printf("Vencedor: %s\n", winner->nickname);
    
    float precision = 0.0f;
    if (shots > 0) precision = ((float)hits / shots) * 100.0f;
    printf("Tiros: %d | Acertos: %d | Precisao: %.1f%%\n", shots, hits, precision);

    printf("\n--- Estado final dos tabuleiros ---\n");
    printf("Tabuleiro de %s (Vencedor):\n", winner->nickname);
    board_print(winner->board, true);

    printf("\nTabuleiro de %s (Perdedor - Visao Real):\n", loser->nickname);
    board_print(loser->board, true); // Mostra onde estavam os navios escondidos

    printf("\nMapa de tiros:\n");
    board_print(loser->board, false);
    
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

/**
 * Loop principal de turnos. Alterna jogadores até a vitória.
 */
void game_loop(Game *game) {
    int total_shots = 0;
    int total_hits = 0;

    while (!game->game_over) {
        Player *attacker = (game->current_player == 1) ? &game->p1 : &game->p2;
        Player *defender = (game->current_player == 1) ? &game->p2 : &game->p1;

        render_turn(attacker, defender);

        int r, c;
        // Validação de entrada e opção de saída
        if (!prompt_coord_loop(defender->board->rows, defender->board->cols, &r, &c)) {
            printf("\nJogo encerrado por %s.\n", attacker->nickname);
            game->game_over = 1;
            return;
        }

        execute_shot(defender, r, c, &total_hits);
        total_shots++;

        // Condição de Vitória
        if (fleet_is_destroyed(&defender->fleet)) {
            game->game_over = 1;
            show_victory_screen(attacker, defender, total_shots, total_hits);
        } else {
            printf("\nPressione Enter para passar a vez...");
            getchar(); 
            game->current_player = (game->current_player == 1) ? 2 : 1;
        }
    }
}

/**
 * Ponto de entrada do módulo Game. Gerencia ciclo de vida e memória.
 */
void game_start() {
    Game game;
    // Inicializa
    if (game_init(&game)) {
        // Loop
        if (!game.game_over) {
            game_loop(&game);
        }
    }
    // Limpeza de Memória (Ordem inversa à alocação)
    if (game.p1.board) board_free(game.p1.board);
    if (game.p2.board) board_free(game.p2.board);
    fleet_free(&game.p1.fleet);
    fleet_free(&game.p2.fleet);
}