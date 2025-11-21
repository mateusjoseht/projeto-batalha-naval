#include "board.h"
#include <stdio.h>
#include <stdlib.h>

Board *board_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    Board *b = malloc(sizeof(Board));
    if (!b) return NULL;
    b->rows = rows; b->cols = cols;
    b->cells = malloc(sizeof(Cell) * rows * cols);
    if (!b->cells) { free(b); return NULL; }
    for (int i = 0; i < rows * cols; ++i) {
        b->cells[i].state = CELL_WATER;
        b->cells[i].ship_id = -1;
    }
    return b;
}

void board_free(Board *b) {
    if (!b) return;
    free(b->cells);
    free(b);
}

Cell *board_cell(Board *b, int r, int c) {
    if (!b) return NULL;
    if (r < 0 || r >= b->rows || c < 0 || c >= b->cols) return NULL;
    return &b->cells[r * b->cols + c];
}

void board_print(const Board *b, bool show_ships) {
    if (!b) return;
    printf("   ");
    for (int c = 0; c < b->cols; ++c) printf("%2c", 'A' + c);
    printf("\n");
    for (int r = 0; r < b->rows; ++r) {
        printf("%2d ", r+1);
        for (int c = 0; c < b->cols; ++c) {
            const Cell *cell = &b->cells[r * b->cols + c];
            char ch = '~';
            if (cell->state == CELL_WATER) ch = (show_ships && cell->ship_id != -1) ? 'S' : '~';
            else if (cell->state == CELL_SHIP) ch = (show_ships ? 'S' : '~');
            else if (cell->state == CELL_HIT) ch = 'X';
            else if (cell->state == CELL_MISS) ch = '.';
            printf("%2c", ch);
        }
        printf("\n");
    }
}

bool board_can_place(const Board *b, int r, int c, Orientation o, int length) {
    if (!b) return false;
    if (length <= 0) return false;
    if (o == ORIENT_H) {
        if (c + length > b->cols) return false;
        for (int i = 0; i < length; ++i) {
            const Cell *cell = &b->cells[r * b->cols + (c + i)];
            if (cell->ship_id != -1) return false;
        }
    } else {
        if (r + length > b->rows) return false;
        for (int i = 0; i < length; ++i) {
            const Cell *cell = &b->cells[(r + i) * b->cols + c];
            if (cell->ship_id != -1) return false;
        }
    }
    return true;
}

void board_place_ship(Board *b, int r, int c, Orientation o, int length, int ship_id) {
    if (!b) return;
    if (!board_can_place(b, r, c, o, length)) return;
    if (o == ORIENT_H) {
        for (int i = 0; i < length; ++i) {
            Cell *cell = &b->cells[r * b->cols + (c + i)];
            cell->ship_id = ship_id;
            cell->state = CELL_SHIP;
        }
    } else {
        for (int i = 0; i < length; ++i) {
            Cell *cell = &b->cells[(r + i) * b->cols + c];
            cell->ship_id = ship_id;
            cell->state = CELL_SHIP;
        }
    }
}

/* board_shoot: update cell state and returns code; out_ship_id = ship_id if hit */
int board_shoot(Board *b, int r, int c, int *out_ship_id) {
    if (!b) return -1;
    Cell *cell = board_cell(b, r, c);
    if (!cell) return -1;
    if (cell->state == CELL_HIT || cell->state == CELL_MISS) return -1; // repetido
    if (cell->ship_id == -1) {
        cell->state = CELL_MISS;
        if (out_ship_id) *out_ship_id = -1;
        return 0;
    } else {
        cell->state = CELL_HIT;
        if (out_ship_id) *out_ship_id = cell->ship_id;
        return 1;
    }
}
