#ifndef COMILAO_LIST_H
#define COMILAO_LIST_H

#include "utils.h"

//todo: adicionar um booleano no coordlist para registar aumentos de tabuleiro
/*Estrura para cada elemento da lista*/
typedef struct CoordNode{
    int x,y;
    struct CoordNode *next;
} CoordNode;

/*Lista ligada que contem as coordenadas escolhidas durante o jogo*/
typedef struct CoordList{
    int size;
    struct CoordNode *list;
} CoordList;


/*Cria e inicializa a lista de moves*/
CoordList* createList();

/*adiciona um novo elemento ao fim da lista*/
void addNode(CoordList* list,int x, int y);

/*Escreve os movimentos por jogador*/
void printMoves(CoordList* moves,Player** players);

#endif /*COMILAO_LIST_H*/
