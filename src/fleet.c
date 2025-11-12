#include "fleet.h"
// Inicializa a frota do jogador.
// Parâmetros:
//  - fleet_ptr: ponteiro para a estrutura Fleet a ser inicializada.
// Comportamento:
//  - Aloca o array de navios e define o contador de navios.
// Retorno: true em caso de sucesso, false em falha.
bool fleet_init(Fleet* fleet_ptr) {
    printf("DEBUG: Chamou STUB fleet_init()\n");
    // Stub: retorna false para indicar que a implementação está pendente
    return false;
}

// Libera recursos associados à frota.
// Parâmetros:
//  - fleet_ptr: ponteiro para a estrutura a ser limpa.
// Comportamento:
//  - Libera o array de navios quando alocado e restaura um estado seguro.
void fleet_cleanup(Fleet* fleet_ptr) {
    printf("DEBUG: Chamou STUB fleet_cleanup()\n");
}