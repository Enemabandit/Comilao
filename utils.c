#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/*Inicializa cada jogador*/
Player** createPlayers(){
    Player** result = malloc(sizeof(Player*) * 2);
    int i,j;

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

//todo: validar output da funçao fclose
/*Gera um ficheiro .TXT com o report das jogadas e estados do tabuleiro*/
void printReport(char* fileName,Board *board, CoordList *moves){
    FILE* report = fopen(fileName,"w");
    CoordNode *nodeAux = moves->list;

    int i;
    for(i=0;i < moves->size; i++){
        fprintf(report,"%i:",i);
        if(i % 2 == 0)              //<------------conferir a ordem d impressão dos jogadores
            fprintf(report,"JogadorA -> ");
            else fprintf(report,"JogadorB -> ");
        fprintf(report,"%i%i",nodeAux->x,nodeAux->y);

        nodeAux = nodeAux->next;
    }

    fclose(report);
    printf("report exportado com sucesso!");
}
