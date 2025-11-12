#include "board.h"
// Inicializa a estrutura Board.
// Parâmetros:
//  - board_ptr: ponteiro para a estrutura a ser inicializada.
//  - rows, cols: dimensões do tabuleiro.
// Comportamento:
//  - Aloca e configura o campo 'cells' e define 'rows' e 'cols'.
// Retorno: true em caso de sucesso, false em falha de alocação.
bool board_init(Board* board_ptr, int rows, int cols) {
    printf("DEBUG: Chamou STUB board_init()\n");
    // Implementação de stub: retorna falha para sinalizar que
    // a função precisa ser implementada no P1.
    return false; 
}

// Libera recursos associados ao Board.
// Parâmetros:
//  - board_ptr: ponteiro para a estrutura cujo conteúdo será liberado.
// Comportamento:
//  - Libera o array 'cells' quando alocado. Pode ser chamada
//    em casos de limpeza parcial (é segura para estados parciais).
void board_cleanup(Board* board_ptr) {
    printf("DEBUG: Chamou STUB board_cleanup()\n");
    // free(board_ptr->cells); // A implementação final deve liberar 'cells' quando apropriado
}