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

    uint8_t*** GenerateBoard(uint32_t _seed) {

        srand(_seed);
        clock_t start = clock();

        int _test = 0;
        uint8_t*** _board = malloc(sizeof(uint8_t**) * 9);
        for (size_t g = 0; g < 9; g++) 
            _board[g] = malloc(sizeof(uint8_t**) * 3);

        for (size_t g = 0; g < 9; g++) {
            for (size_t y = 0; y < 3; y++) {
                _board[g][y] = malloc(sizeof(uint8_t*) * 3);
                for (size_t x = 0; x < 3; x++) {
                    _board[g][y][x] = 1;
                }
            }
        }
        

        log("TIME", "%fs\n", ((double) (clock() - start)) / CLOCKS_PER_SEC);
        return _board;

    }

#pragma endregion
