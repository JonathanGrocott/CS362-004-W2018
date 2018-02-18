/* -----------------------------------------------------------------------
 * Author: Jonathan Grocott
 * Description: Unit tests for the initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state) function in dominion.c. 
 * File Name: unittest1.c
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

    int i;
	int failure = 0; 
    int seed = 1000;
    int totalPlayers;
    int result;
    int testNum = 3;

	printf("\n-----------------------------------------");
    printf("\n--------Testing Initialize Game----------");

   	printf("\n\n----Test #1: Initialize game with one player----");

   	memset(&test, 23, sizeof(struct gameState));   // clear the game state

   	totalPlayers = 1;

   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

    if(result == -1){
    	printf("\nSUCCESS: one player is not enough to play the game");
    }
    else{
    	printf("\n	Fail: one player alone cant play the game");
		failure = 1; 
    }

    printf("\n\n----Test #2: Initialize game with five players----");

   	memset(&test, 23, sizeof(struct gameState));   // clear the game state

   	totalPlayers = 5;

   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

    if(result == -1){
    	printf("\nSUCCESS: Five players is too much for the game");
    }
    else{
    	printf("\n	Fail: five players cant play the game");
		failure = 1; 
    }

    for(totalPlayers = 2; totalPlayers <=4; totalPlayers++){
    	printf("\n\n----Test #3: Initialize game with 2-4 players----");

    	testNum++;

	   	memset(&test, 23, sizeof(struct gameState));   // clear the game state

	   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

	    if(result == 0){
    	printf("\nSUCCESS: %d players is enough for the game", totalPlayers);
	    }
	    else{
	    	printf("\n	Fail: %d players are suppose to be able to play the game", totalPlayers);
			failure = 1; 
	    }
	    if(totalPlayers == 2){
	    	if(test.supplyCount[curse] == 10){
	    		printf("\nSUCCESS: supply count for curse is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for curse is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[estate] == 8){
	    		printf("\nSUCCESS: supply count for estate is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for estate is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[duchy] == 8){
	    		printf("\nSUCCESS: supply count for duchy is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for duchy is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[province] == 8){
	    		printf("\nSUCCESS: supply count for province is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for province is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[copper] == 60 - (7 * totalPlayers)){
	    		printf("\nSUCCESS: supply count for copper is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for copper is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[silver] == 40){
	    		printf("\nSUCCESS: supply count for silver is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for silver is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[gold] == 30){
	    		printf("\nSUCCESS: supply count for gold is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for gold is incorrect");
				failure = 1; 
	    	}
	    }
	    if(totalPlayers == 3){
	    	if(test.supplyCount[curse] == 20){
	    		printf("\nSUCCESS: supply count for curse is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for curse is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[estate] == 12){
	    		printf("\nSUCCESS: supply count for estate is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for estate is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[duchy] == 12){
	    		printf("\nSUCCESS: supply count for duchy is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for duchy is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[province] == 12){
	    		printf("\nSUCCESS: supply count for province is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for province is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[copper] == 60 - (7 * totalPlayers)){
	    		printf("\nSUCCESS: supply count for copper is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for copper is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[silver] == 40){
	    		printf("\nSUCCESS: supply count for silver is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for silver is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[gold] == 30){
	    		printf("\nSUCCESS: supply count for gold is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for gold is incorrect");
				failure = 1; 
	    	}
	    }
	    if(totalPlayers == 4){
	    	if(test.supplyCount[curse] == 30){
	    		printf("\nSUCCESS: supply count for curse is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for curse is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[estate] == 12){
	    		printf("\nSUCCESS: supply count for estate is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for estate is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[duchy] == 12){
	    		printf("\nSUCCESS: supply count for duchy is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for duchy is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[province] == 12){
	    		printf("\nSUCCESS: supply count for province is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for province is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[copper] == 60 - (7 * totalPlayers)){
	    		printf("\nSUCCESS: supply count for copper is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for copper is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[silver] == 40){
	    		printf("\nSUCCESS: supply count for silver is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for silver is incorrect");
				failure = 1; 
	    	}
	    	if(test.supplyCount[gold] == 30){
	    		printf("\nSUCCESS: supply count for gold is correct");
	    	}
	    	else{
	    		printf("\n	Fail: supply count for gold is incorrect");
				failure = 1; 
	    	}
	    }

    }
    	totalPlayers = 2;
    	memset(&test, 23, sizeof(struct gameState));   // clear the game state

	   	result = initializeGame(totalPlayers, k, seed, &test); // initialize a new game

	   	printf("\n\n----Test #4: Testing if kingdom cards are correct amount----");

	   	if(test.supplyCount[adventurer] == 10){
	   		printf("\nSUCCESS: supply count for adventurer is correct");
	   	}
	   	else{
	    	printf("\n	Fail: supply count for adventurer is incorrect");
			failure = 1; 
	    	}
	    if(test.supplyCount[gardens] == 8){
	   		printf("\nSUCCESS: supply count for gardens is correct");
	   	}
	   	else{
	    	printf("\n	Fail: supply count for gardens is incorrect");
			failure = 1; 
	    	}

	    for(i =0; i < totalPlayers; i++){
			
			if(i==0){
				if(test.handCount[i] == 5){
					printf("\nSUCCESS: Player #%d hand count is 5", i+1);
				}
				else{
					printf("\n	Fail: Player #%d hand count is not 5", i+1);
					failure = 1; 
					}
			}
			else{
				if(test.handCount[i] == 0){
					printf("\nSUCCESS: Player #%d hand count is empty", i+1);
				}
				else{
					printf("\n	Fail: Player #%d hand count is not empty", i+1);
					failure = 1; 
					}
			}
		    if(test.discardCount[i] == 0){
		    	printf("\nSUCCESS: Player #%d discardCount is empty", i+1);
		    }
		    else{
		    	printf("\n	Fail: Player #%d discardCount is not empty", i+1);
				failure = 1; 
		    	}

	    }

	    if(test.numActions == 1){
	   		printf("\nSUCCESS: Number of actions is correct");
	   	}
	   	else{
	    	printf("\n	Fail: Number of actions is incorrect");
			failure = 1; 
	    	}

	    if(test.numBuys == 1){
	   		printf("\nSUCCESS: Number of buys is correct");
	   	}
	   	else{
	    	printf("\n	Fail: Number of buys is incorrect");
			failure = 1; 
	    	}

	if(failure != 1){
		printf("\n\n\n >>>>>>ALL TESTS PASSED: initializeGame() \n\n\n");
	}



    return 0;
}