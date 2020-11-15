/**
 * @file Game.c
 * @author Giovanni Frigerio Zeno
 * @date October 31, 2020
 * @brief File containing the source code for Lasca:
 * Game controls the whole game, so if a piece is moved or the game has to end,
 * this file is in charge of it.
 */
#include <stdio.h>
#include "Game.h"
#include "Cell.h"
#include "Board.h"
#include "Play.h"

void move_piece(Board *board, int turn) {
    int x, y;
    Piece *piece;
    Cell *initialCell;

    /* Gets data from user input */
    x = get_x_input_coordinate();
    y = get_y_input_coordinate();

    /* Checks input data for impossible moves */
    if (check_initial_input(board, x, y) == 1) {
        initialCell = get_cell(board, x, y);
        piece = get_piece(initialCell);
        /* Gets data from user input */
        x = get_x_input_coordinate();
        y = get_y_input_coordinate();
        /* Sets the piece to the new cell */
        set_piece(get_cell(board, x, y), piece);
        /* Deletes the piece from the old cell */
        set_cell_empty(initialCell);
    }
}

int check_initial_input(Board* board, int x, int y) {
    if (is_cell_white(get_cell(board, x, y)) == 1)
        if (is_cell_empty(get_cell(board, x, y)) == 0)
            if (can_piece_move(get_cell(board, x, y), board) == 1)
                return 1;
            else
                printf("Questa pedina non può essere mossa in nessuna cella, riprova.\n");
        else
            printf("Qui non c'è nessuna pedina! Riprova.\n");
    else
        printf("Quella cella non fa parte del campo, riprova.\n");
    return 0;
}

int check_final_input(Board* board, int x, int y) {
    if (is_cell_white(get_cell(board, x, y)) == 1) {
        if (is_cell_empty(get_cell(board, x, y)) == 1) {
            /* TODO: Add control for if cell is next to first cell or if you can eat */

            return 1;
        } else {
            printf("Qui c'è già una pedina! Riprova.\n");
        }
    } else {
        printf("Quella cella non fa parte del campo, riprova.\n");
    }
    return 0;
}

int can_piece_move(Cell* cell, Board* board) {

    Cell *move1, *move2, *move3, *move4;

    Play *play = malloc(sizeof(Play));
    play[0] = *new_play(1, 2, red, soldier, cell, move1);

    move1 = get_cell(board, cell->x + 1, cell->y - 1);  /* move1-2-3-4 are the all movement you can do on the board */
    move2 = get_cell(board, cell->x - 1, cell->y - 1);
    move3 = get_cell(board, cell->x - 1, cell->y + 1);
    move4 = get_cell(board, cell->x + 1, cell->y + 1);

    if (cell->piece->type == soldier && turn == red) {   /* check the type of piece*/
        if (move1 != NULL)                /* if the cell are empty you can move the piece on the next cell*/
            return is_cell_empty(move1);
        if (move2 != NULL)
            return is_cell_empty(move2);
        return 0;
    }

    if (cell->piece->type == soldier && turn == yellow) {   /* check the type of piece*/
        if (move3 != NULL)                /* if the cell are empty you can move the piece on the next cell*/
            return is_cell_empty(move1);
        if (move4 != NULL)
            return is_cell_empty(move2);
        return 0;

    if (cell->piece->type == column) {   /* same control for the column piece */
        if (move1 != NULL)
            return is_cell_empty(move1);
        if (move2 != NULL)
            return is_cell_empty(move2);
        if (move3 != NULL)
            return is_cell_empty(move3);
        if (move4 != NULL)
            return is_cell_empty(move4);
        return 0;
    }
    return 0;
}


int you_can_eat(Cell* cell, Board* board) {
    Cell *eat1;
    Cell *eat2;
    Cell *eat3;
    Cell *eat4;
    Cell *move1;
    Cell *move2;
    Cell *move3;
    Cell *move4;

    move1 = get_cell(board, cell->x + 1, cell->y - 1);
    move2 = get_cell(board, cell->x - 1, cell->y - 1);
    move3 = get_cell(board, cell->x - 1, cell->y + 1);
    move4 = get_cell(board, cell->x + 1, cell->y + 1);
    eat1 = get_cell(board, cell->x + 1, cell->y - 1);
    eat2 = get_cell(board, cell->x - 1, cell->y - 1);
    eat3 = get_cell(board, cell->x - 1, cell->y + 1);
    eat4 = get_cell(board, cell->x + 1, cell->y + 1);

    /* TODO: check if the player can move in an empty cell over opponent piece */
    if (is_cell_empty(move1) == 1) {             /* we use 'move' for see if there is a opponent piece */
        if (is_cell_empty(eat1) == 0) {          /* and with 'eat function' for check if there is a empty*/
            printf("%d %d", eat1->x, eat1->y);    /* cell after opponent piece for eat */
            return 0;
        }
    } else if (is_cell_empty(move2) == 1) {
        if (is_cell_empty(eat2) == 0) {
            printf("%d %d", eat2->x, eat2->y);
            return 0;
        }
    } else if (is_cell_empty(move3) == 1 && cell->piece->type == column) {  /* column eat QUI AGGIUNGERE COLORI*/
        if (is_cell_empty(eat3) == 0) {
            printf("%d %d", eat3->x, eat3->y);
            return 0;
        }
    } else if (is_cell_empty(move4) == 1 && cell->piece->type == column) {
        if (is_cell_empty(eat4) == 0) {
            printf("%d %d", eat4->x, eat4->y);
        }
        return 0;

    }
    return 1;
}


int get_x_input_coordinate() {
    int x;
    printf("Inserisci la coordinata x della cella:");
    scanf("%d", &x);
    return x;
}

int get_y_input_coordinate() {
    int y;
    printf("Inserisci la coordinata y della cella:");
    scanf("%d", &y);
    return y;
}
