#ifndef COMILAO_FILE_H
#define COMILAO_FILE_H
#include "board.h"

/*Funcao que guarda o jogo num ficheiro binário. Todo: precisa de revisão quando implementar o aumentar ficheiro */
void SaveGame(char* fileName,CoordList *moves,int maxCol,int maxRow);
/*funcao que le do ficheiro o camanho da board*/
void readBoardSize(char *fileName, int *initCol, int *initRow);

void getMovesFromFile(char *fileName, CoordList *moves);

/*Gera um ficheiro .TXT com o report das jogadas e estados do tabuleiro*/
void printReport(char* fileName,int numcol,int numrow, CoordList *moves);

#endif //COMILAO_FILE_H
