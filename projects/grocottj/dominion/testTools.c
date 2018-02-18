#include <stdio.h>
#include <math.h>
#include <string.h>
#include "testTools.h"
#include "dominion.h"

 //Set global vars 
#define NUMTESTS 10000
#define MINCARDS 3

void engine_testSmithy(struct gameState *pre, struct errors *e) {

    int handPosition;  
    int choice1, choice2, choice3;  
    int bonus;  

    // test variables
    int playerNumber = pre->whoseTurn;
    struct gameState post;
    int i;

    handPosition = randInt(0, pre->handCount[playerNumber]);
    pre->hand[playerNumber][handPosition] = smithy;

    memcpy(&post, pre, sizeof(struct gameState));

    bonus = randInt(0, MAX_DECK);
    choice1 = randInt(curse, treasure_map);
    choice2 = randInt(curse, treasure_map);
    choice3 = randInt(curse, treasure_map);

	//Call card effect with smithy and randoms
    cardEffect(smithy, choice1, choice2, choice3, &post, handPosition, &bonus); 


	//Testing that post played hand should increment +1
    if (pre->playedCardCount + 1 != post.playedCardCount){
		e->metric1++;
		#if (NOISY_TEST == 1)
			printf("TEST FAILED: Player hand not incremented by 1.\n");
        #endif
	}
	
	//Testing that post played hand count incremented +2
    if (pre->handCount[playerNumber] + 2 != post.handCount[playerNumber]){
		e->metric2++;
		#if (NOISY_TEST == 1)
			printf("TEST FAILED: Post played hand count not +2.\n");
        #endif
	}

	//Testing that post played deck decremented by 3
    if (pre->deckCount[playerNumber] - 3 != post.deckCount[playerNumber]){
		e->metric3++;
		#if (NOISY_TEST == 1)
			printf("TEST FAILED: Post played deck not -3.\n");
        #endif
	}
	
    //Test that opponent card count is unchanged
    for (i = 0; i < pre->numPlayers; i++) {
		if (i == playerNumber) continue;
		else {
			if (pre->deckCount[i] != post.deckCount[i] || pre->handCount[i] != post.handCount[i] || pre->discardCount[i] != post.discardCount[i]){
				e->metric4++; 
				#if (NOISY_TEST == 1)
					printf("TEST FAILED: Opponent card count changed.\n");
				#endif
			}			
		}
    }
}

void randomizeGameState(struct gameState *state) {
    
	int numPlayers = randInt(2, MAX_PLAYERS); // range 0 - MAX_PLAYERS
    int playerNumber = randInt(0, numPlayers);  // range 0 - numPlayers
    int i;
	
    // assign randoms, from the class lecture
    for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)state)[i] = floor(Random() * 256);
    }

    // assign reasonable values
    state->deckCount[playerNumber] = randInt(MINCARDS, MAX_DECK);
    state->discardCount[playerNumber] = randInt(0, MAX_DECK - state->deckCount[playerNumber]);
    state->handCount[playerNumber] = randInt(0, MAX_DECK - state->deckCount[playerNumber] - state->discardCount[playerNumber]);
    state->playedCardCount = 0; 
    state->numPlayers = numPlayers;
    state->whoseTurn = playerNumber;

    // assign random cards to deck, discard pile, and hand
    for (i = 0; i < state->deckCount[playerNumber]; i++)
	state->deck[playerNumber][i] = randInt(curse, treasure_map);
    for (i = 0; i < state->discardCount[playerNumber]; i++)
	state->discard[playerNumber][i] = randInt(curse, treasure_map);
    for (i = 0; i < state->handCount[playerNumber]; i++)
	state->hand[playerNumber][i] = randInt(curse, treasure_map);
}

//Returns a random int between two #'s
int randInt(int low, int high) {
    double r = rand();
    return (int)(low + r * (high - low) / (double)RAND_MAX);
}


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

