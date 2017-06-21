Breakout
Autor: Ighor Augusto

Baseado em: https://github.com/valeriangalliat/breakout
Obrigado Valerian!

# Dependencias: 

- ncurses

$ apt-get install libncurses5 libncurses5-dev

# Compilação:

$ git clone https://github.com/f0rb1dd3n/breakout.git
$ cd breakout
$ make
$ cd bin
$ ./breakout

# Controles: 

Setas para direita e esquerda
Setas para cima e para baixo movem mais rápido

# Bricks:

São 4 tipos de bricks:

- 1 acerto para destruir, 2 pontos,
- 2 acertos para destruir, 4 pontos,
- 3 acertos para destruir, 8 pontos,
- 4 acertos para destruir, 16 pontos.

A cor representa quantos acertos faltam para destruir:

- verde:        1 acerto,
- azul:         2 acertos,
- amarelo:      3 acertos,
- vermelho:     4 acertos.

Os pontos sao adicionados quando o brick é destruido.

# Vidas: 

Possui 3 vidas, começando do 2 e teminando no 0.
Quando errar e perder uma vida a bola volta para o centro
assim como o bastão.

Quando ganhar cada vida extra valerá 2 pontos a mais.
