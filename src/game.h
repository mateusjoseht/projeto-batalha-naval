#ifndef GAME_H
#define GAME_H

// Incluindo as bibliotecas padrão que o projeto permite [cite: 10]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// --- Enums (estados e orientações) ---

// Estado de uma célula do tabuleiro.
typedef enum { 
    CELL_WATER, // água
    CELL_SHIP,  // navio posicionado
    CELL_HIT,   // navio atingido
    CELL_MISS   // tiro na água
} CellState;

// Orientação de um navio no tabuleiro.
typedef enum { 
    ORIENT_H, // horizontal
    ORIENT_V  // vertical
} Orientation;


// --- Estruturas principais ---

// Representa uma célula do tabuleiro.
typedef struct {
    CellState state; // estado atual da célula
    int ship_id;     // id do navio presente, -1 se vazio
} Cell;

// Representa o tabuleiro do jogo.
// 'cells' é um array linear de tamanho rows * cols.
typedef struct {
    int rows, cols;
    Cell *cells;    // alocado dinamicamente
} Board;

// Representa um navio individual.
typedef struct {
    char name[20];
    int length;
    int hits;      // quantidade de acertos recebidos
    int placed;    // flag: 1 se posicionado, 0 caso contrário
} Ship;

// Conjunto de navios pertencentes a um jogador.
typedef struct {
    Ship *ships; // vetor de navios (alocado dinamicamente)
    int count;   // número de navios
} Fleet;

// Representação de um jogador.
typedef struct {
    Board board;  // tabuleiro com os próprios navios
    Board shots;  // visão do jogador sobre os tiros realizados
    Fleet fleet;  // frota do jogador
    char nickname[32];
} Player;

// Estado global do jogo.
typedef struct {
    Player p1;
    Player p2;
    int current_player; // 1 ou 2
    int game_over;      // 1 se o jogo terminou, 0 caso contrário
} Game;

// Controle do fluxo do jogo: inicialização, loop e limpeza.
void game_start();

#endif // GAME_H