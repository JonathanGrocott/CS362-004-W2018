/* -----------------------------------------------------------------------
 * Author: Jonathan Grocott
 * Description: Unit tests for the isGameOver(struct gameState *state) 
	function in dominion.c. 
 * File Name: unittest3.c
 * Date Created: 1/31/2018
 * -----------------------------------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {

	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState test;

    int seed = 1000;
    int totalPlayers = 2;
    int result;
	int failure = 0; 
	
	printf("\n\n-----------------------------------------");
    printf("\n--------Testing isGameOver()----------\n\n");

    printf("----Test #1: isGameOver() testing for no state change----");

    memset(&test, 23, sizeof(struct gameState));   // clear the game state
	 
    initializeGame(totalPlayers, k, seed, &test); // initialize a new game

    result = isGameOver(&test);

    if(result == 0){
    	printf("\nSUCCESS: No change in game state");
    }
    else{
    	printf("\n	Fail: Game should not end");
		failure = 1;
    }

    printf("\n\n----Test #2: isGameOver() testing when province = 0----");

    memset(&test, 23, sizeof(struct gameState));   // clear the game state
 
    initializeGame(totalPlayers, k, seed, &test); // initialize a new game
    test.supplyCount[province] = 0;
    result = isGameOver(&test);

    if(result == 1){
    	printf("\nSUCCESS: Province is out of supply: game ends");
    }
    else{
    	printf("\n	Fail: Game was suppose to end");
		failure = 1;
    }
    printf("\n\n----Test #3: isGameOver() testing when province = 1----");

    memset(&test, 23, sizeof(struct gameState));   // clear the game state

    initializeGame(totalPlayers, k, seed, &test); // initialize a new game
    test.supplyCount[province] = 1;

    result = isGameOver(&test);

    if(result == 0){
    	printf("\nSUCCESS: Province has 1 card left: game continues");
    }
    else{
    	printf("\n	Fail: Game was not suppose to end");
		failure = 1;
    }

    printf("\n\n----Test #4: isGameOver() testing when province = 1, supply count is 0----");
    test.supplyCount[adventurer] = 0;
    result = isGameOver(&test);

    if(result == 0){
    	printf("\nSUCCESS: Game continued");
    }
    else{
    	printf("\n	Fail: Game was not suppose to end");
		failure = 1;
    }
    printf("\n\n----Test #5: isGameOver() testing when province = 1, two supply count is 0----");
    test.supplyCount[smithy] = 0;
    result = isGameOver(&test);

    if(result == 0){
    	printf("\nSUCCESS: Game continued");
    }
    else{
    	printf("\n	Fail: Game was not suppose to end");
		failure = 1;
    }
    printf("\n\n----Test #6: isGameOver() testing when province = 1, three supply count is 0----");
    test.supplyCount[feast] = 0;
    result = isGameOver(&test);

    if(result == 1){
    	printf("\nSUCCESS: Game ended");
    }
    else{
    	printf("\n	Fail: Game was suppose to end");
		failure = 1;
    }
	
	if(failure != 1){
		printf("\n\n\n >>>>>>ALL TESTS PASSED: isGameOver() \n\n\n");
	}

	return 0;
 
}