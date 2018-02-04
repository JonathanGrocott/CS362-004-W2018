#ifndef _testTools_H
#define _testTools_H

#include "dominion.h"

#define CARD_NAME_LENGTH 20

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

int fakeAssert(char condition[], int result);

int containsCard(int card, int *array, int arrayCount);
int compareState(
  struct gameState *state1,
  struct gameState *state2,
  struct gameStateComparison *results
);


#endif