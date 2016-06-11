#include "file.h"
#include <stdio.h>

/*Funcao que guarda o jogo num ficheiro binário.*/
void SaveGame(char* fileName,CoordList *moves,int maxCol,int maxRow){
    FILE *saveFile = fopen(fileName,"wb");
    CoordNode *nodeAux = moves->list;
    int i;

    if (saveFile == NULL){
        printf("Erro ao criar Ficheiro");
        return;
    }
    else {
        fwrite(&maxCol,sizeof(int),1,saveFile);
        fwrite(&maxRow,sizeof(int),1,saveFile);
        fwrite(&moves->size, sizeof(int),1,saveFile);
        for (i = 0; i < moves->size; i++) {
            fwrite(&nodeAux->x, sizeof(int), 1, saveFile);
            fwrite(&nodeAux->y, sizeof(int), 1, saveFile);

            nodeAux = nodeAux->next;
        }
    }
    if (fclose(saveFile) == 0)
        printf("Jogo gravado com sucesso!");
    else printf("Erro ao gravar Jogo!");
}

/*funcao que le do ficheiro o camanho da board*/
void readBoardSize(char *fileName, int *initCol, int *initRow){
    FILE* loadedFile = fopen(fileName,"rb");

    if (loadedFile == NULL){
        printf("Erro ao abrir Ficheiro");
        return;
    }
    else {
        fread(initCol, sizeof(int), 1, loadedFile);
        fread(initRow, sizeof(int), 1, loadedFile);
    }

    if (fclose(loadedFile) == 0)
        printf("Tamanho da board lido com sucesso!");
    else printf("Erro ao ler o tamanho da board!");
}

void getMovesFromFile(char *fileName, CoordList *moves){
    FILE* loadedFile = fopen(fileName,"rb");
    int xAux,yAux,totalMoves;

    int i;

    if (loadedFile == NULL){
        printf("Erro ao abrir Ficheiro");
        return;
    }
    else{
        fseek(loadedFile,sizeof(int)*2,SEEK_SET);
        fread(&totalMoves,sizeof(int),1,loadedFile);

        for(i=0;i<totalMoves;i++){
            fread(&xAux,sizeof(int),1,loadedFile);
            fread(&yAux,sizeof(int),1,loadedFile);

            addNode(moves,xAux,yAux);
        }

    }
    if (fclose(loadedFile) == 0)
        printf("Jogo carregado com sucesso!");
    else printf("Erro ao carregar o jogo!");


}

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
    int i;

    if (report == NULL){
        printf("Erro ao criar Ficheiro");
        return;
        }
    else {
        for (i = 0; i < moves->size; i++) {
            fprintf(report, "%i:", i+1 );

            if (i % 2 == 0)
                playerName = 'A';
            else
                playerName = 'B';

            fprintf(report,"Jogador%c -> ", playerName);
            fprintf(report, "%i%i", nodeAux->x, nodeAux->y);
            if (nodeAux->resized == 0) {
                printf("\n");
                moveToCoords(boardAux, nodeAux->x, nodeAux->y);
                printBoardToFile(report, boardAux, nodeAux->x, nodeAux->y, playerName);
            } else {
                printf(" -> Tabuleiro aumentado\n");
            }

            nodeAux = nodeAux->next;
        }
        if (fclose(report) == 0)
            printf("report exportado com sucesso!");
        else printf("Erro ao Exportar o report!");
    }
}
