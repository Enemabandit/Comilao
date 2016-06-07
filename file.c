#include "file.h"
#include <stdio.h>

void printBoardToFile(FILE *file,Board *board){
    int i,j;
    enum coordY coordY = 'A';

    fprintf(file," ");
    for(j=0; j<=board->maxcol;j++) {
        fprintf(file," %c", coordY);
        coordY++;
    }
    fprintf(file,"\n");

    for(i = 0; i <= board->maxrow; i++){
        fprintf(file,"%i",i+1);
        for(j = 0; j <= board->maxcol; j++){
            fprintf(file,"|%c",board->position[j][i]);
        }
        fprintf(file,"|\n");
    }
    fprintf(file,"\n");
}

/*Gera um ficheiro .TXT com o report das jogadas e estados do tabuleiro*/
void printReport(char* fileName,int maxcol,int maxrow, CoordList *moves) {
    FILE *report = fopen(fileName, "w");
    CoordNode *nodeAux = moves->list;
    Board *boardAux = createBoard(maxcol,maxrow);

    if (report == NULL)
        printf("Erro ao criar Ficheiro");
    else {
        int i;
        for (i = 0; i < moves->size; i++) {
            fprintf(report, "%i:", i);
            if (i % 2 == 0)
                fprintf(report, "JogadorA -> ");
            else fprintf(report, "JogadorB -> ");
            fprintf(report, "%i%i |", nodeAux->x, nodeAux->y);

            printf("Olá");
           //moveToCoords(boardAux,nodeAux->x,nodeAux->y);
           // printBoardToFile(report,boardAux);

            nodeAux = nodeAux->next;
        }
        if (fclose(report) == 0)
            printf("report exportado com sucesso!");
        else printf("Erro ao Exportar o report!");
    }
}
