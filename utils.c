#include "utils.h"
#include <stdlib.h>

/*Inicializa cada jogador*/
Player** createPlayers(){
    Player** result = malloc(sizeof(Player*) * 2);

    result[0]=malloc(sizeof(Player));
    result[1]=malloc(sizeof(Player));

    result[0]->x = -1;
    result[0]->y = -1;
    result[0]->name = 'A';

    result[1]->x = -1;
    result[1]->y = -1;
    result[1]->name = 'B';

    return result;
}


