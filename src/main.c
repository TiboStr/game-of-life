#include "lib/grid.h"

#include <stdio.h>
#include <argp.h> /* https://www.linuxtopia.org/online_books/programming_books/gnu_c_programming_tutorial/argp-example.html */
#include <stdlib.h>
#include <string.h>

const int DEFAULT_WIDTH = 20;
const int DEFAULT_HEIGHT = 10;

typedef enum {
    random_state, drawing_state, coordinates_state
} program_states;


struct arguments {
    program_states program_state;
    char *infile;
    int width;
    int height;
    int iterations;
};


static struct argp_option options[] = {
        {"random",      'r', 0,            0, "Generate random starting points (default option if nothing is specified)", 0},
        {"drawing",     'd', "FILE",       0, "Read file where a starting pattern is drawn",                              1},
        {"coordinates", 'c', "FILE",       0, "Read file where coordinates are listed",                                   1},
        {"width",       'w', "WIDTH",      0, "The width of the visualization, default value",                            2},
        {"height",      'h', "HEIGHT",     0, "The height of the visualization",                                          2},
        {"iterations",  'i', "ITERATIONS", 0, "Number of generations that will be displayed",                             3},
        {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'r':
            arguments->program_state = random_state;
            break;
        case 'd':
            arguments->program_state = drawing_state;
            arguments->infile = arg;
            break;
        case 'c':
            arguments->program_state = coordinates_state;
            arguments->infile = arg;
            break;
        case 'w':
            arguments->width = atoi(arg);
            break;
        case 'h':
            arguments->height = atoi(arg);
            break;
        case 'i':
            arguments->iterations = atoi(arg);
            break;
        case ARGP_KEY_END:
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options,
                           parse_opt,
                           "",
                           "game_of_life -- An implementation of Conway's Game of Life"};


int main(int argc, char **argv) {

    struct arguments arguments;

    arguments.infile = NULL;
    arguments.program_state = random_state;
    arguments.width = DEFAULT_WIDTH;
    arguments.height = DEFAULT_HEIGHT;
    arguments.iterations = -1;

    /* Parse arguments */
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    /*printf(
            "infile: %s\n"
            "program_state: %i\n"
            "width: %i\n"
            "height: %i\n",
            arguments.infile, arguments.program_state, arguments.width, arguments.height
    );*/


    Grid *grid = init_grid(arguments.width, arguments.height);

    if (arguments.program_state == random_state) {
        generate_random_grid(grid);
    } else {
        void (*functions[2])(Grid *grid, char *file);
        functions[0] = generate_grid_from_drawing;
        functions[1] = generate_grid_from_coordinates;

        (*functions[arguments.program_state - 1])(grid, arguments.infile);
    }


    simulate_grid(grid, arguments.iterations);

    destroy_grid(grid);

}
