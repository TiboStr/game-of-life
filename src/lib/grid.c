#include "grid.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


Grid *init_grid(int width, int height) {
    Grid *grid = malloc(sizeof(Grid));

    grid->width = width;
    grid->height = height;
    grid->cells = (Cell *) calloc(width * height, sizeof(Cell));

    return grid;
}

void destroy_grid(Grid *grid) {
    free(grid->cells);
    free(grid);
}

/*Grid *deep_copy_grid(Grid *original_grid) {
    Grid *new_grid = malloc(sizeof(Grid));

    new_grid->width = original_grid->width;
    new_grid->height = original_grid->height;

    new_grid->cells = (Cell *) calloc(new_grid->width * new_grid->height, sizeof(Cell));
    memcpy(new_grid->cells, original_grid->cells, new_grid->width * new_grid->height);

}*/


void set_cell(Grid *grid, int x, int y, int alive) {

    int index = y * grid->width + x;


    assert(index < grid->width * grid->height /*Wrong x and y values*/);
    assert(alive == 1 || alive == 0 /*Wrong value for parameter 'alive' (should be 1 or 0)*/);

    //printf("x y: %d %d\n", x, y);

    //printf("%d\n", grid->cells[index].state & 0x01);


    assert(
            (
                    /*You try to set a cell as alive, but it is already alive*/
                    alive == 1 && (grid->cells[index].state & 0x01) == 0
            ) ||
            (
                    /*You try to set a cell as alive, but it is already alive*/
                    alive == 0 && (grid->cells[index].state & 0x01) == 1
            )
    );

    int neighbour_coordinates[8][2] = {
            {x - 1, y - 1},
            {x,     y - 1},
            {x + 1, y - 1},
            {x + 1, y},
            {x + 1, y + 1},
            {x,     y + 1},
            {x - 1, y + 1},
            {x - 1, y}
    };

    if (alive) {
        grid->cells[index].state |= 0x01;
    } else {
        grid->cells[index].state &= ~0x01;
    }

    // Change neighbour count of all neighbours of the cell
    int change[] = {-0x02, 0x02};

    for (int i = 0; i < 8; i++) {
        int x_coord = neighbour_coordinates[i][0];
        int y_coord = neighbour_coordinates[i][1];

        if (x_coord < 0 || y_coord < 0 || x_coord >= grid->width || y_coord >= grid->height) {
            continue;
        }

        grid->cells[y_coord * grid->width + x_coord].state += change[alive];

    }

}

void generate_random_grid(Grid *grid) {

    for (int x = 0; x < grid->width; x++) {
        for (int y = 0; y < grid->height; y++) {
            if (((float) rand() / (float) (RAND_MAX)) > 0.70) {
                set_cell(grid, x, y, 1);
            }
        }
    }
}

void generate_grid_from_coordinates(Grid *grid, char *file) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Could not read file %s\n", file);
        exit(EXIT_FAILURE);
    }


    while ((read = getline(&line, &len, fp)) != -1) {
        // Strip newline
        while (line[read - 1] == '\r' || line[read - 1] == '\n') {
            line[--read] = 0;
        }

        // Blank line
        if (!read) {
            continue;
        }

        int x;
        int y;

        int res = sscanf(line, "%d %d", &x, &y);

        if (res != 2 /*on success, sscanf returns number of input items*/) {
            printf("Error while parsing file '%s', make sure your coordinates are integers values seperated by one space",
                   file);
            exit(EXIT_FAILURE);
        }

        if (x < 0 || x >= grid->width || y < 0 || y >= grid->height) {
            printf("Error while parsing file '%s'. Make sure your coordinates are valid integer values.\n", file);
            printf("The x value cannot be smaller than 0 or bigger than the width (=%d).\n", grid->width);
            printf("The y value cannot be smaller than 0 or bigger than the height (=%d).\n", grid->height);
            exit(EXIT_FAILURE);
        }

        set_cell(grid, x, y, 1);

    }

    fclose(fp);
    if (line)
        free(line);

}

void generate_grid_from_drawing(Grid *grid, char *file) {

}


void next_generation(Grid *grid) {

    Cell *buffer = (Cell *) calloc(grid->width * grid->height, sizeof(Cell));
    memcpy(buffer, grid->cells, grid->width * grid->height);

    Grid *grid_copy;
    grid_copy->width = grid->width;
    grid_copy->height = grid->height;
    grid_copy->cells = buffer;


    for (int cell_index = 0; cell_index < grid->width * grid->height; cell_index++) {
        if (!grid->cells[cell_index].state) {
            // No neighbours and not alive
            continue;
        }

        int number_of_neighbours = grid->cells[cell_index].state >> 1;

        int x = cell_index % grid->width;
        int y = (cell_index - x) / grid->width;

        assert(y * grid->width + x == cell_index /*x and y are wrongly calculated*/);

        // unsigned char s = grid->cells[cell_index].state;

        if (grid->cells[cell_index].state & 0x01) {
            // Cell is alive, only survives if cell has two or three neighbours
            if (!(number_of_neighbours == 2 || number_of_neighbours == 3)) {
                set_cell(grid_copy, x, y, 0);
                //printf("kill: %d %d\n", x, y);
            }

        } else {
            // Cell is not alive, becomes alive if it has 3 neighbours
            if (number_of_neighbours == 3) {
                set_cell(grid_copy, x, y, 1);
                //  printf("make alive: %d %d\n", x, y);

            }

        }

    }

    memcpy(grid->cells, buffer, grid->width * grid->height);
    free(buffer);

}

void print_grid(Grid *grid) {


    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            //  printf("%d\n", grid->cells[y*grid->width+x].state);

            if ((grid->cells[y * grid->width + x].state & 0x01) == 1) {
                printf("█");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}


