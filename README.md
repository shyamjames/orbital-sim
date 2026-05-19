# orbital-sim 

This project has two C programs:

- `orbital.c` (terminal simulation)
- `orbital_vis.c` (SDL2 visualization)

## Compile commands

### 1) CLI simulation (`orbital.c`)

```bash
gcc -std=c11 -O2 -Wall -Wextra orbital.c -lm -o orbital
```

Flags used:

- `-std=c11`: compile as C11
- `-O2`: optimization level 2
- `-Wall -Wextra`: enable common warnings
- `-lm`: link the math library (`sqrt`, etc.)

### 2) SDL visualization (`orbital_vis.c`)

Use `pkg-config` (recommended):

```bash
gcc -std=c11 -O2 -Wall -Wextra orbital_vis.c $(pkg-config --cflags --libs sdl2) -lm -o orbital_vis
```

If your setup does not use `pkg-config`, link SDL2 directly:

```bash
gcc -std=c11 -O2 -Wall -Wextra orbital_vis.c -lSDL2 -lm -o orbital_vis
```

Additional flags used:

- `$(pkg-config --cflags --libs sdl2)`: SDL2 include path and linker flags
- `-lSDL2`: link SDL2 directly (manual mode)

## Run

```bash
./orbital
./orbital_vis
```

If `orbital_vis.c` fails to compile, install SDL2 development headers for your OS and re-run the command.


Hello