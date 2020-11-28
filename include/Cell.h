/**
 * @file Cell.h
 * @author Paul Toffoloni
 * @date October 26, 2020
 * @brief File containing the definition and usage for Lasca:
 * Cell represents one of the single cells that make up the board.
 */
#ifndef Cell_h
#define Cell_h

#include "Piece.h"
#include <stdlib.h>

enum CellColor {
   white = 0,
   black = 1
};
/**
 * Cell represents one of the single cells that make up the board.
 * It contains its coordinates and the piece on it, this way we can access
 * every piece by having the cell.
 */
typedef struct Cell {
    int x, y;     /**< The x and y coordinates of the cell in the board. */
    int color;    /**< The color of the cell. */
    Piece *piece;/**< Pointer that represents the piece in the cell. */

} Cell;

/**
 * Prints the piece of a cell.
 * If the piece is NULL, prints 0.
 * If the piece is other than NULL, prints a number indicating the height of the piece,
 * of the color of the piece.
 * @param cell The pointer of the cell of which the content has to be printed.
 */
void print_cell_content(Cell *cell);

/**
 * Sets the pointer of the piece of a cell to NULL.
 * @param cell The cell of which the pointer has to be set to NULL.
 */
void set_cell_empty(Cell *cell);

/**
 * Returns the piece of a cell.
 * @param cell The cell of which the piece has to be printed.
 * @return The piece of the indicated cell.
 */
Piece* get_piece(Cell *cell);

/**
 * Sets selected piece on the selected cell.
 * @param cell The cell the piece has to be set on.
 * @param piece The piece that has to be changed of cell.
 */
void set_piece(Cell *cell, Piece* piece);

/**
 * Checks if the piece in the cell is empty or not.
 * @param cell The cell that has to be checked.
 * @return 0 if the cell is empty.
 */
int is_cell_empty(Cell *cell);

/**
 *
 * @param cell
 * @return
 */
int is_cell_white(Cell *cell);

/**
 * Creates a piece assigning memory and attributes.
 * @param cell The cell that gets is piece initialized.
 * @param color The color of which the initialized piece has to be.
 */
void init_piece(Cell* cell, int color);

#endif /* Cell_h */
