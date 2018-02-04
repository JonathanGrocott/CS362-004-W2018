/******************************************************************************
 * Author: Jonathan Grocott
 * Description: Unit tests for the smithy cardEffect function in dominion.c. 
 * File Name: cardtest1.c
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
	int i = 0, j = 0,						// iteration variable for loop counting
		numPlayers = 2,				// number of players in game
		randomSeed = 10000,			// seed for random generation
		validationCheck = 1,		// used to determine P/F
		found = 0;					// detects if card found in deck
		
		int failure = 0; 
	// Setup initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	state.hand[state.whoseTurn][0] = smithy;
	memcpy(&stateOriginal, &state, sizeof(struct gameState));

	// DISPLAY
	printf("\n-----------------------------------------");
    printf("\n--------Testing smithyCall()----------\n\n");
	printf("\n----Test #1: 3 valid cards added to current player hand----\n");
	
	//Refactored for cardtest1
	smithyCall(&state, 0);
	
	validationCheck = 1;
	for (i = 0; i < state.handCount[state.whoseTurn]; i++) {
		if (state.hand[state.whoseTurn][i] != stateOriginal.hand[state.whoseTurn][i]) {
			if (state.hand[state.whoseTurn][i] == -1) {
				validationCheck = 0;
				failure++; 
			}
		}
	}
	// Ensure top card is valid selection
	if (state.hand[state.whoseTurn][stateOriginal.handCount[state.whoseTurn] + 1] == -1){
		validationCheck = 0;
		failure++;
	}
	// Ensure card after top card is -1
	if (state.hand[state.whoseTurn][stateOriginal.handCount[state.whoseTurn] + 2] != -1){
		validationCheck = 0;
		failure++;
	}
	printTestResult(validationCheck, 3, 4);

	printf("\n----Test #2: Current player hand count changed: 3 draws - 1 discard = 2----\n");
	validationCheck = 0;
	if (state.handCount[state.whoseTurn] != stateOriginal.handCount[state.whoseTurn] + 2){
		validationCheck = 0;
		failure++;
	}
	printTestResult(validationCheck, 2, 3);

	printf("\n----Test #3: The smithy card is properly removed from the player hand----\n");
	validationCheck = 1;
	if (state.hand[state.whoseTurn][0] == smithy){
		validationCheck = 0;
		failure++;
	}
	printTestResult(validationCheck, 1, 0);
	
	printf("\n----Test #4: 3 cards	came from player's deck----\n");
	validationCheck = 1;
	for (i = 0; i < state.handCount[state.whoseTurn]; i++) {
		if (state.hand[state.whoseTurn][i] != stateOriginal.hand[state.whoseTurn][i]) {
			found = 0;
			for (j = 0; j < stateOriginal.deckCount[state.whoseTurn]; j++) {
				if (state.hand[state.whoseTurn][i] == stateOriginal.deck[state.whoseTurn][j]) {
					found = 1;
				}
			}
			if (found == 0){
				validationCheck = 0;
				failure++;
			}
		}
	}
	printTestResult(validationCheck, 1, 0);

	printf("\n----Test #5: Player 2's decks were not modified----\n");
	validationCheck = 1;
	if (isHandSame(&state, &stateOriginal, state.whoseTurn + 1) != 1){
		validationCheck = 0;
		failure++;
	}
	if (isDeckSame(&state, &stateOriginal, state.whoseTurn + 1) != 1){
		validationCheck = 0;
		failure++;
	}
	if (isDiscardSame(&state, &stateOriginal, state.whoseTurn + 1) != 1){
		validationCheck = 0;
		failure++;
	}
	printTestResult(validationCheck, 1, 0);

	printf("\n----Test #6: Game kingdom decks were not modified----\n");
	validationCheck = 1;
	for (i = 0; i < 28; i++) {
		if (state.supplyCount[i] != stateOriginal.supplyCount[i]){
			validationCheck = 0;
			failure++;
		}
	}
	printTestResult(validationCheck, 1, 1);
	
	if(failure == 0){
		printf("\n\n\n >>>>>>ALL TESTS PASSED: smithyCall() \n\n\n");
	}
	else{
		printf("\n\n\n >>>>>>FAILURES IN SMITHY: %d \n\n\n", failure);
	}
	
	return 0;
}