#ifndef BOARD_H
#define BOARD_H
#include "game.h"

// Inicializa o tabuleiro.
// Uso: chama-se antes de usar a struct Board para garantir que
// os campos internos (dimensões e array de células) estejam válidos.
// Retorna true em sucesso ou false em caso de erro.
bool board_init(Board* board_ptr, int rows, int cols);

// Limpa/descarta recursos associados ao tabuleiro.
// Uso: libera memória alocada por board_init e coloca a struct
// em um estado seguro para destruição ou re-inicialização.
void board_cleanup(Board* board_ptr);

#endif