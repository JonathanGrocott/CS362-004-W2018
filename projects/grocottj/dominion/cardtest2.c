/******************************************************************************
 * Author: Jonathan Grocott
 * Description: Unit tests for the adventurer cardEffect function in dominion.c. 
 * File Name: cardtest2.c
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
	int i = 0,						// iteration variable for loop counting
		numPlayers = 2,				// number of players in game
		randomSeed = 10000,			// seed for random generation
		validationCheck = 1,		// used to determine pass or fail
		cardDrawn = 0,				// card selected from deck
		count = 0,					// number of cards removed from player deck
		drawntreasure = 0;			// determines number of cards drawn
	int failure = 0; 
	
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	memcpy(&stateOriginal, &state, sizeof(struct gameState));


	
	printf("\n-----------------------------------------");
    printf("\n--------Testing adventurerCall()----------\n\n");
	printf("\n----Test #1: Non-treasure cards are successfully added to the discard pile----\n");
	
	
	//Refactored for cardtest2
	adventurerCall(0, 0, 0, 0, &state, 0, 0);

	
	validationCheck = 1;
	while (drawntreasure < 2) {
		cardDrawn = stateOriginal.deck[state.whoseTurn][stateOriginal.deckCount[state.whoseTurn] - 1];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
			drawntreasure++;
			count++;
		} else {
			count++;
		}
	}
	if (state.discardCount[state.whoseTurn] != stateOriginal.discardCount[state.whoseTurn] + (count - 2)){
		failure++;
		validationCheck = 0;
	}
	printTestResult(validationCheck, 1, 1);

	printf("\n----Test #2: Two additional treasure cards are added to the player's hand----\n");
	validationCheck = 1;
	if (state.handCount[state.whoseTurn] != state.handCount[state.whoseTurn] + 2){
		validationCheck = 0;
		failure++;
	}
	if (!(state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] == copper ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] == silver ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] == gold)) {
		validationCheck = 0;
		failure++;
	}
	if (!(state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 2] == copper ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 2] == silver ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 2] == gold)) {
		validationCheck = 0;
		failure++;
	}
	printTestResult(validationCheck, 2, 0);

	printf("\n----Test #3: Other Player's cards are not modified----\n");
	validationCheck = 1;
	if (isDeckSame(&state, &stateOriginal, state.whoseTurn + 1) != 1){
		validationCheck = 0;
		failure++;
	}
	if (isHandSame(&state, &stateOriginal, state.whoseTurn + 1) != 1){
		validationCheck = 0;
		failure++;
	}
	if (isDiscardSame(&state, &stateOriginal, state.whoseTurn + 1) != 1){
		validationCheck = 0;
		failure++;
	}
	printTestResult(validationCheck, 1, 1);

	printf("\n----Test #4: Game state supply count is not modified----\n");
	validationCheck = 1;
	for (i = 0; i < 28; i++) {
		if (state.supplyCount[i] != stateOriginal.supplyCount[i])
		validationCheck = 0;
		//failure++;
	}
	if(validationCheck == 0){
		failure++;
	}
	printTestResult(validationCheck, 1, 1);
	
	if(failure == 0){
		printf("\n\n\n >>>>>>ALL TESTS PASSED: adventurerCall() \n\n\n");
	}
	else{
		printf("\n\n\n >>>>>>FAILURES IN ADVENTURER: %d \n\n\n", failure);
	}
	
	return 0;
}