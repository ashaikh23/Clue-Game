#ifndef PROJECT1_ITEMS_H
#define PROJECT1_ITEMS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define numItems 6

char *itemNames[6];
const char *regularItemAttributes[6];

struct Item {
    char *name;
    char *attribute;
    bool isMurderItem;

    //Linked List Functionality
    struct Item *next;
};

void shuffleItemIndexes();

struct Item *getItem(struct Item *itemHead, int rand);

struct Item *insertItem(struct Item *head, int pos, struct Item *newItem);

struct Item *removeItem(struct Item *head, char *input);

#endif //PROJECT1_ITEMS_H