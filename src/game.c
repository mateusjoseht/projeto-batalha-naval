#include "game.h"
#include "io.h"     // (Para funções de UI, como io_print_winner)
#include "board.h"  // (Para board_create, board_destroy)
#include "fleet.h"  // (Para fleet_create)

/*
 * Inicializa o estado do jogo.
 *
 * Descrição:
 *  - Prepara os jogadores e aloca os recursos necessários (tabuleiros e frotas).
 *  - Em caso de falha parcial, a função limpa os recursos já alocados
 *    antes de retornar false.
 *
 * Parâmetros:
 *  - game_ptr: ponteiro para a estrutura Game que será inicializada.
 *
 * Retorno:
 *  - true em caso de inicialização bem-sucedida; false caso contrário.
 */
bool game_init(Game* game_ptr) {
    printf("DEBUG: Função game_init() chamada.\n");
    int rows = 10, cols = 10;

    // 3. Criar tabuleiros (usando board.c)
    //    Passamos o *endereço* (&) do board que já existe
    if (!board_init(&game_ptr->p1.board, rows, cols)) {
        printf("ERRO CRÍTICO: Falha ao alocar tabuleiro P1.\n");
        return false;
    }
    if (!board_init(&game_ptr->p2.board, rows, cols)) {
        printf("ERRO CRÍTICO: Falha ao alocar tabuleiro P2.\n");
        board_cleanup(&game_ptr->p1.board); // Limpa o P1 que deu certo
        return false;
    }
    
    // 4. Criar frotas (usando fleet.c)
    if (!fleet_init(&game_ptr->p1.fleet)) {
        printf("ERRO CRÍTICO: Falha ao alocar frota P1.\n");
        board_cleanup(&game_ptr->p1.board); // Limpa tudo
        board_cleanup(&game_ptr->p2.board);
        return false;
    }
    if (!fleet_init(&game_ptr->p2.fleet)) {
        printf("ERRO CRÍTICO: Falha ao alocar frota P2.\n");
        board_cleanup(&game_ptr->p1.board); // Limpa tudo
        board_cleanup(&game_ptr->p2.board);
        fleet_cleanup(&game_ptr->p1.fleet);
        return false;
    }

    // 5. Posicionar frotas (usando fleet.c e io.c)
    // ...
    
    game_ptr->current_player = 1; 
    game_ptr->game_over = 0;      
    
    printf("DEBUG: game_init() CONCLUÍDO.\n");
    return true; // Sucesso!
}

/*
 * Loop principal do jogo.
 *
 * Descrição:
 *  - Executa os turnos alternados até que 'game_over' seja marcado.
 *  - Chamadas a funções de I/O, processamento de tiro e verificação
 *    de vitória devem ocorrer aqui.
 *
 * Parâmetros:
 *  - game_ptr: ponteiro para o estado atual do jogo.
 */
void game_loop(Game* game_ptr) {
    printf("DEBUG: Função game_loop() chamada.\n");
    
    while (game_ptr->game_over == 0) {
        // --- Lógica do Jogo (A ser implementada) ---
        // 1. Mostrar os tabuleiros (usando board_print)
        // 2. Indicar de quem é o turno
        // 3. Pedir coordenadas do tiro (usando io_get_coordinates)
        // 4. Processar o tiro (game_process_shot)
        // 5. Verificar se houve vitória (game_check_victory)
        // 6. Trocar o jogador (game_ptr->current_player)
        
        printf("DEBUG: Turno do jogador %d...\n", game_ptr->current_player);
        
        // ---- APENAS PARA TESTE ----
        // Vamos forçar o fim do jogo para não ficar em loop infinito
        if (game_ptr->current_player == 1) {
            game_ptr->current_player = 2; // Troca o turno
        } else {
            game_ptr->game_over = 1; // Termina o jogo
        }
        // -------------------------
    }
}

/*
 * Exibe o resultado final do jogo.
 *
 * Descrição:
 *  - Determina o vencedor (quando aplicável) e delega a impressão
 *    para as funções de I/O apropriadas.
 *
 * Parâmetros:
 *  - game_ptr: ponteiro para o estado final do jogo.
 */
void game_show_result(Game* game_ptr) {
    printf("DEBUG: Função game_show_result() chamada.\n");
    
    // Determinar o vencedor e apresentar resultado ao usuário.
    printf("O jogo acabou! (Vencedor a ser determinado)\n");
}

/*
 * Ponto de controle do jogo: orquestra inicialização, loop e limpeza.
 *
 * Fluxo:
 *  1. Cria a instância local de Game.
 *  2. Inicializa recursos por meio de game_init().
 *  3. Executa game_loop() enquanto o jogo não terminar.
 *  4. Mostra o resultado e realiza a limpeza de recursos alocados.
 */
void game_start() {
    printf("DEBUG: game_start() foi chamada.\n");
    
    Game o_jogo; // Instância local do jogo
    
    if (game_init(&o_jogo)) {
        game_loop(&o_jogo);
        game_show_result(&o_jogo);
    } else {
        printf("Erro: Falha ao inicializar o jogo!\n");
    }

    // Limpeza de recursos (chamada segura mesmo em falhas parciais).
    board_cleanup(&o_jogo.p1.board);
    board_cleanup(&o_jogo.p2.board);
    fleet_cleanup(&o_jogo.p1.fleet);
    fleet_cleanup(&o_jogo.p2.fleet);

    printf("DEBUG: game_start() finalizada (memória limpa).\n");
}