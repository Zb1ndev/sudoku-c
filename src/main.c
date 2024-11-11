#include <stdio.h>
#include <time.h>

#include "sudoku/sudoku.h"

int main(void) {

    uint32_t _seed = time(NULL); 
    log("SEED", "%s%d\n", GREEN, _seed);
    uint8_t*** _board = GenerateBoard(_seed);

    if (CheckBoard(_board) == false)
        log("NOTE", "%sFailed to generate good board!\n", RED);
    DrawBoard(_board);

    
    return 0;
    
}