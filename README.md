# Project 1 - Clue Text Adventure Game by Aymaan Shaikh

Welcome to the Clue Text Adventure Game. The objective of this game is to unravel the mystery by discovering where the murder took place, identifying the murder weapon, and uncovering the culprit.

## Compilation

To compile and run the game, follow these steps in your terminal:

1. Open your terminal.
2. Type the following command to compile the source code:
   ```
   gcc -o cluegame adventure.c characters.c characters.h items.c items.h player.c player.h rooms.c rooms.h
   ```
3. Once compiled, execute the game by typing:
   ```
   ./cluegame
   ```

## Game Components

This game is built upon several source files, each with specific functionalities:

- `adventure.c`: Contains the main function, as well as functions to read user input and interpret commands.
- `characters.c` and `characters.h`: Implement data structures and functions related to characters in the game.
- `items.c` and `items.h`: Define data structures and functions for handling items within the game.
- `player.c` and `player.h`: Manage the player's data structures and related functions.
- `rooms.c` and `rooms.h`: Implement data structures and functions for rooms and their connections.

## Game Structure

The game employs a linked-list structure to dynamically allocate memory for different components. It consists of three main types of linked lists: Characters, Items, and Rooms. Each room has its own linked lists for items and characters, while the player maintains an inventory using a linked list of items.

Rooms are interconnected through directional pointers (north, east, south, west), forming a navigable game map. The items and characters are populated randomly within rooms using pointers to individual items and characters from the main linked lists.

## Managing User Input

User input is managed using the `gets()` function, which reads input from the user and processes it. The game prompts the user for valid inputs and uses functions like `strncmp` and `strcmp` to validate and interpret commands.

## Game Functionality

The game boasts the following features:

1. Nine interconnected rooms, including a starting room, creating a navigable game map.
2. Randomized room placements using the `shuffleRoomIndexes()` function.
3. A variety of items and characters, with rooms initially containing at most one item each.
4. Randomly chosen murder scenario: room, item, and character.
5. Inventory management for rooms and the player's avatar.
6. A set of commands for players, including help, list, look, go, take, drop, inventory, and clue.
7. Error handling for incorrect inputs, prompting users to re-enter commands.
8. Winning and losing conditions based on player guesses.

## Extra Features

The game includes additional features:

- An easter egg for players to discover.
- A blood radius indicating proximity to the murder room.
- Visual indicators for the murder room's proximity.

**Note:** The game includes a total of 9 rooms, 6 items, and 5 characters. Players can use the provided commands to interact with the game world and uncover the truth.

Feel free to explore the game, solve the mystery, and enjoy the adventure!
