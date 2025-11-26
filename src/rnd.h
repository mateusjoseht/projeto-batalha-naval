#ifndef RND_H
#define RND_H

#include "game.h" // Para acessar o enum Orientation

/* Inicializa a semente do gerador aleatório (srand) */
void rnd_init(void);

/* Retorna um inteiro aleatório entre min e max (inclusivo) */
int rnd_int(int min, int max);

/* Retorna uma orientação aleatória (ORIENT_H ou ORIENT_V) */
Orientation rnd_orientation(void);

#endif // RND_H