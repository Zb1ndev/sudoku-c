#include "sudoku.h"

#pragma region CHECKS

    bool CheckColumns(uint8_t*** _board) {
        for (size_t x = 0; x < 9; x++) {
            uint8_t _offset = ((int)x / 3);
            uint8_t _numbers[9] = {1,2,3,4,5,6,7,8,9};
            for (size_t g = 0; g < 3; g++) {
                for (size_t y = 0; y < 3; y++) {
                    if (_numbers[_board[(g*3)+_offset][y][x%3]-1] == 0)
                        return false;
                    _numbers[_board[(g*3)+_offset][y][x%3]-1] = 0;
                }
            }
        }
        return true;
    }
    bool CheckGroups(uint8_t*** _board) {
        for (size_t g = 0; g < 9; g++) {
            uint8_t _numbers[9] = {1,2,3,4,5,6,7,8,9};
            for (size_t y = 0; y < 3; y++) {
                for (size_t x = 0; x < 3; x++) {
                    if (_numbers[_board[g][y][x]-1] == 0)
                        return false;
                    _numbers[_board[g][y][x]-1] = 0;
                }
            }
        }
        return true;
    }
    bool CheckRows(uint8_t*** _board) {
        for (size_t y = 0; y < 9; y++) {
            uint8_t _offset = (((int)y / 3) * 3);
            uint8_t _numbers[9] = {1,2,3,4,5,6,7,8,9};
            for (size_t g = 0; g < 3; g++) {
                for (size_t x = 0; x < 3; x++) {
                    if (_numbers[_board[g+_offset][y%3][x]-1] == 0)
                        return false;
                    _numbers[_board[g+_offset][y%3][x]-1] = 0;
                }
            }
        }
        return true;
    }
    int CheckBoard(uint8_t*** _board) { 
        return CheckColumns(_board) && CheckRows(_board) && CheckGroups(_board);
    }

#pragma endregion
#pragma region DRAWING

    void DrawBoard(uint8_t*** _board) {
        printf("%s┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓\n",NORMAL);
        for (size_t x = 0; x < 9; x++) {
            for (size_t g = 0; g < 3; g++)  {
                printf("┃");
                int _realGroup = (g + ((int)x / 3) * 3);
                for (size_t y = 0; y < 3; y++)  {
                    printf(" %d ", _board[_realGroup][x%3][y]);
                }
            }
            printf("┃\n");
            if ((x+1) % 3 == 0 && x+1 != 9) 
                printf("┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫\n");   
        }
        printf("┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛\n");
    }

#pragma endregion
#pragma region GENERATOR

    uint8_t** GetRows(uint8_t*** _board, size_t _y) {

        uint8_t** _res = malloc(3 * sizeof(uint8_t*));
        for (size_t i = 0; i < 3; i++) 
            _res[i] = malloc(9 * sizeof(uint8_t));    

        for (size_t y = _y * 3; y < (_y * 3) + 3; y++) {
            uint8_t _counter = 0; // X Position [1..9]
            uint8_t _offset = (((size_t)y / 3) * 3); // [3x3] Group Offset
            for (size_t g = 0; g < 3; g++) // Iterate hrough group
                for (size_t x = 0; x < 3; x++) // Iterate through X positions of group
                    _res[y%3][_counter++] = _board[g+_offset][y%3][x];
        }

        return _res;

    }
    uint8_t**  SortRow(uint8_t** _rows, uint8_t _row) {
        
    }


    uint8_t*** GenerateBoard(uint32_t _seed) {

        srand(_seed);
        clock_t start = clock();
        
        // Generate Random Numbers 1..9 in each Group (3x3) 
        uint8_t*** _board = malloc(sizeof(uint8_t**) * 9);
        for (size_t g = 0; g < 9; g++) {
            int _counter = 0;
            int _numbers[9] = {1,2,3,4,5,6,7,8,9};
            _board[g] = malloc(sizeof(uint8_t**) * 3);
            for (size_t y = 0; y < 3; y++) {
                _board[g][y] = malloc(sizeof(uint8_t*) * 3);
                for (size_t x = 0; x < 3; x++) {
                    int _index = rand() % (9 - _counter);
                    _board[g][y][x] = _numbers[_index];
                    _numbers[_index] = _numbers[(9 - _counter++) - 1];
                }
            }
        }

        // Sort Board
        /*
            Rows -
            For each group, we are going to manually sort the first two rows. To do this we will get all three rows in a array
            get the duplicates and the values that are not existent of each and go about sorting the first 2 rows.

            Columns - 
            I think you do the same thing as in the rows but there is some redundant checks to ensure it makes a real board.
        */

        for (size_t g = 0; g < 3; g++) {

            uint8_t** _rows = GetRows(_board, g);
            for (size_t r=0; r<2; r++) 
                SortRow(_rows, r);
        
        }
        
        log("TIME", "%fms\n", (((double) (clock() - start)) / CLOCKS_PER_SEC)*1000);
        return _board;

    }

#pragma endregion