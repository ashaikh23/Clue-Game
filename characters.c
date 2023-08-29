#include <stdlib.h>
#include "characters.h"
#include <time.h>

char *characterNames[5] = {"Cook", "Maid", "Smoker", "Gardener", "Mechanic"};

char *murderItemAttributes[5] = {"Item feels greasy", "Item looks like its been cleaned recently",
                                 "Item has lots of ash on it", "item has lots of dirt on it",
                                 "item has lots of black grease on it!"};

//Shuffling itemNames array and setting murderItemAttributes to each character
void shuffleCharacterIndexes() {
    srand(time(NULL));
    for (int i = 0; i < numCharacters; i++) {
        int index1 = rand() % numCharacters;
        int index2 = rand() % numCharacters;
        char *temp = characterNames[index1];
        char *tempAttribute = murderItemAttributes[index1];
        characterNames[index1] = characterNames[index2];
        characterNames[index2] = temp;
        murderItemAttributes[index1] = murderItemAttributes[index2];
        murderItemAttributes[index2] = tempAttribute;
    }
}

struct Character *insertCharacter(struct Character *head, int pos, struct Character *newCharacter) {
    //BASE CASE
    if (head == NULL || pos == 0) {
        //set newRoom to next
        newCharacter->next = head;
        head = newCharacter;
    } else {
        head->next = insertCharacter(head->next, pos - 1, newCharacter);
    }

    return head;
}

struct Character *removeCharacter(struct Character *head, char *input) {
    //BASE CASE
    if (head != NULL || head->name == input) {
        if (head->next != NULL) {
            head = head->next;
        } else {
            head = NULL;
        }
    } else {
        head->next = removeCharacter(head->next, input);
    }
    return head;
}

//setting murder character
struct Character *getCharacter(struct Character *charHead, int rand) {
    for (int i = 0; i < rand; i++) {
        charHead = charHead->next;
    }
    return charHead;
}