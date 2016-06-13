#ifndef COMILAO_UTILS_H
#define COMILAO_UTILS_H

//TODO: verificar se realmente é necessário haver esta struct
typedef struct Player {
    char name;
    int isBot;
    int x,y;
} Player;

//typedef enum CoordY{A,B,C,D,E,F,G,H,I,J} CoordY;

Player** createPlayers(int isBot);


#endif /*COMILAO_UTILS_H*/
