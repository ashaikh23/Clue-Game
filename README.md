Project 1 Clue Text Adventure Game Eyssa Benhida, Aymaan Shaikh

The objective of the game is to find out where the murder took place, with what item, and of course, who did it.

Compilation:
Type out: gcc -o cluegame adventure.c characters.c characters.h items.c items.h player.c player.h rooms.c rooms.h

then type: ./cluegame

To compile the code you need all files adventure.c, characters.c, characters.h, items.c, items.h, player.c, player.h, room.c, room.h and, the main function is located in adventure.c 

rooms.c, rooms.h - the source and header file implementing data structures and functions for rooms.
items.c, items.h - the source and header file implementing data structures and functions for items.
adventure.c - the source file with functions to read user input and interpret commands as well as the main function.
characters.c, characters.h – the source and header file implementing data structures and functions for characters.
player.c, player.h – the source and header file implementing data structures and functions for player.

Overview of game board structure:

Pointers:
The game was built using 3 sets of linked lists (Characters, Items, Rooms) which were dynamically allocated into memory
    
Each room has its own linked list (itemList, charList) for inventory and the player has its own linked list(itemList) for inventory.

We use a struct Room with the directions that the rooms have NESW

Each of the items were dynamically allocated memory using malloc and freed using free

Building the game map:
To design the game board, we statically linked each room using the 4 pointers (east, west, north, south). Then we populated the rooms randomly using the rand() function, based on time using pointers to individual items and characters from the main character/item linked lists. 
Simply put, each room contains its own set of Items, and Characters which is effectively an inventory of characters and items in each room, which could be used to add/remove characters/items when needed during gameplay through commands such as take/put/etc.… made by the player.

Managing User Input:

We get the user input, by using the C library function char *gets(char *str), which reads a line from stdin and places it into the string pointed to by the string. It will stop when either the newline char is read or when the end-of-document is reached. In various functions within the code, we used a case-sensitive while loop to ask the user for valid user input or to keep prompting the user for a value that could be used in the game.

When comparing strings, we used the C library function strncmp to compare the first n bytes of the first and second strings, and we also used strcmp, which compares two strings character by character. If the strings are equal then the function returns the value 0, if it's>0 then the ASCII is greater in string one, or if it's lower then it's <0.

Simply put, the game is played by typing in user input and typing commands as well as re-typing if it is incorrect.

Functionality:
1.	The game has 9 rooms including the starting room which is connected via pointers.
2.	The game randomly initializes the location of each room in the game board before the game starts using shuffleRoomIndexes() and we use rand() to 
3.	The game has at least 6 items *itemNames[6] and 5 characters *characterNames[5], other than the player's avatar and each room contains at most one item at the beginning
4.	The game randomly picks a room, an item, and a character as the answer.
5.	The game allows each room to have a linkedList of items
6.	The game implements an avatar where the avatar has an inventory (a linkedList of items as player-> itemList
7.	The game implements a table of commands: help, list, look, go, take, drop, inventory, clue; for each of the functionality of the function’s players can use the command and re-type if they have spelled it incorrectly or making it an invalid input.
8.	The game also included a winning and losing state (if they have 10 guesses)


Extra:
We have included an easter egg which can be found
We also have a blood radius if its next to the murder room, as well as a value if it is the Murder room, close to it, or if it’s not.