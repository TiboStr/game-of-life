#ifndef GAME_OF_LIFE_GRID_H
#define GAME_OF_LIFE_GRID_H


typedef struct {
    // 8-bits:
    //     most significant bit, means alive, middle 4 bits are to store number of neighbours, 3 leas significant bits are unused
    //     000 0000 1 means alive with no neighbours
    //     000 1000 1 means alive with 8 neighbours
    unsigned char state;
} Cell;

typedef struct {
    int width;
    int height;

    Cell *cells;
} Grid;


Grid *init_grid(int width, int height);

void destroy_grid(Grid *grid);

void set_cell(Grid *grid, int x, int y, int alive);

void generate_random_grid(Grid *grid);

void generate_grid_from_coordinates(Grid *grid);

void generate_grid_from_drawing(Grid *grid);

void next_generation(Grid *grid);

void print_grid(Grid *grid);


#endif //GAME_OF_LIFE_GRID_H
