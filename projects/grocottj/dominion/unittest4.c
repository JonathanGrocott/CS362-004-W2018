/******************************************************************************
 * Author: Jonathan Grocott
 * Description: updateCoins function unit tests in dominion.c. 
 * Date Created: 1/29/2018
 *****************************************************************************/
 
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include "testTools.c"

int main() {
	struct gameState state,	stateOriginal;	// backup copy of game to detect changes
	int i = 0,						
		numPlayers = 2,				// number of players in game
		randomSeed = 1000,			// seed for random generation
		validationCheck = 1;		// used to determine pass or fail
	int failure = 0; 
	
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);


	for (i = 0; i < 5; i++) {
		state.hand[state.whoseTurn][i] = copper;
	}
	updateCoins(state.whoseTurn, &state, 0);

	// DISPLAY
	printf("\n\n-----------------------------------------");
    printf("\n--------Testing updateCoins()----------\n\n");

	printf("----Test #1: Placed five copper cards in player hand, should be 5----\n");
	validationCheck = 1;
	if (state.coins != 5){
		failure = 1; 
		validationCheck = 0;
	}
	printTestResult(validationCheck, 5, 5);

	printf("\n----Test #2: Placed six silver cards in player hand, set handCount to 6, should be 12---\n");
	validationCheck = 1;
	for (i = 0; i < 6; i++) {
		state.hand[state.whoseTurn][i] = silver;
	}
	state.handCount[state.whoseTurn] = 6;
	updateCoins(state.whoseTurn, &state, 0);
	if (state.coins != 12){
		failure = 1; 
		validationCheck = 0;
	}
	printTestResult(validationCheck, 12, 12);

	printf("\n----Test #3: Copper, 2 Silver, 2 Gold, set handCount to 5, should be 11----\n");
	validationCheck = 1;
	state.handCount[state.whoseTurn] = 5;
	state.hand[state.whoseTurn][0] = copper;
	state.hand[state.whoseTurn][1] = silver;
	state.hand[state.whoseTurn][2] = silver;
	state.hand[state.whoseTurn][3] = gold;
	state.hand[state.whoseTurn][4] = gold;
	updateCoins(state.whoseTurn, &state, 0);
	if (state.coins != 11){
		failure = 1; 
		validationCheck = 0;
	}
	printTestResult(validationCheck, 11, 11);

	printf("\n----Test #4: Setting hand count to 4, should only read value of top 4 cards = 8----\n");
	validationCheck = 1;
	state.handCount[state.whoseTurn] = 4;
	updateCoins(state.whoseTurn, &state, 0);
	if (state.coins != 8){
		failure = 1; 
		validationCheck = 0;
	}
	printTestResult(validationCheck, 8, 8);
	
	printf("\n----Test #5: Including bonus of 5, should result in 8 + 5 = 13----\n");
	validationCheck = 1;
	updateCoins(state.whoseTurn, &state, 5);
	if (state.coins != 13){
		failure = 1; 
		validationCheck = 0;
	}
	printTestResult(validationCheck, 13, 13);
	
	printf("\n----Test #6: updateCoins only accesses cards, card piles should be unchanged----\n");
	validationCheck = 1;
	if (isHandSame(&state, &stateOriginal, 0) != 1){
		failure = 1; 
		validationCheck = 0;
	}
	if (isHandSame(&state, &stateOriginal, 0) != 1){
		failure = 1; 
		validationCheck = 0;
	}
	if (isDeckSame(&state, &stateOriginal, 0) != 1){
		failure = 1; 
		validationCheck = 0;
	}
	if (isDeckSame(&state, &stateOriginal, 0) != 1){
		failure = 1; 
		validationCheck = 0;
	}
	if (isDiscardSame(&state, &stateOriginal, 0) != 1){
		failure = 1; 
		validationCheck = 0;
	}
	if (isDiscardSame(&state, &stateOriginal, 0) != 1){
		failure = 1; 
		validationCheck = 0;
	}
	printTestResult(validationCheck, 1, 1);

	if(failure != 1){
		printf("\n\n\n >>>>>>ALL TESTS PASSED: updateCoins() \n\n\n");
	}
	
	
	return 0;
}