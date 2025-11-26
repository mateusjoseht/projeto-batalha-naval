#ifndef IO_H
#define IO_H

#include <stdbool.h>

bool parse_coord(const char *s, int *out_r, int *out_c, int max_rows, int max_cols);
char *read_line(char *buf, int size);
int ask_board_size(int min_size, int max_size);
char ask_placement_mode(void); 
void ask_nickname(char *buf, int size);

/* MUDANÇA: Agora retorna bool. True = Coordenada válida. False = Usuário digitou SAIR/exit */
bool prompt_coord_loop(int max_rows, int max_cols, int *out_r, int *out_c);

#endif // IO_H