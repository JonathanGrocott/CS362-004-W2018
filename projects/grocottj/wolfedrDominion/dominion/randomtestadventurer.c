/******************************************************************************
 * Author: Jonathan Grocott
 * Description: Random test for the adventurer card in dominion.c
 * Date Created: 2/12/2018
 *****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

//Bit to set the printf statements on/off
#define NOISY_TEST 1


int main (int argc, char** argv) {

    srand(time(NULL));
	int numTests = 10000; //change back to 1000
    int NUMQUESTIONS = 3;

#if (NOISY_TEST == 1)
	printf("\n**************************\n");
    printf("TESTING ADVENTURER CARD\n");
	printf("**************************\n");
#endif
	
#if (NOISY_TEST == 1)
    printf("EXECUTING RANDOM TESTS......\n");
#endif


    int failures = 0;
    for(int i = 0; i < numTests; i++){
        int numplayers = rand() % (MAX_PLAYERS - 1) + 2; // Value between 2 and 4.
        struct gameState G;
        int k[10] = {adventurer, gardens, embargo, village, steward, mine, cutpurse, sea_hag, tribute, smithy};

        initializeGame(numplayers, k, rand(), &G);

        int player = rand() % numplayers;
        G.whoseTurn = player;
        
		//set random numbers for inputs
        int bonus = rand() % 50;
        int choice1 = rand() % 50;
        int choice2 = rand() % 50;
        int choice3 = rand() % 50;
        int handPos = rand() % MAX_HAND;

		//original and copy of gamestate
        struct gameState orig;
        memcpy(&orig, &G, sizeof(struct gameState));

		//call adventurer with randoms
        cardEffect(adventurer, choice1, choice2, choice3, &G, handPos, &bonus);

		//Testing if hand count incremented by +2
        if(G.handCount[player] != (orig.handCount[player] + 2)){
            #if (NOISY_TEST == 1)
			printf("TEST FAILED: Player %d didn't draw 2 cards.\n", player);
            #endif
			failures++;
        }

		//Testing if players newest/top card drawn is copper, silver or gold
        int cardDrawn1 = G.hand[player][G.handCount[player] - 1];//top card 
        if(cardDrawn1 != copper && cardDrawn1 != silver && cardDrawn1 != gold){
            #if (NOISY_TEST == 1)
			printf("TEST FAILED: Player %d's newest card isn't Copper/Silver/Gold.\n", player);
            #endif
			failures++;
        }

		//Testing if players second newest card is copper, silver or gold
        int cardDrawn2 = G.hand[player][G.handCount[player] - 2];
        if(cardDrawn2 != copper && cardDrawn2 != silver && cardDrawn2 != gold){
            #if (NOISY_TEST == 1)
			printf("TEST FAILED: Player %d's second newest card isn't Copper/Silver/Gold.\n", player);
            #endif
			failures++;
        }
		
    }
	
#if (NOISY_TEST == 1)
    printf(">>> %d of %d TESTS PASSED\n\n", numTests * NUMQUESTIONS - failures, numTests * NUMQUESTIONS);
#endif

}
