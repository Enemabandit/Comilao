
#ifndef COMILAO_BOARD_H
#define COMILAO_BOARD_H
/*constantes com as dimencoes minimas e maximas da board*/
#define LIMMINCOL 6
#define LIMMAXCOL 10
#define LIMMINROW 4
#define LIMMAXROW 8

#include "list.h"
#include "utils.h"

typedef struct Board{
    int maxcol,maxrow;
    int possibleMoves;
    char **position;
}Board;

/*Aumenta uma linha e uma coluna a board dada*/
Board* resizeBoard(Board *board,CoordList *moves);

/*Preenche a board "carregada" com um lista de moves*/
void loadMovesToBoard(Board *board,CoordList *moves);

/*Move o "cursor" para uma posição sem validar qualquer dos inputs*/
void moveToCoords(Board *board,int x, int y);

/*Move o jogador para a posição e testa se o jogo acabou (return 1 if finished else return 0)*/
int makeMoveAndTestFinish(Board* board,Player* player,CoordList* moves,int x,int y);

/*returns 0 quando o espaço é ' ' e 1 quando é '*' ou 'X'*/
int validateMove(Board* board,int x, int y);

/*valida o input de um int dentro de um intervalo (note: interval argument: 1 = open interval , 2 = closed interval*/
int validateIntInterval(int number, int min, int max,int interval);

/*Cria uma nova Board, devolvendo incializada*/
Board* createBoard(int numcol, int numrow);

/*funcao que establece a dimencao da board*/
void getBoardSize(int *numcol, int *numrow, int limMinCol, int limMaxCol, int limMinRow, int limMaxRow);

/*Escreve a board dada no ecrã*/
void printBoard(Board* board);

#endif /*COMILAO_BOARD_H*/
