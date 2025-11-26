#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef enum { CELL_WATER, CELL_SHIP, CELL_HIT, CELL_MISS } CellState;
typedef enum { ORIENT_H, ORIENT_V } Orientation;

typedef struct {
    CellState state;
    int ship_id; // -1 se não houver navio
} Cell;

typedef struct {
    int rows, cols;
    Cell *cells; // alocado rows*cols
} Board;

/* criação / liberação */
Board *board_create(int rows, int cols);
void board_free(Board *b);

/* acesso */
Cell *board_cell(Board *b, int r, int c); // NULL se fora

/* debugging / print */
void board_print(const Board *b, bool show_ships);

/* posicionamento */
bool board_can_place(const Board *b, int r, int c, Orientation o, int length);
void board_place_ship(Board *b, int r, int c, Orientation o, int length, int ship_id);

/* tiro:
   retorna: 0 = água (miss), 1 = acerto, 2 = afundou, -1 = inválido/repetido
   fleet info ficará no jogo; aqui só atualizamos célula */
int board_shoot(Board *b, int r, int c, int *out_ship_id);

#endif // BOARD_H
