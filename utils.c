#include "utils.h"

#include <stdlib.h>

int randomizeCoord(){

}

/*Inicializa cada jogador*/
Player** createPlayers(int isBot){
    Player** result = malloc(sizeof(Player*) * 2);

    result[0]=malloc(sizeof(Player));
    result[1]=malloc(sizeof(Player));

    result[0]->x = -1;
    result[0]->y = -1;
    result[0]->isBot = 0;
    result[0]->name = 'A';

    if (isBot = 0) {
        result[1]->x = -1;
        result[1]->y = -1;
        result[1]->isBot = 1;
        result[1]->name = 'B';
    } else {
        result[1]->x = -1;
        result[1]->y = -1;
        result[1]->isBot = 0;
        result[1]->name = 'B';
    }

    return result;
}

void generateCoords(int *x, int *y,int lastPlayerX, int lastPlayerY, int maxCol, int maxRow){
    x = randomizeCoord(lastPlayerX,maxCol);
    y = randomizeCoord(lastPlayerY,maxRow);
}

