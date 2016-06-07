#include "file.h"
#include <stdio.h>

/*funcao que escreve a board no ficheiro de report, recebe as coordenadase o nome do jogador para
 * o escrever na respectiva posição */
void printBoardToFile(FILE *file,Board *board,int x,int y, char name){
    int i,j;
    char coordY = 'A';

    fprintf(file," ");
    for(j=0; j<=board->maxcol;j++) {
        fprintf(file," %c", coordY++);
    }
    fprintf(file,"\n");
    board->position[x][y] = name;
    for(i = 0; i <= board->maxrow; i++){
        fprintf(file,"%i",i+1);
        for(j = 0; j <= board->maxcol; j++){
            fprintf(file,"|%c",board->position[j][i]);
        }
        fprintf(file,"|\n");
    }
    fprintf(file,"\n");
    board->position[x][y] = ' ';
}

/*Gera um ficheiro .TXT com o report das jogadas e estados do tabuleiro*/
void printReport(char* fileName,int maxcol,int maxrow, CoordList *moves) {
    FILE *report = fopen(fileName, "w");
    CoordNode *nodeAux = moves->list;
    Board *boardAux = createBoard(maxcol+1,maxrow+1);
    char playerName;

    if (report == NULL)
        printf("Erro ao criar Ficheiro");
    else {
        int i;
        for (i = 0; i < moves->size; i++) {
            fprintf(report, "%i:", i);

            if (i % 2 == 0)
                playerName = 'A';
            else
                playerName = 'B';

            fprintf(report,"Jogador%c -> ", playerName);
            fprintf(report, "%i%i\n", nodeAux->x, nodeAux->y);


            moveToCoords(boardAux,nodeAux->x,nodeAux->y,playerName);

            printBoardToFile(report,boardAux,nodeAux->x,nodeAux->y,playerName);

            nodeAux = nodeAux->next;
        }
        if (fclose(report) == 0)
            printf("report exportado com sucesso!");
        else printf("Erro ao Exportar o report!");
    }
}
