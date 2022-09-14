#include "grid.h"

int main() {

    Grid* grid = init_grid(10, 10);

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
