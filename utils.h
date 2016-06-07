#ifndef COMILAO_UTILS_H
#define COMILAO_UTILS_H

typedef struct Player {
    char name;
    int x,y;
} Player;

enum coordY{A,B,C,D,E,F,G,H,I,J};

Player** createPlayers();


#endif /*COMILAO_UTILS_H*/
