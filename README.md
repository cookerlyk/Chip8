# Chip8
Chip 8 Interpreter written in C, using SDL2 for graphics.<br><br>

Currently, the interpreter is in a playable state. The only missing core features are the system buzzer and more accurate timing for the execution of the system.

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
### Compatibility:
Verified compatible with Linux and Mac OS.

### Dependencies:
GNU C compiler<br>
Command line tools if you are on Mac OS<br>
[SDL2](https://www.libsdl.org/download-2.0.php) installed on your machine<br>
A copy of a Chip-8 Rom<br>

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

'esc' Key: Close the Emulator
