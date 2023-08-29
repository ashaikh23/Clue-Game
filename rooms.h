#ifndef CLUEGAME_ROOMS_H
#define CLUEGAME_ROOMS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define numRooms 9

char *roomNames[9];

struct Room {
    char *name;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    bool isMurderRoom;
    bool isBloody;

    //Room Inventory(ONLY ONE ITEM AT A TIME)
    struct Item *itemListHead;

    //Character Inventory(ONLY ONE CHARACTER AT A TIME)
    struct Character *characterListHead;

    //Linked List Functionality
    struct Room *next;
};

struct Room *setRoomPointers(struct Room *roomHead, struct Room *resultRoom);

void shuffleRoomIndexes();

struct Room *spawnItems(struct Room *roomHead, struct Item *itemHead);

struct Room *spawnCharacters(struct Room *roomHead, struct Character *charHead);

struct Room *setMurderRoom(struct Room *roomHead, int rand);

struct Room *getRoom(struct Room *roomHead, int rand);

struct Room *insertRoom(struct Room *head, int pos, struct Room *newRoom);

struct Room *removeRoom(struct Room *head, char *input);

#endif //CLUEGAME_ROOMS_H
