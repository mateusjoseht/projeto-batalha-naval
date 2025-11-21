#include "io.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *read_line(char *buf, int size) {
    if (!fgets(buf, size, stdin)) return NULL;
    size_t n = strlen(buf);
    if (n > 0 && buf[n-1] == '\n') buf[n-1] = '\0';
    return buf;
}

bool parse_coord(const char *s, int *out_r, int *out_c, int max_rows, int max_cols) {
    if (!s || !*s) return false;
    // primeira letra(s) = coluna (A..), resto = linha
    int i = 0;
    // skip leading spaces
    while (s[i] && isspace((unsigned char)s[i])) i++;
    if (!isalpha((unsigned char)s[i])) return false;
    char col_letter = toupper((unsigned char)s[i]);
    int col = col_letter - 'A';
    i++;
    // parse row number
    while (s[i] && isspace((unsigned char)s[i])) i++;
    if (!isdigit((unsigned char)s[i])) return false;
    int row = 0;
    while (s[i] && isdigit((unsigned char)s[i])) {
        row = row * 10 + (s[i] - '0');
        i++;
    }
    // input like A1 => row 1 corresponds to index 0
    if (col < 0 || col >= max_cols) return false;
    if (row < 1 || row > max_rows) return false;
    if (out_r) *out_r = row - 1;
    if (out_c) *out_c = col;
    return true;
}

int ask_board_size(int min_size, int max_size) {
    char buf[64];
    int size = 0;
    do {
        printf("Tamanho do tabuleiro (%d-%d): ", min_size, max_size);
        read_line(buf, sizeof(buf));
        size = atoi(buf);
    } while (size < min_size || size > max_size);
    return size;
}

char ask_placement_mode(void) {
    char buf[32];
    while (1) {
        printf("Posicionamento (M)anual ou (A)utomatico? ");
        read_line(buf, sizeof(buf));
        if (buf[0] == '\0') continue;
        char c = toupper((unsigned char)buf[0]);
        if (c == 'M' || c == 'A') return c;
    }
}

void ask_nickname(char *buf, int size) {
    printf("Informe apelido do jogador: ");
    read_line(buf, size);
}

void prompt_coord_loop(int max_rows, int max_cols, int *out_r, int *out_c) {
    char buf[64];
    while (1) {
        printf("Digite coordenada do tiro (ex: E5): ");
        read_line(buf, sizeof(buf));
        if (parse_coord(buf, out_r, out_c, max_rows, max_cols)) return;
        printf("Coordenada inválida. Tente novamente.\n");
    }
}
