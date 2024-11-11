#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_RAND 9
#define rand() ((rand() % MAX_RAND) + 1)
#define log(name, format, ...) { printf("%s[!]%s %s %s❱❱%s ", BLACK, CYAN, name, BLACK, NORMAL); \
                                 printf(format, __VA_ARGS__); }

#define NORMAL "\033[0;37m"
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"

bool CheckRows(uint8_t*** _board);
bool CheckGroups(uint8_t*** _board);
bool CheckColumns(uint8_t*** _board);

uint8_t*** GenerateBoard(uint32_t _seed);
int CheckBoard(uint8_t*** _board);

void DrawBoard(uint8_t*** _board);
