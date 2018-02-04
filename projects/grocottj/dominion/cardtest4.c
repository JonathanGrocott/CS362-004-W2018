/******************************************************************************
 * Author: Jonathan Grocott
 * Description: Unit tests for the mineCall function in dominion.c.
	 * Trash a treasure card for a treasure card costing up to 3 coins more.
	 * The new treasure card should be added to the player's hand.
	 * Move the played card to the playedCards pile. 
 * File Name: cardtest4.c
 * Date Created: 2/3/2018
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "testTools.c"

#define P1 0
#define P2 1
#define HANDPOS 0
#define COPPERPOS 1
#define COPPER2POS 2
#define BARONPOS 3
#define ESTATEPOS 4

int testMine() {
  int passCount = 0;
  int testCount = 0;
  int failure = 0; 
  int result = 0;
  struct gameState initialState = {0};
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};

  printf("\n-----------------------------------------");
  printf("\n--------Testing mineCall()----------\n\n");

  /* Set up a custom game state */
  state.whoseTurn = P1;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = silver;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = cutpurse;
  state.deckCount[P1] = 5;
  state.hand[P1][0] = mine;
  state.hand[P1][1] = copper;
  state.hand[P1][2] = copper;
  state.hand[P1][3] = baron;
  state.hand[P1][4] = estate;
  state.handCount[P1] = 5;
  state.discardCount[P1] = 0;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  state.supplyCount[silver] = 10;
  memcpy(&initialState, &state, sizeof(struct gameState));

  /* Test using a non-treasure card for choice1 */
  printf("\n----Test #1: choice1 = estate, choice2 = silver----\n");
  memcpy(&preState, &state, sizeof(struct gameState));
  
  //refactored
  result = mineCall(0, ESTATEPOS, silver, 0, &state, HANDPOS, 0);
  

  /* Should not make any changes when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't treasure (< copper)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't treasure (< copper)",
    (result == -1)
  );

  /* Test using a non-treasure card for choice1 */
  printf("\n----Test #2: choice1 = baron, choice2 = silver----\n");
  memcpy(&preState, &state, sizeof(struct gameState));
  

	result = mineCall(0, BARONPOS, silver, 0, &state, HANDPOS, 0);
  
  /* Should not make any changes when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't treasure (> gold)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't treasure (> gold)",
    (result == -1)
  );

  /* Test using a treasure card for choice 1 and a non-card for choice2 */
  printf("\n----Test #3: choice1 = copper, choice2 = treasure_map + 999----\n");
  memcpy(&initialState, &state, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  

	result = mineCall(0, COPPERPOS, treasure_map+999, 0, &state, HANDPOS, 0);
  
  /* Should not make any changes when choice1 isn't a real card */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't a card (> treasure_map)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't a card (> treasure_map)",
    (result == -1)
  );

  /* Test using a treasure card for choice 1 and a non-card for choice2 */
  printf("\n----Test #4: choice1 = copper, choice2 = curse - 999----\n");
  memcpy(&initialState, &state, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  

	result = mineCall(0, COPPERPOS, curse-999, 0, &state, HANDPOS, 0);
  
  /* Should not make any changes when choice1 isn't a real card */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice1 isn't a card (< curse)",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice1 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice1 isn't a card (< curse)",
    (result == -1)
  );

  /* Test using a treasure card for choice1 and a non-treasure card for
     choice 2 */
  printf("\n----Test #5: choice1 = copper, choice2 = estate----\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  
	result = mineCall(0, COPPERPOS, estate, 0, &state, HANDPOS, 0);
  
  /* Should not make any changes when choice2 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice2 isn't treasure",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice2 isn't treasure */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice2 isn't treasure",
    (result == -1)
  );

  /* Test using a treasure card for choice1 and a treasure card that's more
     than 3 coins more expensive */
  printf("\n----Test #6: choice1 = copper, choice2 = gold----\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  

	result = mineCall(0, COPPERPOS, gold, 0, &state, HANDPOS, 0);
  
  /* Should not make any changes when choice2 is too costly */
  testCount += 1;
  passCount += fakeAssert(
    "Should not change state when choice2 is too costly",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Should return -1 when choice2 is too costly */
  testCount += 1;
  passCount += fakeAssert(
    "Should return -1 when choice2 is too costly",
    (result == -1)
  );

  /* Test using a treasure card for choice1 and a treasure card that's up to
     3 coins more (silver) */
  printf("\n----Test #7: choice1 = copper, choice2 = silver----\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  memcpy(&preState, &state, sizeof(struct gameState));
  
	result = mineCall(0, COPPERPOS, silver, 0, &state, HANDPOS, 0);
  compareState(&state, &preState, &gsc);

  /* Should add choice2 card to hand */
  testCount += 1;
  passCount += fakeAssert(
    "Should add choice2 card to hand",
    (containsCard(silver, state.hand[P1], state.handCount[P1]))
  );

  /* Should trash choice1 card */
  testCount += 1;
  passCount += fakeAssert(
    "Should trash choice1 card",
    (state.hand[P1][COPPERPOS] != copper
    && !containsCard(copper, state.deck[P1], state.deckCount[P1])
    && !containsCard(copper, state.discard[P1], state.discardCount[P1])
    && !containsCard(copper, state.playedCards, state.playedCardCount))
  );

  /* Should only trash ONE instance of choice1 card */
  testCount += 1;
  passCount += fakeAssert(
    "Should only affect one instance of choice1 card",
    (state.hand[P1][COPPER2POS] == copper)
  );

  /* Should not affect other players */
  testCount += 1;
  passCount += fakeAssert(
    "Should not affect other players",
    (gsc.handChanged[P2] == 0
    && gsc.deckChanged[P2] == 0
    && gsc.discardChanged[P2] == 0
    && state.handCount[P2] == preState.handCount[P2]
    && state.deckCount[P2] == preState.deckCount[P2]
    && state.discardCount[P2] == preState.discardCount[P2])
  );

  /* Should move played card to playedCards */
  testCount += 1;
  passCount += fakeAssert(
    "Should move played card to playedCards",
    (!containsCard(mine, state.hand[P1], state.handCount[P1])
    && containsCard(mine, state.playedCards, state.playedCardCount))
  );


  failure = testCount-passCount;
  
  if(passCount==testCount){
		printf("\n\n\n >>>>>>ALL TESTS PASSED: mineCall() \n\n\n");
	}
	else{
		printf("\n\n\n >>>>>>FAILURES IN MINE: %d \n\n\n", failure);
	}

  return 0;
}

int main() {
  testMine();
  return 0;
}