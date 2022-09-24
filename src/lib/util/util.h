#ifndef GAME_OF_LIFE_UTIL_H
#define GAME_OF_LIFE_UTIL_H

#include <stdio.h>
#include <stdlib.h>


unsigned int count_lines(FILE *file);

unsigned int get_longest_line_in_file(FILE *file, char *longest_line);


#endif //GAME_OF_LIFE_UTIL_H
