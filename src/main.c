#include "board.h"
#include "io.h"
#include <stdio.h>

int main(void) {
    int rows = 10, cols = 10;
    Board *b = board_create(rows, cols);
    if (!b) return 1;
    // testa colocação manual básica
    board_place_ship(b, 1, 1, ORIENT_H, 3, 0); // navio id 0 em B2 horizontal
    board_print(b, true);
    int r,c;
    prompt_coord_loop(rows, cols, &r, &c);
    int ship_id;
    int res = board_shoot(b, r, c, &ship_id);
    if (res == 0) printf("Resultado: AGUA\n");
    else if (res == 1) printf("Resultado: ACERTO no navio %d\n", ship_id);
    else printf("Tiro inválido/repetido\n");
    board_print(b, true);
    board_free(b);
    return 0;
}
