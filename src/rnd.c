#include "rnd.h"
#include <stdlib.h>
#include <time.h>

void rnd_init(void) {
    // Usa a hora atual para garantir números diferentes a cada execução
    srand((unsigned int)time(NULL));
}

int rnd_int(int min, int max) {
    // Fórmula padrão para intervalo [min, max]
    return min + (rand() % (max - min + 1));
}

Orientation rnd_orientation(void) {
    // 0 ou 1
    return (rand() % 2 == 0) ? ORIENT_H : ORIENT_V;
}