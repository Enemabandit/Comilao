
#include <stdio.h>
#include "board.h"

/*Pede as coordenadas ao utilizador e garante que estão contidas na board*/
void getCoords(int *x,int *y,int maxCol,int maxRow){
    int invalid;

    do {
        printf("Introduza a coordenada x:");
        scanf("%i", x);
        (*x)--;
        if(validateIntInterval(*x,0,maxCol,2) != 1) {
            printf("x fora dos limites\n");
            invalid = 1;
        } else invalid = 0;
    }while(invalid);

    do {
        printf("Introduza a coordenada y:");
        scanf("%i", y);
        (*y)--;
        if(validateIntInterval(*y,0,maxRow,2) != 1) {
            printf("y fora dos limites\n");
            invalid = 1;
        } else invalid = 0;
    }while(invalid);
}

/*Funcao recursiva que corre cada passo do jogo*/
void gameLoop(Board *board, Player **players, CoordList *moves){
    int x, y;
    /*Alterna o player em foco*/
    Player* currentPlayer = players[moves->size % 2] ;

    printf("Jogador%c\n", currentPlayer->name);
    printBoard(board);

    do {
        getCoords(&x, &y, board->maxcol, board->maxrow);
    }while (!validateMove(board,x,y));

    /*Testa se o player em foco perdeu o jogo*/
    if(makeMoveAndTestFinish(board,currentPlayer,moves,x,y)) {
        Player* currentPlayer = players[((moves->size)++) % 2] ;
        printf("Jogo terminado! parabens Jogador%c, ganhou o Jogo\n",currentPlayer->name);
        return;
    }
    else if (board->possibleMoves > 1)
        gameLoop(board, players, moves);
        else {
        printf("Jogo terminado! parabens Jogador%c, ganhou o Jogo\n",currentPlayer->name);
        return;
    }
}

//TODO: ALTERAR as colunas de INTs para CHAR!!!
//TODO: Validar os inputs
int main() {

    /*variaveis preenchidas pelo input do utilizador na func. setupBoard*/
    int numcol , numrow;

    Player **players = createPlayers();

    Board *board;
    CoordList *moves;

    moves = createList();

    printf("********** Jogo do Comilao **********\n");
    printf("\n");
    setupBoard(&numcol,&numrow,LIMMINCOL,LIMMAXCOL,LIMMINROW,LIMMAXROW);
    board = createBoard(numcol,numrow);

    gameLoop(board, players, moves);
    printMoves(moves,players);
    return 0;
}

