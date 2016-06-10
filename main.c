#include <stdio.h>
#include "board.h"
#include "file.h"

//TODO: IMPORTANTE!!! printReport não está a funcionar bem quando o tabuleiro é aumentado
//TODO: validacoes dos menus!!!
/*Escreve o menu principal no ecra e devolve a opcao escolhida*/
int mainMenu() {
    int result;

    printf("********** Jogo do Comilao **********\n");
    printf("*                                   *\n");
    printf("*   1)Novo Jogo                     *\n");
    printf("*   2)Carregar Jogo                 *\n");
    printf("*                                   *\n");
    printf("*************************************\n");
    do {
        printf("   Opcao: ");;
        scanf("%i",&result);
        if (result != 1 && result != 2) printf("Opção inválida!\n");
    } while (result != 1 &&result != 2);

    return result;
}
/*Escreve o menu anterior a realização de uma jogada no ecra e devolve a opcao escolida*/
int menuPrePlay(Player* player,CoordList *moves){
    int result;
    printf("Jogador%c\n",player->name);
    printf("  |Jogada n:%i\n",(moves->size +1));
    printf("  |  1)Mostrar Jogadas Realizadas\n");
    printf("  |  2)Salvar Jogo\n");
    printf("  |  3)Continuar\n");
    do {
        printf("  |Opcao -> ");;
        scanf("%i",&result);
        if (result != 1 && result != 2 && result !=3) printf("Opção inválida!\n");
    } while (result != 1 && result != 2 && result !=3);
    return result;
};
/*Escreve o menu posterior a realização de uma jogada no ecra e devolve a opcao escolida*/
int menuPostPlay(Player* player,CoordList *moves){
    int result;
    printf("Jogador%c\n",player->name);
    printf("  |Jogada n:%i\n",(moves->size));
    printf("  |  1)Aumentar Tabuleiro\n");
    printf("  |  2)Salvar Jogo\n");
    printf("  |  3)Continuar\n");
    do {
        printf("   Opcao: ");;
        scanf("%i",&result);
        if (result != 1 && result != 2 && result !=3) printf("Opção inválida!\n");
    } while (result != 1 && result != 2 && result !=3);
    return result;
};
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

    printf("Estado do Tabuleiro:\n");
    printBoard(board);

    switch(menuPrePlay(currentPlayer,moves)){
        case 1:
            if (moves->size == 0)
                printf("Ainda não foram realizadas jogadas!\n");
            else
                printMoves(moves,players);
            break;
        case 2:
            //TODO: pedir nome do ficheiro
            SaveGame("SaveTest",moves,board->maxcol,board->maxrow);
            break;
        default:
            break;
    }
    /*Pede as coordenadas ao jogador e garante que estas estão dentro do tabuleiro*/
    do {
        getCoords(&x, &y, board->maxcol, board->maxrow);
    }while (!validateMove(board,x,y));

    /*Testa se o player em foco perdeu o jogo*/
    if(makeMoveAndTestFinish(board,currentPlayer,moves,x,y)) {
        Player* currentPlayer = players[((moves->size)+1) % 2] ;
        printf("Jogo terminado! parabens Jogador%c, ganhou o Jogo\n",currentPlayer->name);
        return;
    }
    else if (board->possibleMoves > 1) {
        switch(menuPostPlay(currentPlayer,moves)){
            case 1:
                //todo: implementar aumentar tabuleiro
                /*Aumenta uma linha e uma coluna a board dada*/
                board = resizeBoard(board,moves);
                break;
            case 2:
                //TODO: pedir nome do ficheiro
                SaveGame("SaveTest",moves,board->maxcol,board->maxrow);
                break;
            default:
                break;
        }
        gameLoop(board, players, moves);
    }
        else {
        printf("Jogo terminado! parabens Jogador%c, ganhou o Jogo\n",currentPlayer->name);
        return;
    }

    return;
}

//TODO: ALTERAR as colunas de INTs para CHAR!!!
//TODO: Validar os inputs
int main() {
    /*variaveis preenchidas pelo input do utilizador na func. setBoardSize*/
    int initCol, initRow;
    //char* fileName[50];
    Player **players = createPlayers();
    CoordList *moves = createList();
    Board *board;

    switch (mainMenu()) {
        case 1:
            setBoardSize(&initCol, &initRow, LIMMINCOL, LIMMAXCOL, LIMMINROW, LIMMAXROW);
            board = createBoard(initCol, initRow);
            gameLoop(board, players, moves);
        break;
        case 2:
            //todo: pensar na possibilidade aumentar o tabuleiro quando se faz load de um save no menuPostPlay()
            //printf("Introduza o nome do ficheiro: ");
            //scanf("%s[50]",fileName);
            readBoardSize("SaveTest", &initCol, &initRow);
            board = createBoard(++initCol,++initRow);
            getMovesFromFile("SaveTest", moves);
            loadMovesToBoard(board,moves);
            printf("Jogo Carregado!\n");
            gameLoop(board,players,moves);
        break;

    }

    printMoves(moves,players);
    //TODO: pedir nome do ficheiro
    printReport("teste1.txt",initCol,initRow,moves); //todo: quando for implementado o aumento do tabuleiro vou ter de mudar initCol e initRow
    return 0;
}

