#include "lib/grid.h"

#include <stdio.h>
#include <argp.h> /* https://www.linuxtopia.org/online_books/programming_books/gnu_c_programming_tutorial/argp-example.html */

typedef enum {
    random, drawing, coordinates
} program_states;


struct arguments {
    program_states program_state;
    char *infile;
};

static struct argp_option options[] = {
        {"random",      'r', 0,      0, "Generate random starting points (default option)"},
        {"drawing",     'd', "FILE", 0, "Read file where a starting pattern is drawn"},
        {"coordinates", 'c', "FILE", 0, "Read file where coordinates are listed"},
        {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'r':
            arguments->program_state = random;
            break;
        case 'd':
            arguments->program_state = drawing;
            arguments->infile = arg;
            break;
        case 'c':
            arguments->program_state = coordinates;
            arguments->infile = arg;
            break;
        case ARGP_KEY_NO_ARGS:
            arguments->program_state = random;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, "", "game_of_life -- An implementation of Conway's Game of Life"};


int main(int argc, char **argv) {

    struct arguments arguments;

    arguments.infile = NULL;
    arguments.program_state = random;

    /* Parse arguments */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);


    Grid *grid = init_grid(10, 10);

    printf("start\n");

    print_grid(grid);

    printf("------------------\n");

    next_generation(grid);
    print_grid(grid);


    printf("------------------\n");


    next_generation(grid);
    print_grid(grid);

    printf("------------------\n");

    next_generation(grid);
    print_grid(grid);

    destroy_grid(grid);

    printf("done\n");
}
