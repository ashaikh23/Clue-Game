#ifndef CLUEGAME_PLAYER_H
#define CLUEGAME_PLAYER_H

struct Player {
    int guesses;
    struct Room *curRoom;
    struct Item *itemList;
    struct Character *charList;
};

void look(struct Player *player);

void go(struct Player *player, char *input);

struct Player *takeItem(struct Player *player, char *input, struct Room *roomHead);

struct Player *dropItem(struct Player *player, char *input, struct Item *itemHead);

void listInventory(struct Player *player);

void list();

void help();

struct Player *clue(struct Player *player, char *itemInput, char *charInput, struct Room *room);

void guess();

#endif //CLUEGAME_PLAYER_H