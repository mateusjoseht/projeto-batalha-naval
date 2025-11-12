#ifndef GAME_H
#define GAME_H

// Incluindo as bibliotecas padrão que o projeto permite [cite: 10]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// --- Enums (Tipos Enumerados) ---

/**
 * Define os possíveis estados de uma célula do tabuleiro.
 * [cite: 36]
 */
typedef enum { 
    CELL_WATER, // Água (padrão)
    CELL_SHIP,  // Navio posicionado
    CELL_HIT,   // Navio atingido
    CELL_MISS   // Tiro na água
} CellState;

/**
 * Define a orientação de um navio no tabuleiro.
 * [cite: 45]
 */
typedef enum { 
    ORIENT_H, // Horizontal
    ORIENT_V  // Vertical
} Orientation;


// --- Structs (Estruturas de Dados) ---

/**
 * Representa uma única célula do tabuleiro.
 * [cite: 37-40]
 */
typedef struct {
    CellState state; // O estado (água, navio, etc.)
    int ship_id;     // ID do navio que está aqui (ou -1 se for água)
} Cell;

/**
 * Representa o tabuleiro do jogo.
 * [cite: 41-44]
 */
typedef struct {
    int rows, cols; // Dimensões
    Cell *cells;    // Ponteiro para o array de células (alocado com malloc) [cite: 43]
} Board;

/**
 * Representa um navio da frota.
 * [cite: 46-51]
 */
typedef struct {
    char name[20]; // Nome (ex: "Porta-aviões")
    int length;    // Tamanho (ex: 5 células)
    int hits;      // Quantos tiros já levou
    int placed;    // Flag (1 ou 0) se já foi posicionado
} Ship;

/**
 * Representa a frota de um jogador (um conjunto de navios).
 * [cite: 52-55]
 */
typedef struct {
    Ship *ships; // Ponteiro para o array de navios (alocado com malloc)
    int count;   // Quantidade de navios na frota
} Fleet;

/**
 * Representa um jogador.
 * [cite: 56-61]
 */
typedef struct {
    Board board; // Tabuleiro COM MEUS NAVIOS
    Board shots; // Tabuleiro ONDE EU ATIREI (a visão do inimigo)
    Fleet fleet; // Minha frota
    char nickname[32]; // Nome
} Player;

/**
 * A estrutura "mãe" que controla o estado do jogo.
 * [cite: 62-66]
 */
typedef struct {
    Player p1; // Jogador 1
    Player p2; // Jogador 2
    int current_player; // De quem é a vez (1 ou 2)
    int game_over;      // Flag (1 ou 0) se o jogo acabou
} Game;


#endif // Fim do GAME_H