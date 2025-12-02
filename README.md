Batalha Naval (Projeto PIF - 2025.2)

Implementação do clássico jogo Batalha Naval em linguagem C, desenvolvido como requisito parcial para a disciplina de Programação Imperativa Funcional (PIF). O projeto foca em gerenciamento de memória manual (malloc/free), modularização e lógica de ponteiros.

👥 Equipe

Mateus José (Módulo Game, Integração e Lógica Principal)

Lucas Rocha (Módulo Board e Input/Output)

Bernardo Santos (Módulo Fleet e Randomização)

🛠️ Como Compilar e Rodar

Este projeto utiliza um Makefile para automação da build.

Pré-requisitos

Compilador GCC (MinGW no Windows ou gcc nativo no Linux/Mac)

Make (mingw32-make)

Passo a Passo

Abra o terminal na pasta raiz do projeto.

Compile o jogo:

mingw32-make


Execute o jogo:

./batalha_naval.exe


Para limpar arquivos temporários (.o) e o executável:

mingw32-make clean


🎮 Como Jogar

Configuração: Ao iniciar, você pode ir em Configurações para definir o tamanho do tabuleiro (6 a 26) e o modo de posicionamento(tamanho padrão é 10x10).

Posicionamento:

Automático: O jogo distribui os navios aleatoriamente sem sobreposição.

Manual: Você digita a coordenada inicial (ex: A1) e a orientação (H ou V) para cada navio.

Batalha:

O jogo alterna turnos entre Jogador 1 e Jogador 2.

Digite a coordenada do tiro (ex: B5).

O mapa mostrará:

~ : Água desconhecida (Fog of War)

. : Tiro na água (Erro)

X : Tiro no navio (Acerto)

S : Seu navio (visível apenas no seu turno)

Vitória: O jogo termina imediatamente quando todos os navios de uma frota forem afundados.

🏗️ Arquitetura e Decisões de Design

O código segue uma arquitetura modular estrita para separar responsabilidades e facilitar a colaboração via Git.

Módulos

game.c/h (O Maestro): Controla o loop principal, alterna turnos, verifica condições de vitória e integra os outros módulos. Mantém o estado global do jogo.

board.c/h (O Engenheiro): Encapsula a lógica da matriz do tabuleiro.

Decisão de Design: O tabuleiro é alocado como um array unidimensional (malloc(rows * cols)), acessado via aritmética de ponteiros (index = r * cols + c) para eficiência de cache e memória.

fleet.c/h (O Almirante): Gerencia a frota.

Decisão de Design: A frota contém um array dinâmico de struct Ship. A validação de "navio afundado" é feita verificando se hits == length.

io.c/h (A Interface): Centraliza inputs do usuário e validações de string (ex: converter "A5" para índices 0, 4). Evita sujar a lógica do jogo com scanf direto.

rnd.c/h (Utilitários): Encapsula a geração de números aleatórios.

Gerenciamento de Memória

O projeto segue estritamente a regra RAII (Resource Acquisition Is Initialization) manual:

board_create aloca memória -> board_free libera.

fleet_init aloca memória -> fleet_free libera.

O ciclo de vida é garantido pela função game_start, que executa a limpeza (cleanup) obrigatoriamente ao final da partida, prevenindo memory leaks.

⚙️ Funcionalidades Implementadas

[x] Menu Interativo (Novo Jogo, Configurações, Sair).

[x] Configuração Dinâmica (Tabuleiro redimensionável).

[x] Posicionamento Híbrido (Manual e Automático).

[x] Gameplay Robusto (Validação de tiros repetidos e limites).

[x] Feedback Visual (Legendas claras e limpeza de tela).

[x] Relatório Final (Exibição dos tabuleiros e estatísticas de precisão).

Projeto desenvolvido para a disciplina de PIF - CESAR School.
