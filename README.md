# Chip8
Chip 8 Interpreter written in C:

30/34 instructions are implimented<br>


## Building and Running:

To build the project run: <br>
```
<unix> location/of/project make
```
Running from the command line:<br>
```
<unix> ./chip8 path/to/rom
```
Running from the command line with logging enabled:<br>
```
<unix> ./chip8 path/to/rom log
```

### Dependencies:
GNU C compiler<br>
SDL2 <br>
A Chip-8 Rom<br>

## Keyboard Layout:

### Chip8 Keypad:
|   |   |   |   |
|---|---|---|---|
| 1 | 2 | 3 | C |
| 4 | 5 | 6 | D |
| 7 | 8 | 9 | E |
| A | 0 | B | F |

### Emulator Keyboard Mapping:
|   |   |   |   |
|---|---|---|---|
| 1 | 2 | 3 | 4 |
| Q | W | E | R |
| A | S | D | F |
| Z | X | C | V |


Press the 'ESC' key to close the emulator
