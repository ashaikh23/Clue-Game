#ifndef PROJECT1_CHARACTERS_H
#define PROJECT1_CHARACTERS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define numCharacters 5

char *characterNames[5];
char *murderItemAttributes[5];


struct Character {
    char *name;
    bool isMurderer;

    //Linked List Functionality
    struct Character *next;
};

void shuffleCharacterIndexes();

struct Character *insertCharacter(struct Character *head, int pos, struct Character *newCharacter);

struct Character *removeCharacter(struct Character *head, char *input);

struct Character *getCharacter(struct Character *charHead, int rand);

#endif //PROJECT1_CHARACTERS_H