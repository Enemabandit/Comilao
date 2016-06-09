
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

/*Preenche a board "carregada" com um lista de moves*/
void loadMovesToBoard(Board *board,CoordList *moves){
    int i;
    CoordNode *nodeAux = moves->list;

    for(i =0;i<moves->size;i++){
        moveToCoords(board,nodeAux->x,nodeAux->y);

        nodeAux = nodeAux->next;
    }
}

/*Move o "cursor" para uma posição sem validar qualquer dos inputs*/
void moveToCoords(Board *board,int x, int y){
    int i,j;

    for(i=x; i >= 0 ;i--) {
        for (j = y; j >= 0; j--) {
                board->position[i][j] = ' ';
        }
    }

}
/*Move o jogador para a posição e testa se o jogo acabou (return 1 if finished else return 0)*/
int makeMoveAndTestFinish(Board* board,Player* player,CoordList* moves,int x,int y){
    int i,j;
    int foodEaten = 0;

    if (board->position[x][y] == '*'){
        for(i=x; i >= 0 ;i--) {
            for (j = y; j >= 0; j--) {
                if (board->position[i][j] == '*') {
                    foodEaten++;
                    }
                board->position[i][j] = ' ';
            }
        }
        player->x = x;
        player->y = y;

        addNode(moves,x,y);

        board->possibleMoves = board->possibleMoves - foodEaten;
        return 0;
    }
    else {
        addNode(moves,x,y);
        return 1;
    }
}

/*returns 0 quando o espaço é ' ' e 1 quando é '*' ou 'X'*/
int validateMove(Board* board,int x, int y){
    if (board->position[x][y] == ' ') {
        printf("E impossivel movimentar para uma celula sem comida!\n");
        return 0;
    }
            else return 1;
}

/*valida o input de um int dentro de um intervalo (note: interval argument: 1 = open interval , 2 = closed interval*/
int validateIntInterval(int number, int min, int max,int interval){
    if (interval == 1){
        if (number <= min || number >= max) return 0;
        else return 1;
    }else if(interval == 2){
        if (number < min || number > max) return 0;
        else return 1;
    } else return 2;
}

/*função que aloca a board em memória*/
Board* allocateBoard(int numcol,int numrow){
    Board* result = malloc(sizeof(Board));
    int i;

    result->maxcol = numcol - 1;
    result->maxrow = numrow - 1;
    result->possibleMoves = numcol * numrow;

    /*Aloca a board em memória*/
    result->position=malloc(sizeof (char*) * numcol);
    for (i = 0; i < numcol; i++){
        result->position[i] = malloc(sizeof(char) * numrow);
    }
    return result;
}

/*Cria uma nova Board, devolvendo incializada*/
Board* createBoard(int numcol, int numrow){
    int i,j;
    Board* result = allocateBoard(numcol,numrow);

    /*iInicializa cada célula com ("*")*/
    for(i = 0; i < numrow; i++){
        for(j = 0; j < numcol; j++){
            result->position[j][i] = '*';
        }
    }
    /*Muda o valor do canto inferior direito para X(veneno)*/
    result->position[result->maxcol][result->maxrow] = 'X';
    return result;

}

/*funcao que establece a dimencao da board*/
void setBoardSize(int *numcol, int *numrow, int limMinCol, int limMaxCol, int limMinRow, int limMaxRow){
    //input for the size of the board
    int invalid;
    do {
        do {
            printf("Introduza o numero de colunas(entre %i e %i): ",limMinCol,limMaxCol);
            scanf("%i", numcol);
            if (validateIntInterval(*numcol,limMinCol,limMaxCol,2) != 1) {
                printf("este input nao e valido\n");
                invalid = 1;
            }
            else invalid = 0;
        } while (invalid);
        do {
            printf("Introduza o numero de linhas (entre %i e %i): ",limMinRow,limMaxRow);
            scanf("%i", numrow);
            if (validateIntInterval(*numrow,limMinRow,limMaxRow,2) != 1 ) {
                printf("Este input nao e valido!\n");
                invalid = 1;
            }
            else invalid = 0;
        } while (invalid);
        printf("\n");
        if (*numcol <= *numrow) {printf("O numero de colunas tem de ser superior ao numero de linhas!\n");}
    } while (*numcol <= *numrow);
    printf("\nJogo inciado com sucesso!\n");
}

/*Escreve a board dada no ecrã*/
void printBoard(Board* board){
    int i,j;
    char coordY = 'A';

    printf(" ");
    for(j=0; j<=board->maxcol;j++) {
        printf(" %c", coordY);
        coordY++;
    }
    printf("\n");

    for(i = 0; i <= board->maxrow; i++){
        printf("%i",i+1);
        for(j = 0; j <= board->maxcol; j++){
           printf("|%c",board->position[j][i]);
        }
        printf("|\n");
    }
    printf("\n");
}
