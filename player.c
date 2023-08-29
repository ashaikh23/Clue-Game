#include "player.h"
#include <stdlib.h>
#include "rooms.h"
#include <time.h>
#include "items.h"
#include "characters.h"

void look(struct Player *player) {
    //Print all items in room
    int i = 0;
    printf("Room name: %s", player->curRoom->name);
    printf("\nItems in room: ");
    while (getItem(player->curRoom->itemListHead, i) != NULL) {
        printf("%s, ", getItem(player->curRoom->itemListHead, i)->name);
        i++;
    }

    //Print all Characters in room
    i = 0;
    printf("\nCharacters in room: ");
    while (getCharacter(player->curRoom->characterListHead, i) != NULL) {
        printf("%s, ", getCharacter(player->curRoom->characterListHead, i)->name);
        i++;
    }

    //Print all Rooms in room
    if (player->curRoom->south != NULL) {
        printf("\nThere is a room to the south!");
    }
    if (player->curRoom->north != NULL) {
        printf("\nThere is a room to the north!");
    }
    if (player->curRoom->east != NULL) {
        printf("\nThere is a room to the east!");
    }
    if (player->curRoom->west != NULL) {
        printf("\nThere is a room to the west!");
    }
    if (player->curRoom->isBloody == NULL) {
        printf("\nRoom is not bloody!");
    } else if (player->curRoom->isBloody == true) {
        printf("\nRoom is bloody!");
    }
}

//Player curRoom updated based on input
void go(struct Player *player, char *input) {
    if (input == "north" && player->curRoom->north != NULL) {
        player->curRoom = player->curRoom->north;
    } else if (input == "south" && player->curRoom->south != NULL) {
        player->curRoom = player->curRoom->south;
    } else if (input == "east" && player->curRoom->east != NULL) {
        player->curRoom = player->curRoom->east;
    } else if (input == "west" && player->curRoom->west != NULL) {
        player->curRoom = player->curRoom->west;
    } else {
        printf("Room not found!");
    }
}

//Take item from room to player inventory
struct Player *takeItem(struct Player *player, char *input, struct Room *roomHead) {
    int i = 0;
    int j = 0;

    //Go through each room, then go through each rooms itemlist, then compare each time to input
    while (getRoom(roomHead, j) != NULL) {
        if (getRoom(roomHead, j)->itemListHead != NULL) {
            while (getItem(getRoom(roomHead, j)->itemListHead, i) != NULL) {
                if (getRoom(roomHead, j)->itemListHead != NULL) {
                    if (getItem(getRoom(roomHead, j)->itemListHead, i)->name == input) {
                        //insert into player itemlist at 0
                        printf("\n%s", getItem(getRoom(roomHead, j)->itemListHead, i)->attribute);
                        struct Item *newItem = getItem(getRoom(roomHead, j)->itemListHead, i);
                        getRoom(roomHead, j)->itemListHead = removeItem(getRoom(roomHead, j)->itemListHead, input);
                        player->itemList = insertItem(player->itemList, 0, newItem);
                        return player;
                    }
                }
                i++;
            }
        }
        j++;
        i = 0;
    }
    return player;
}

//Take item from player inventory to room inventory
struct Player *dropItem(struct Player *player, char *input, struct Item *itemHead) {
    int i = 0;
    while (getItem(itemHead, i) != NULL) {
        if (getItem(itemHead, i)->name == input) {
            player->curRoom->itemListHead = insertItem(player->curRoom->itemListHead, 0, getItem(itemHead, i));
            player->itemList = removeItem(player->itemList, input);
            return player;
        }
        i++;
    }
    return player;
}

//Lists player inventory
void listInventory(struct Player *player) {
    int i = 0;
    printf("\nInventory:");
    while (getItem(player->itemList, i) != NULL) {
        if (getItem(player->itemList, i)->name != NULL) {
            printf("     %s", getItem(player->itemList, i)->name);
        }
        i++;
    }
    printf("\n");
}

//lists out all the possible items, characters and rooms in the game
void list() {
    printf("\nItems in game: Rope, Pipe, Shovel, Knife, Pencil, Lighter\n");
    printf("Characters in game: Gardener, Cook, Smoker, Mechanic, Maid\n");
    printf("Rooms in game: Study, Kitchen, Office, Greenhouse, Bathroom, Bedroom, Garage, Smokeroom, Dining Room\n");
}

//Lists out all usable commands in the game
void help() {
    printf("\nCommands(CASE SENSITIVE):\n");
    printf("go DIRECTION  : (move to the room in the direction stated, ex: go north)\n");
    printf("list : (lists out all the rooms/items/characters in the game)\n");
    printf("look : (lists out all the items and characters in the room, as well as the nearby rooms)\n");
    printf("take ITEMNAME(pickup item ITEMNAME from room)\n");
    printf("drop ITEMNAME(drop item ITEMNAME from player inventory to room)\n");
    printf("inventory(list out the players inventory)\n");
    printf("clue ITEMNAME CHARNAME(guess who commited the murder using what)\n");
    printf("help : (lists out all the commands in the game)\n");
    printf("quit : (used to quit prompts to retype inputs)\n");
}

struct Player *clue(struct Player *player, char *itemInput, char *charInput, struct Room *roomHead) {
    bool validRoom = false, validItem = false, validChar = false;

    //increment guesses every time clue is called
    player->guesses++;

    //Check if curRoom is murder room
    if (player->curRoom->isMurderRoom == true) {
        validRoom = true;
    }

    //Check if murder item is in inventory
    int i = 0;
    while (getItem(player->itemList, i) != NULL) {
        if (strcmp(getItem(player->itemList, i)->name, itemInput) == 0 && getItem(player->itemList, i)->isMurderItem) {
            validItem = true;
        }
        i++;
    }

    //Check if murder item is in the room
    i = 0;
    while (getItem(player->curRoom->itemListHead, i) != NULL) {
        if (getItem(player->curRoom->itemListHead, i)->name == itemInput &&
            getItem(player->curRoom->itemListHead, i)->isMurderItem) {
            validItem = true;
        }
        i++;
    }

    ///Make case for already in room

    //go thru each room go thru characters of each room to find and remove/insert accordingly
    i = 0;
    int j = 0;
    while (getRoom(roomHead, j) != NULL && validChar == false) {
        if (getRoom(roomHead, j)->characterListHead != NULL) {
            while (validChar == false && getCharacter(getRoom(roomHead, j)->characterListHead, i) != NULL &&
                   j < numRooms) {
                if (getRoom(roomHead, j)->characterListHead != NULL) {
                    if (strcmp(getCharacter(getRoom(roomHead, j)->characterListHead, i)->name, charInput) == 0) {
                        player->curRoom->characterListHead = insertCharacter(player->curRoom->characterListHead, 0,
                                                                             getCharacter(getRoom(roomHead,
                                                                                                  j)->characterListHead,
                                                                                          i));
                        getRoom(roomHead, j)->characterListHead = removeCharacter(
                                getRoom(roomHead, j)->characterListHead, charInput);
                        validChar = true;
                    }
                }
                i++;
            }
        }
        j++;
        i = 0;
    }
    //Winning cases
    if (validRoom) {
        printf("Valid room!");
    } else {
        printf("invalid room!");
    }
    if (validItem) {
        printf("Valid item!");
    } else {
        printf("invalid item!");
    }
    if (validChar) {
        printf("Valid char!");
    } else {
        printf("invalid char!");
    }
    if (validRoom && validItem && validChar) {
        printf("YOU WON!");
        player->guesses = 100;
    } else {
        printf("Try again");
    }
    return player;
}