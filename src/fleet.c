#include "fleet.h"
#include "rnd.h"
#include <stdio.h>
#include <string.h>

void fleet_init(Fleet *f) {
    // Regra: 1 Porta-aviões(5), 1 Encouraçado(4), 2 Cruzadores(3), 2 Destroyers(2)
    // Total: 6 navios
    f->count = 6;
    f->ships = (Ship *)malloc(f->count * sizeof(Ship));

    if (f->ships == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para frota.\n");
        exit(1);
    }

    // Configuração manual dos navios conforme especificação
    // ID 0: Porta-aviões
    strcpy(f->ships[0].name, "Porta-avioes");
    f->ships[0].length = 5;
    f->ships[0].hits = 0;
    f->ships[0].placed = 0;

    // ID 1: Encouraçado
    strcpy(f->ships[1].name, "Encouracado");
    f->ships[1].length = 4;
    f->ships[1].hits = 0;
    f->ships[1].placed = 0;

    // ID 2: Cruzador 1
    strcpy(f->ships[2].name, "Cruzador");
    f->ships[2].length = 3;
    f->ships[2].hits = 0;
    f->ships[2].placed = 0;

    // ID 3: Cruzador 2
    strcpy(f->ships[3].name, "Cruzador");
    f->ships[3].length = 3;
    f->ships[3].hits = 0;
    f->ships[3].placed = 0;

    // ID 4: Destroyer 1
    strcpy(f->ships[4].name, "Destroyer");
    f->ships[4].length = 2;
    f->ships[4].hits = 0;
    f->ships[4].placed = 0;

    // ID 5: Destroyer 2
    strcpy(f->ships[5].name, "Destroyer");
    f->ships[5].length = 2;
    f->ships[5].hits = 0;
    f->ships[5].placed = 0;
}

void fleet_free(Fleet *f) {
    if (f->ships != NULL) {
        free(f->ships);
        f->ships = NULL;
    }
    f->count = 0;
}

bool fleet_place_randomly(Fleet *f, Board *b) {
    // Tenta posicionar cada navio da frota
    for (int i = 0; i < f->count; i++) {
        Ship *ship = &f->ships[i];
        
        // Se já estiver posicionado (ex: mistura de manual com auto), pula
        if (ship->placed) continue;

        bool placed = false;
        int attempts = 0;
        const int MAX_ATTEMPTS = 1000; // Evita loop infinito se tabuleiro estiver cheio

        while (!placed && attempts < MAX_ATTEMPTS) {
            int r = rnd_int(0, b->rows - 1);
            int c = rnd_int(0, b->cols - 1);
            Orientation o = rnd_orientation();

            // Usa a função do board.h para verificar colisão e limites
            if (board_can_place(b, r, c, o, ship->length)) {
                // Posiciona e vincula o ID 'i' ao tabuleiro
                board_place_ship(b, r, c, o, ship->length, i);
                ship->placed = 1;
                placed = true;
            }
            attempts++;
        }

        if (!placed) {
            // Falhou em colocar um dos navios (tabuleiro muito pequeno?)
            return false; 
        }
    }
    return true;
}

bool fleet_update_hit(Fleet *f, int ship_id) {
    if (ship_id < 0 || ship_id >= f->count) return false;

    Ship *s = &f->ships[ship_id];
    s->hits++;

    // Retorna true se acabou de afundar (hits igualou length)
    if (s->hits == s->length) {
        return true; 
    }
    return false;
}

bool fleet_is_destroyed(const Fleet *f) {
    for (int i = 0; i < f->count; i++) {
        // Se algum navio ainda não levou dano total, a frota vive
        if (f->ships[i].hits < f->ships[i].length) {
            return false;
        }
    }
    return true;
}