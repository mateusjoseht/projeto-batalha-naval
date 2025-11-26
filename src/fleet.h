#ifndef FLEET_H
#define FLEET_H

#include "game.h"  // Necessário para as structs Fleet e Ship
#include "board.h" // Necessário para interagir com o tabuleiro

/*
 * Inicializa a frota com os navios padrão exigidos na regra:
 * 1 Porta-aviões (5), 1 Encouraçado (4), 2 Cruzadores (3), 2 Destroyers (2).
 * Aloca memória para fleet->ships.
 */
void fleet_init(Fleet *f);

/* Libera a memória alocada para os navios da frota */
void fleet_free(Fleet *f);

/*
 * Tenta posicionar toda a frota aleatoriamente no tabuleiro.
 * Retorna true se conseguiu, false se falhou (tabuleiro muito pequeno/cheio).
 * Usa as funções de 'rnd' e 'board_can_place'.
 */
bool fleet_place_randomly(Fleet *f, Board *b);

/*
 * Registra um dano no navio especificado pelo ID.
 * Retorna true se o navio afundou com esse tiro.
 */
bool fleet_update_hit(Fleet *f, int ship_id);

/* Verifica se todos os navios da frota afundaram (Fim de Jogo) */
bool fleet_is_destroyed(const Fleet *f);

#endif // FLEET_H
