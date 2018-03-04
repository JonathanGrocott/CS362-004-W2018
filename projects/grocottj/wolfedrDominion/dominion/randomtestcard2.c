/******************************************************************************
 * Author: Jonathan Grocott
 * Description: Random test for the council_room card in dominion.c
 * Date Created: 2/13/2018
 *****************************************************************************/
 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "testTools.h"
#include "testTools.c"

//Bit to set the printf statements on/off
#define NOISY_TEST 1


int main (int argc, char** argv) {
	
	srand(time(NULL));
	int numTests = 10000;
    int numQuestions = 1;
	int sum = numTests*numQuestions;
	
#if (NOISY_TEST == 1)
	printf("\n**************************\n");
    printf("TESTING COUNCILL ROOM CARD\n");
	printf("**************************\n");
#endif

#if (NOISY_TEST == 1)
    printf("EXECUTING %d RANDOM TESTS......\n", sum);
#endif

    
    int failures = 0;
    for(int i = 0; i < numTests; i++){
        int numplayers = rand() % (MAX_PLAYERS - 1) + 2; // Value between 2 and 4.
        numQuestions += numplayers;
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

		//call council_room with randoms
        cardEffect(council_room, choice1, choice2, choice3, &G, handPos, &bonus);

        for(int i = 0; i < numplayers; i++){
            if(i == player){
				//Testing if player1 hand count incremented by +3
                if(G.handCount[i] != orig.handCount[i] + 3){
					#if (NOISY_TEST == 1)
                    printf("TEST FAILED: Player %d didn't get 3 more cards.\n", i);
                    #endif
					failures++;
                }
            }else{
				//Testing if player draw +1 card 
                if(G.handCount[i] != orig.handCount[i] + 1){
					#if (NOISY_TEST == 1)
                    printf("TEST FAILED: Player %d didn't draw 1 card.\n", i);
                    #endif
					failures++;
                }
            }
			//Test that player gets +1 buys
			if(G.numBuys != orig.numBuys + 1){
					#if (NOISY_TEST == 1)
                    printf("TEST FAILED: Player %d didn't get +1 buys.\n", i);
                    #endif
					failures++;
                }
			
        }
    }
#if (NOISY_TEST == 1)
    printf(">>> %d of %d TESTS PASSED\n", numQuestions - failures, numQuestions);
	printf("**************************\n\n");
#endif
}