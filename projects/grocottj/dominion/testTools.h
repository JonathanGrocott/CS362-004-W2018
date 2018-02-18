#ifndef _testTools_H
#define _testTools_H

#include "dominion.h"

#define CARD_NAME_LENGTH 20

/* This struct is a modification of gameState which basically adds additional
   members for keeping track of overall changes for two-dimensional arrays
   (e.g. handChanged[] for hand[][]). The values in gameStateComparison
   indicate change status (0 for unchanged or 1 for changed). */
struct gameStateComparison {
  int numPlayers;
  int supplyCount[treasure_map+1];
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions;
  int coins;
  int numBuys;
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int handChanged[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int deckChanged[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int discardChanged[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};

//struct to keep errors 
struct errors {
    int metric1;
    int metric2;
    int metric3;
    int metric4;
    int metric5;
};

//Random testing functions
void engine_testSmithy(struct gameState *pre, struct errors *e);
void randomizeGameState(struct gameState *state);
int randInt(int low, int high);


int fakeAssert(char condition[], int result);
void printTestResults(int passCount, int testCount);
int containsCard(int card, int *array, int arrayCount);
int handIndex(int card, int *array, int arrayCount);
int isTreasureCard(int card);
int treasureCardsInHand(int player, struct gameState *state);
int compareState(
  struct gameState *state1,
  struct gameState *state2,
  struct gameStateComparison *results
);
void printIntArray(int *array, int arrayCount);
void enumToCardName(int card, char *name, int nameLength);
void printGameState(struct gameState *state);

#endif