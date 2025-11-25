#ifndef IO_H
#define IO_H

#include <stdbool.h>

/* converte coord tipo "A5" ou "j10" para índices 0-based
   retorna true se válido e dentro de limites. */
bool parse_coord(const char *s, int *out_r, int *out_c, int max_rows, int max_cols);

/* lê uma linha da entrada e remove \n; retorna pointer para buffer (interno) */
char *read_line(char *buf, int size);

/* prompts */
int ask_board_size(int min_size, int max_size);
char ask_placement_mode(void); // 'M' ou 'A'
void ask_nickname(char *buf, int size);

/* lê coord do usuário em loop até válida */
void prompt_coord_loop(int max_rows, int max_cols, int *out_r, int *out_c);

#endif // IO_H
