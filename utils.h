#ifndef COMILAO_UTILS_H
#define COMILAO_UTILS_H

#include "board.h"
#include "list.h"

typedef struct Player {
    char name;
    int x,y;
} Player;

enum coordY{A,B,C,D,E,F,G,H,I,J};

Player** createPlayers();

void printReport(char* fileName,Board *board, CoordList *moves);

#endif /*COMILAO_UTILS_H*/
