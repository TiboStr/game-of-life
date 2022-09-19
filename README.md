# Game of Life

This is a c implementation of Conway's Game of Life.

You can use e.g. CMake to build an executable.

## Usage

```bash
$ game_of_life --help
Usage: game_of_life [OPTION...] 
game_of_life -- An implementation of Conway's Game of Life

  -r, --random               Generate random starting points (default option if
                             nothing is specified)
  -c, --coordinates=FILE     Read file where coordinates are listed
  -d, --drawing=FILE         Read file where a starting pattern is drawn
  -h, --height=HEIGHT        The height of the visualization
  -w, --width=WIDTH          The width of the visualization
  -?, --help                 Give this help list
      --usage                Give a short usage message

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
```

See [examples/](./examples/README.md) for more information.

## License

This project is licensed under the terms of the MIT License. See [LICENSE.md](LICENSE.md) for more details.