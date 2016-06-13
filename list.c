#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/*cria uma nova lista*/
CoordList* createList(){
    CoordList* result = malloc(sizeof(CoordList));
    result->list = NULL;
    result->size = 0;
    return result;
}

/*adiciona um novo elemento ao fim da lista*/
void addNode(CoordList* list,int x, int y){
    CoordNode* result = malloc(sizeof(CoordNode));
    CoordNode* tempLast = list->list;
    int i;

    result->x = x;
    result->y = y;
    result->resized = 0;
    result->next = NULL;
    if(list->size == 0){
        list->list = result;
    }
    else {
        for (i = 1; i < list->size; i++) {
            tempLast = tempLast->next;
        }
        tempLast->next = result;
    }
    list->size++;
}



/*Escreve os movimentos por jogador*/
void printMoves(CoordList* moves,Player** players){
    CoordNode* currentNode = moves->list;
    int playerIndex = 0;

    printf("\n");
    do{
        printf("Jogador: %c -> ",players[playerIndex % 2]->name);
        printf("%i %i ",currentNode->x +1,currentNode->y+1);
        if(currentNode->resized == 1)
            printf("Tabuleiro aumentado\n");
        else printf("\n");
        playerIndex++;
        currentNode= currentNode->next;
    } while(currentNode != NULL);

    printf("\n");
}
/*actualiza o valor da variavel resized no ultimo nó da lista dada*/
void updateLastNodeResizedValue(CoordList *moves){
    int i;
    CoordNode *nodeAux = moves->list;

    for (i = 0; i < moves->size; ++i) {
        if (nodeAux->next != NULL)
            nodeAux= nodeAux->next;
        else
            nodeAux->resized = 1;
    }
}