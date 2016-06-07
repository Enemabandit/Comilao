#include "file.h"
#include <stdio.h>


/*Gera um ficheiro .TXT com o report das jogadas e estados do tabuleiro*/
void printReport(char* fileName,Board *board, CoordList *moves) {
    FILE *report = fopen(fileName, "w");
    CoordNode *nodeAux = moves->list;
    Board *boardAux = createBoard(board->maxcol,board->maxrow);

    if (report == NULL)
        printf("Erro ao criar Ficheiro");
    else {
        int i;
        for (i = 0; i < moves->size; i++) {
            fprintf(report, "%i:", i);
            if (i % 2 == 0)              //<------------conferir a ordem d impressão dos jogadores
                fprintf(report, "JogadorA -> ");
            else fprintf(report, "JogadorB -> ");
            fprintf(report, "%i%i |", nodeAux->x, nodeAux->y);
            nodeAux = nodeAux->next;
        }

        if (fclose(report) == 0)
            printf("report exportado com sucesso!");
        else printf("Erro ao Exportar o report!");
    }
}
