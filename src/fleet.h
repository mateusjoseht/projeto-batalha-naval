#ifndef FLEET_H
#define FLEET_H
#include "game.h"

// Inicializa a estrutura Fleet para uso pelo jogador.
// Uso: prepara o vetor de navios e o contador de navios.
// Retorna true em sucesso, false em falha de alocação.
bool fleet_init(Fleet* fleet_ptr);

// Libera recursos alocados pela Fleet.
// Uso: chamada durante a limpeza do jogo para evitar vazamentos.
void fleet_cleanup(Fleet* fleet_ptr);

#endif