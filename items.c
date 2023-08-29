#include <stdlib.h>
#include "items.h"
#include <time.h>

char *itemNames[6] = {"Rope", "Knife", "Shovel", "Pipe", "Lighter", "Pencil"};

const char *regularItemAttributes[6] = {"Item is rather clean", "Item covered in dust!", "Item is shiny clean!",
                                        "Item looks broken!", "Item feels sticky!",
                                        "Item was tucked in the corner of the room!"};

//Shuffling itemNames array
void shuffleItemIndexes() {
    srand(time(NULL));
    for (int i = 0; i < numItems; i++) {
        int index1 = rand() % numItems;
        int index2 = rand() % numItems;
        char *temp = itemNames[index1];
        itemNames[index1] = itemNames[index2];
        itemNames[index2] = temp;
    }
}

//get Item at position rand
struct Item *getItem(struct Item *itemHead, int rand) {
    for (int i = 0; i < rand; i++) {
        itemHead = itemHead->next;
    }
    return itemHead;
}

struct Item *insertItem(struct Item *head, int pos, struct Item *newItem) {
    //BASE CASE
    if (head == NULL || pos == 0) {
        //set newRoom to next
        newItem->next = head;
        head = newItem;
    } else {
        head->next = insertItem(head->next, pos - 1, newItem);
    }

    return head;
}

struct Item *removeItem(struct Item *head, char *input) {
    if (head != NULL && head->name == input) {
        if (head->next != NULL) {
            head = head->next;
        } else {
            head = NULL;
        }
    } else {
        head->next = removeItem(head->next, input);
    }

    return head;
}