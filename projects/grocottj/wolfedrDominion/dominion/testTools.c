#include <stdio.h>
#include <string.h>
#include "testTools.h"
#include "dominion.h"

int containsCard(int card, int array[], int arrayCount) {
  int i = 0;

  for (i = 0; i < arrayCount; i++) {
    if (array[i] == card) {
      /* Return 1 (found) if the card exists in the location */
      return 1;
    }
  }

  return 0;   
}

int isDiscardSame(struct gameState *state, struct gameState *stateOriginal, int player) {
	int i = 0;
	for (i = 0; i < stateOriginal->discardCount[player]; i++) {
		if (stateOriginal->discard[player][i] != state->discard[player][i])
			return 0;
	}

	return 1;
}

int isHandSame(struct gameState *state, struct gameState *stateOriginal, int player) {
	int i = 0;
	for (i = 0; i < stateOriginal->handCount[player]; i++) {
		if (stateOriginal->hand[player][i] != state->hand[player][i])
			return 0;
	}

	return 1;
}

int isDeckSame(struct gameState *state, struct gameState *stateOriginal, int player) {
	int i = 0;
	for (i = 0; i < stateOriginal->deckCount[player]; i++) {
		if (stateOriginal->deck[player][i] != state->deck[player][i])
			return 0;
	}

	return 1;
}

void printTestResult(int validationCheck, int expected, int actual) {
	if (validationCheck == 1)
		printf("SUCCESS: ");
	else
		printf("FAIL: ");
	if (expected != -1) {
		printf("Expected value: %i,  ", expected);
		printf("Actual value: %i\n", actual);
	}
}

int fakeAssert(char condition[], int result) {

  if (result) {
    printf("SUCCESS: %s\n", condition);
    return 1;
  } else {
    printf("FAIL: %s\n", condition);
    return 0;
  }
}


int compareState(
  struct gameState *a,
  struct gameState *b,
  struct gameStateComparison *gsc
) {
  int i = 0, j = 0;
  int changed = 0;

  /* Compare all the gameState members and assign the result to the matching
     gameStateComparison member */
  gsc->numPlayers = (a->numPlayers == b->numPlayers) ? 0 : 1;

  for (i = 0; i < treasure_map+1; i++) {
    gsc->supplyCount[i] = (a->supplyCount[i] == b->supplyCount[i]) ? 0 : 1;

    changed = changed || gsc->supplyCount[i];
  }

  for (i = 0; i < treasure_map+1; i++) {
    gsc->embargoTokens[i] =
      (a->embargoTokens[i] == b->embargoTokens[i]) ? 0 : 1;

    changed = changed || gsc->embargoTokens[i];
  }

  gsc->outpostPlayed = (a->outpostPlayed == b->outpostPlayed) ? 0 : 1;
  gsc->outpostTurn = (a->outpostTurn == b->outpostTurn) ? 0 : 1;
  gsc->whoseTurn = (a->whoseTurn == b->whoseTurn) ? 0 : 1;
  gsc->phase = (a->phase == b->phase) ? 0 : 1;
  gsc->numActions = (a->numActions == b->numActions) ? 0 : 1;
  gsc->coins = (a->coins == b->coins) ? 0 : 1;
  gsc->numBuys = (a->numBuys == b->numBuys) ? 0 : 1;

  for (i = 0; i < MAX_PLAYERS; i++) {
    for (j = 0; j < MAX_HAND; j++) {
      if (a->hand[i][j] == b->hand[i][j]) {
        gsc->hand[i][j] = 0;
      } else {
        gsc->hand[i][j] = 1;
        gsc->handChanged[i] = 1;
      }

      changed = changed || gsc->hand[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    for (j = 0; j < MAX_DECK; j++) {
      if (a->deck[i][j] == b->deck[i][j]) {
        gsc->deck[i][j] = 0;
      } else {
        gsc->deck[i][j] = 1;
        gsc->deckChanged[i] = 1;
      }

      if (a->discard[i][j] == b->discard[i][j]) {
        gsc->discard[i][j] = 0;
      } else {
        gsc->discard[i][j] = 1;
        gsc->discardChanged[i] = 1;
      }

      changed = changed || gsc->deck[i][j] || gsc->deckChanged[i]
        || gsc->discard[i][j] || gsc->discardChanged[i];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    gsc->handCount[i] = (a->handCount[i] == b->handCount[i]) ? 0 : 1;
    gsc->deckCount[i] = (a->deckCount[i] == b->deckCount[i]) ? 0 : 1;
    gsc->discardCount[i] = (a->discardCount[i] == b->discardCount[i]) ? 0 : 1;

    changed = changed || gsc->handCount[i] || gsc->deckCount[i]
      || gsc->discardCount[i];
  }

  for (i = 0; i < MAX_DECK; i++) {
    gsc->playedCards[i] = (a->playedCards[i] == b->playedCards[i]) ? 0 : 1;

    changed = changed || gsc->playedCards[i];
  }

  gsc->playedCardCount = (a->playedCardCount == b->playedCardCount) ? 0 : 1;

  /* Do one change calculation for all the non-looping members */
  changed = changed || gsc->numPlayers || gsc->outpostPlayed
    || gsc->outpostTurn || gsc->whoseTurn || gsc->phase || gsc->numActions
    || gsc->coins || gsc->numBuys || gsc->playedCardCount;

  /* Return the overall status of whether anything changed */
  return changed;
}

