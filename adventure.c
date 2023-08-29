#include <stdio.h>
#include <stdlib.h>
#include "rooms.h"
#include "items.h"
#include "characters.h"
#include "player.h"
#include <time.h>

int main() {
    //Shuffling indexes for randomness
    shuffleRoomIndexes();
    shuffleItemIndexes();
    shuffleCharacterIndexes();

    //Initializing Player
    struct Player *player = (struct Player *) malloc
            (sizeof(struct Player));

    //Initializing roomHead
    struct Room *roomHead = (struct Room *) malloc
            (sizeof(struct Room));

    for (int i = 0; i < numRooms; i++) {
        struct Room *newRoom = (struct Room *) malloc
                (sizeof(struct Room));
        newRoom->name = roomNames[i];
        roomHead = insertRoom(roomHead, i, newRoom);
    }

    //Initializing itemHead
    struct Item *itemHead = (struct Item *) malloc
            (sizeof(struct Item));

    for (int i = 0; i < numItems; i++) {
        struct Item *newItem = (struct Item *) malloc
                (sizeof(struct Item));
        newItem->name = itemNames[i];
        newItem->attribute = regularItemAttributes[i];
        itemHead = insertItem(itemHead, i, newItem);
    }

    //Initializing charHead
    struct Character *charHead = (struct Character *) malloc
            (sizeof(struct Character));

    for (int i = 0; i < numCharacters; i++) {
        struct Character *newCharacter = (struct Character *) malloc
                (sizeof(struct Character));
        newCharacter->name = characterNames[i];
        charHead = insertCharacter(charHead, i, newCharacter);
    }

    //Initializing room pointers
    struct Room *result = NULL;
    result = setRoomPointers(roomHead, result);
    roomHead = result;

    //Setting murder deck randomly
    srand(time(NULL));
    int murderRoomIndex = rand() % numRooms;
    int murdererIndex = rand() % numCharacters;
    int murderItemIndex = rand() % numItems;
    setMurderRoom(roomHead, murderRoomIndex)->isMurderRoom = true;

    getItem(itemHead, murdererIndex)->isMurderItem = true;
    getItem(itemHead, murdererIndex)->attribute = murderItemAttributes[murdererIndex];
    getCharacter(charHead, murdererIndex)->isMurderer = true;

    //Setting Blood in and around the murder room
    getRoom(roomHead, murderRoomIndex)->isBloody = true;
    if (getRoom(roomHead, murderRoomIndex)->north != NULL) {
        getRoom(roomHead, murderRoomIndex)->north->isBloody = true;
    }
    if (getRoom(roomHead, murderRoomIndex)->south != NULL) {
        getRoom(roomHead, murderRoomIndex)->south->isBloody = true;
    }
    if (getRoom(roomHead, murderRoomIndex)->west != NULL) {
        getRoom(roomHead, murderRoomIndex)->west->isBloody = true;
    }
    if (getRoom(roomHead, murderRoomIndex)->east != NULL) {
        getRoom(roomHead, murderRoomIndex)->east->isBloody = true;
    }

    //Spawn items in rooms
    roomHead = spawnItems(roomHead, itemHead);
    roomHead = spawnCharacters(roomHead, charHead);

    //Initializing player attributes
    player->curRoom = roomHead;

    //________________GAMEPLAY SECTION________________________//
    char input[20], value[20], charVal[20];
    bool won = false;
    printf("Welcome to the game");
    printf("\nInputs are case-sensitive");

    while (player->guesses <= 10 && won == false) {
        printf("\nEnter Command:");
        gets(input);

        if (strncmp(input, "go", 20) == 0) {
            bool looping = true;
            printf("Go where: ");
            while (looping) {
                gets(value);
                if (strncmp(value, "north", 20) == 0) {
                    go(player, "north");
                    looping = false;
                } else if (strncmp(value, "south", 20) == 0) {
                    go(player, "south");
                    looping = false;
                } else if (strncmp(value, "east", 20) == 0) {
                    go(player, "east");
                    looping = false;
                } else if (strncmp(value, "west", 20) == 0) {
                    go(player, "west");
                    looping = false;
                } else if (strcmp(value, "quit") == 0) {
                    printf("Exited");
                    looping = false;
                } else {
                    printf("Retype go where:");
                }
            }
        } else if (strncmp(input, "list", 20) == 0) {
            list();
        } else if (strncmp(input, "look", 20) == 0) {
            look(player);
        } else if (strncmp(input, "take", 20) == 0) {
            printf("What Item to take:");
            bool looping = true;
            while (looping) {
                gets(value);
                bool itemExists = false;
                int i = 0;
                //Item must exist in room, use while loop to look for item and if item exists pick it up and print inside loop, else
                while (getItem(player->curRoom->itemListHead, i) != NULL && itemExists == false) {
                    char *itemname = getItem(player->curRoom->itemListHead, i)->name;
                    if (strcmp(value, itemname) == 0) {
                        player = takeItem(player, getItem(player->curRoom->itemListHead, i)->name, roomHead);
                        looping = false;
                        itemExists = true;
                    } else {
                        i++;
                    }
                }
                if (player->curRoom->itemListHead == NULL && itemExists == false) {
                    printf("Room is empty!");
                    looping = false;
                } else if (strcmp(value, "quit") == 0) {
                    printf("Exited");
                    looping = false;
                } else if (itemExists == false) {
                    printf("Please retype item name: ");
                }
            }
        } else if (strncmp(input, "drop", 20) == 0) {
            printf("What Item to drop:");
            bool looping = true;
            while (looping) {
                gets(value);
                bool itemExists = false;
                int i = 0;
                //Item must exist in room, use while loop to look for item and if item exists pick it up and print inside loop
                while (getItem(player->itemList, i) != NULL && itemExists == false) {
                    char *itemname = getItem(player->itemList, i)->name;
                    if (strcmp(value, itemname) == 0) {
                        player = dropItem(player, getItem(player->itemList, i)->name, itemHead);
                        looping = false;
                        itemExists = true;
                    } else {
                        i++;
                    }
                }
                looping = false;
                if (player->itemList == NULL && itemExists == false) {
                    printf("Inventory is empty!");
                    looping = false;
                } else if (strcmp(value, "quit") == 0) {
                    printf("Exited");
                    looping = false;
                } else if (itemExists == false) {
                    printf("Please retype item name: ");
                }
            }
        } else if (strncmp(input, "inventory", 20) == 0) {
            listInventory(player);
        } else if (strncmp(input, "easter egg", 20) == 0) {
            printf("Hello Marc or whoever is playing this! :)");
        } else if (strncmp(input, "clue", 20) == 0) {
            char *murderItemGuess;
            char *murderCharGuess;
            bool looping = true;
            bool validCharInput = false;
            bool validItemInput = false;


            while (looping) {
                printf("Murderer name?: ");
                gets(charVal);
                for (int i = 0; i < numCharacters; i++) {
                    if (strcmp(murderCharGuess, characterNames[i]) == 0) {
                        validCharInput = true;
                    }
                }

                murderCharGuess = charVal;
                printf("Murder weapon name?: ");
                gets(value);
                murderItemGuess = value;
                for (int i = 0; i < numItems; i++) {
                    if (strcmp(murderItemGuess, itemNames[i]) == 0) {
                        validItemInput = true;
                    }
                }


                if (validItemInput && validCharInput) {
                    player = clue(player, murderItemGuess, murderCharGuess, roomHead);
                    if (player->guesses > 12) {
                        won = true;
                    }
                    looping = false;
                } else if (strcmp(murderCharGuess, "quit") == 0 || strcmp(murderItemGuess, "quit") == 0) {
                    printf("Exited");
                    looping = false;
                } else {
                    printf("Please Retype Inputs:\n");
                }
            }
        } else if (strncmp(input, "help", 20) == 0) {
            help();
        } else {
            printf("Please Re-type");
        }
    }

    //Freeing allocated memory
    free(itemHead);
    free(roomHead);
    free(player);
    free(charHead);
    return 0;
}