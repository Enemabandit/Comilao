#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "file.h"

//TODO: IMPORTANTE!!! free memória sempre que preciso!
//TODO: IMPORTANTE!!! printReport não está a funcionar bem quando o tabuleiro é aumentado
//TODO: validacoes dos menus!!!

void printLogo(){

    printf("                   /""-._ \n");
    printf("                  .      '-,\n");
    printf("                  :         '', \n");
    printf("                  ;      *     '. \n");
    printf("                  ' *         () '. \n");
    printf("                   |               | \n");
    printf("                    |      _.---.._ '. \n");
    printf("                     :  .' _.--''-''  | ,' \n");
    printf("       .._            '/.'             . ; \n");
    printf("        ; `-.          ,                | \n");
    printf("         ;   `,         ;              ._| \n");
    printf("          ;    |     _,-'                ''--._ \n");
    printf("           :    |_,-'                          '-._ \n");
    printf("            | ,-'                       .          '-._ \n");
    printf("           .'         __.-'';             ...,__       '. \n");
    printf("          .'      _,-'       |              |   ''--.,__ '| \n");
    printf("         /   _,--' ;          |             ;            ^.} \n");
    printf("        ;_,-' )     |  )      )              ; \n");
    printf("             /       V  |_.,-'               ; \n");
    printf("            /                               ; \n");
    printf("         ,-'  _,-'''-.    ,-.,             ; \n");
    printf("      ,-' _.-'        |  /    |/'-._...--' \n");
    printf("     :--``             )/                    Jogo do Comilao\n");
}

void printWinner(Player *player){
    printf("\n");
    printf("             .'; \n");
    printf("         .-'` .' \n");
    printf("       ,`.-'-.`|     Jogo Terminado!\n");
    printf("      ; /     '-'\n");
    printf("     |  |       ,-,       Parabens Jogado%c\n",player->name );
    printf("      |  '-.__   )_`'._        Ganhou o jogo!\n");
    printf("       '.     ```      ``'--._ \n");
    printf("      .-' ,                   `'-. \n");
    printf("       '-'`-._           ((   o   ) \n");
    printf("              `'--....(`- ,__..--' \n");
    printf("                       '-'` \n");
}
/*Escreve o menu principal no ecra e devolve a opcao escolhida*/
int mainMenu() {
    int result;
    printLogo();
    printf("                                               |1)Novo Jogo\n");
    printf("                                               |2)Jogar vs bot\n");
    printf("                                               |3)Carregar Jogo\n");
    do {
        printf("   Opcao: ");
        scanf("%i",&result);
        if (result != 1 && result != 2 && result != 3) printf("Opção inválida!\n");
    } while (result != 1 &&result != 2 && result != 3);

    return result;
}
/*Escreve o menu anterior a realização de uma jogada no ecra e devolve a opcao escolida*/
int menuPrePlay(Player* player,CoordList *moves){
    int result;
    printf("Jogador%c\n",player->name);
    printf("  |Jogada n:%i\n",(moves->size +1));
    printf("  |  1)Mostrar Jogadas Realizadas\n");
    printf("  |  2)Salvar Jogo\n");
    printf("  |  3)Introduzir Coordenadas\n");
    do {
        printf("  |Opcao -> ");;
        scanf("%i",&result);
        if (result != 1 && result != 2 && result !=3) printf("Opção inválida!\n");
    } while (result != 1 && result != 2 && result !=3);
    return result;
};
/*Escreve o menu posterior a realização de uma jogada no ecra e devolve a opcao escolida*/
int menuPostPlay(){
    int result;
    printf("  |  1)Aumentar Tabuleiro\n");
    printf("  |  2)Finalizar Jogada\n");
    do {
        printf("   Opcao: ");;
        scanf("%i",&result);
        if (result != 1 && result != 2) printf("Opção inválida!\n");
    } while (result != 1 && result != 2);
    printf("\n");
    return result;
};
/*Pede as coordenadas ao utilizador e garante que estão contidas na board*/
void getCoords(int *x,int *y,int maxCol,int maxRow){
    int invalid;

    do {
        printf("    Introduza a coordenada x -> ");
        scanf("%i", x);
        (*x)--;
        if(validateIntInterval(*x,0,maxCol,2) != 1) {
            printf("x fora dos limites\n");
            invalid = 1;
        } else invalid = 0;
    }while(invalid);

    do {
        printf("    Introduza a coordenada y -> ");
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
            exit(0);
        default:
            break;
    }
    /*Pede as coordenadas ao jogador e garante que estas estão dentro do tabuleiro*/
    do {
        getCoords(&x, &y, board->maxcol, board->maxrow);
    }while (!validateMove(board,x,y));

    /*Testa se o player em foco perdeu o jogo*/
    if(makeMoveAndTestFinish(board,currentPlayer,moves,x,y)) {
        printf("Apanhado no isco!\n");
        Player* currentPlayer = players[((moves->size)) % 2];
        printWinner(currentPlayer);

        return;
    }
    else if (board->possibleMoves > 1) {
        switch(menuPostPlay()){
            case 1:
                /*Aumenta uma linha e uma coluna a board dada*/
                board = resizeBoard(board,moves);
                break;
            default:
                break;
        }
        gameLoop(board, players, moves);
    }
        else {
        printf("Não ha mais jogadas possíveis!\n");
        printWinner(currentPlayer);
        return;
    }

    return;
}

//TODO: ALTERAR as colunas de INTs para CHAR!!!
//TODO: Validar os inputs
int main() {
    /*variaveis preenchidas pelo input do utilizador na func. getBoardSize*/
    int initCol, initRow;
    //char* fileName[50];
    Player **players = createPlayers();
    CoordList *moves = createList();
    Board *board;

    switch (mainMenu()) {
        case 1:
            getBoardSize(&initCol, &initRow, LIMMINCOL, LIMMAXCOL, LIMMINROW, LIMMAXROW);
            board = createBoard(initCol, initRow);
            gameLoop(board, players, moves);
            break;
        case 2:

            break;
        case 3:
            //printf("Introduza o nome do ficheiro: ");
            //scanf("%s[50]",fileName);
            readBoardSize("SaveTest", &initCol, &initRow);
            board = createBoard(initCol,initRow);
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

