#include <stdlib.h>
#include "rooms.h"
#include <time.h>
#include "items.h"
#include "characters.h"

char *roomNames[9] = {"Kitchen", "Study", "Greenhouse", "Garage", "Bedroom", "Smokeroom",
                      "Office", "Bathroom", "Dining Room"};

//Shuffling roomNames array
void shuffleRoomIndexes() {
    srand(time(NULL));
    for (int i = 0; i < numRooms; i++) {
        int index1 = rand() % 9;
        int index2 = rand() % 9;
        char *temp = roomNames[index1];
        roomNames[index1] = roomNames[index2];
        roomNames[index2] = temp;
    }
}

struct Room *insertRoom(struct Room *head, int pos, struct Room *newRoom) {
    //BASE CASE
    if (head == NULL || pos == 0) {
        //set newRoom to next
        newRoom->next = head;
        head = newRoom;
    } else {
        head->next = insertRoom(head->next, pos - 1, newRoom);
    }

    return head;
}

struct Room *removeRoom(struct Room *head, char *input) {
    //BASE CASE
    if (head != NULL || head->name == input) {
        //set newRoom to next
        if (head->next != NULL) {
            head = head->next;
        } else {
            head = NULL;
        }
    } else {
        head->next = removeRoom(head->next, input);
    }

    return head;
}

//spawning items into the game randomly
struct Room *spawnItems(struct Room *roomHead, struct Item *itemHead) {
    srand(time(NULL));
    int randRoomIndex = rand() % numRooms;
    int i = 0;
    while (i < numItems) {
        randRoomIndex = rand() % numRooms;
        if (getRoom(roomHead, rand() % numRooms) != NULL && getRoom(roomHead, randRoomIndex)->itemListHead == NULL) {
            getRoom(roomHead, randRoomIndex)->itemListHead = (struct Item *) malloc
                    (sizeof(struct Item));
            getRoom(roomHead, randRoomIndex)->itemListHead->name = getItem(itemHead, i)->name;
            getRoom(roomHead, randRoomIndex)->itemListHead->attribute = getItem(itemHead, i)->attribute;
            getRoom(roomHead, randRoomIndex)->itemListHead->isMurderItem = getItem(itemHead, i)->isMurderItem;
            i++;
        }
    }
    return roomHead;
}

//spawning Characters into the game randomly
struct Room *spawnCharacters(struct Room *roomHead, struct Character *charHead) {
    srand(time(NULL));
    int randCharIndex = rand() % numRooms;
    int i = 0;
    while (i < numCharacters) {
        //CASE FOR OVERLAPPING ROOMS
        randCharIndex = rand() % numRooms;
        if (getRoom(roomHead, randCharIndex) != NULL && getRoom(roomHead, randCharIndex)->characterListHead == NULL) {
            getRoom(roomHead, randCharIndex)->characterListHead = (struct Character *) malloc
                    (sizeof(struct Character));
            getRoom(roomHead, randCharIndex)->characterListHead->name = getCharacter(charHead, i)->name;
            i++;
        }
    }
    return roomHead;
}

//Setting murderRoom based on random index provided
struct Room *setMurderRoom(struct Room *roomHead, int rand) {
    for (int i = 0; i < rand; i++) {
        roomHead = roomHead->next;
    }
    return roomHead;
}

//get room at index rand
struct Room *getRoom(struct Room *roomHead, int rand) {
    for (int i = 0; i < rand; i++) {
        roomHead = roomHead->next;
    }
    return roomHead;
}

//Setting room pointers statically
struct Room *setRoomPointers(struct Room *roomThead, struct Room *resultRoom) {
    struct Room refRoom = *roomThead;
    resultRoom = roomThead;

    //room 0 Top-Left
    roomThead->north = NULL;
    roomThead->south = refRoom.next->next->next;
    roomThead->east = refRoom.next;
    roomThead->west = NULL;

    roomThead = roomThead->next;
    //room 1 Top-Middle
    roomThead->north = NULL;
    roomThead->south = refRoom.next->next->next->next;
    roomThead->east = refRoom.next->next;
    roomThead->west = resultRoom; //address

    roomThead = roomThead->next;
    //room 2 Top-Right
    roomThead->north = NULL;
    roomThead->south = refRoom.next->next->next->next->next;
    roomThead->east = NULL;
    roomThead->west = refRoom.next;

    roomThead = roomThead->next;
    //room 3 Middle-Left
    roomThead->north = resultRoom;//address
    roomThead->south = refRoom.next->next->next->next->next->next;
    roomThead->east = refRoom.next->next->next->next;
    roomThead->west = NULL;

    roomThead = roomThead->next;
    //room 4 Middle-Middle
    roomThead->north = refRoom.next;
    roomThead->south = refRoom.next->next->next->next->next->next->next;
    roomThead->east = refRoom.next->next->next->next->next;
    roomThead->west = refRoom.next->next->next;

    roomThead = roomThead->next;
    //room 5 Middle-Right
    roomThead->north = refRoom.next->next;
    roomThead->south = refRoom.next->next->next->next->next->next->next->next;
    roomThead->east = NULL;
    roomThead->west = refRoom.next->next->next->next;

    roomThead = roomThead->next;
    //room 6 Bottom-Left
    roomThead->north = refRoom.next->next->next;
    roomThead->south = NULL;
    roomThead->east = refRoom.next->next->next->next->next->next->next;
    roomThead->west = NULL;

    roomThead = roomThead->next;
    //room 7 Bottom-Middle
    roomThead->north = refRoom.next->next->next->next;
    roomThead->south = NULL;
    roomThead->east = refRoom.next->next->next->next->next->next->next->next;
    roomThead->west = refRoom.next->next->next->next->next->next;

    roomThead = roomThead->next;
    //room 8 Bottom-Right
    roomThead->north = refRoom.next->next->next->next->next;
    roomThead->south = NULL;
    roomThead->east = NULL;
    roomThead->west = refRoom.next->next->next->next->next->next->next;

    return resultRoom;
}