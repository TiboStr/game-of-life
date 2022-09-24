#include <string.h>
#include "util.h"

/* Reads a file and returns the number of lines in this file. */
/* https://stackoverflow.com/a/30792411 */
unsigned int count_lines(FILE *file) {
    unsigned int lines = 0;
    int32_t c;
    int32_t last = '\n';
    while (EOF != (c = fgetc(file))) {
        if (c == '\n' && last != '\n') {
            ++lines;
        }
        last = c;
    }

    rewind(file);
    return lines;
}


unsigned int get_longest_line_in_file(FILE *file, char *longest_line) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    unsigned int longest = 0;

    while ((read = getline(&line, &len, file)) != -1) {

        if (read > longest) {
            longest_line = realloc(longest_line, read + 1);
            strcpy(longest_line, line);

            while (line[read - 1] == '\r' || line[read - 1] == '\n') {
                line[--read] = 0;
            }

            longest = read;
        }


    }

    rewind(file);
    return longest;

}

