#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "board.h" // Inclui a definição de Board do P1

// --- 1. Definições das Estruturas da Frota ---
// Elas precisam vir ANTES da struct Player, pois Player usa Fleet.

typedef struct {
    char name[20];
    int length;
    int hits;
    int placed;
} Ship;

typedef struct {
    Ship *ships; // Array de navios
    int count;
} Fleet;


// --- 2. Estruturas Principais do Jogo ---

typedef struct {
    Board *board;      // Ponteiro para o Board (definido em board.h)
    Fleet fleet;       // Struct Fleet (definida logo acima)
    char nickname[32]; // Nome do jogador
} Player;

typedef struct {
    Player p1; 
    Player p2; 
    int current_player; // 1 ou 2
    int game_over;      
} Game;
// Funções do game.c
void game_start();
void game_settings(); // <--- ADICIONE ESTA LINHA AQUI

#endif // GAME_H