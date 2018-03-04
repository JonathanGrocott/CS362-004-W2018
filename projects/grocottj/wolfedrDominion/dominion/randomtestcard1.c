/******************************************************************************
 * Author: Jonathan Grocott
 * Description: Random test for the smithy card in dominion.c
 * Date Created: 2/13/2018
 *****************************************************************************/
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "dominion_helpers.h"
#include "rngs.h"
#include "testTools.h"
#include "testTools.c"


//Bit to set the printf statements on/off
#define NOISY_TEST 1


int main() {
    
	srand(time(NULL));
    struct errors e = {0};

#if (NOISY_TEST == 1)
	printf("\n**************************\n");
    printf("TESTING SMITHY CARD\n");
	printf("**************************\n");
	printf("EXECUTING %d RANDOM TESTS....\n", NUMTESTS);
#endif
	//For each test randomize the game state and test
    for (int i = 0; i < NUMTESTS; i++) {
		struct gameState state;
		randomizeGameState(&state);
		engine_testSmithy(&state, &e);
    }

	//If there are failures print them
    if (e.metric1 + e.metric2 + e.metric3 + e.metric4 + e.metric5 > 0){
		#if (NOISY_TEST == 1)
			printf("\nTESTS FAILED, Details Below\n");
			printf("\n*****ERROR RATES*****\n");
			printf("PLAYER CARD COUNT: %.2f%%\n", e.metric1 * 1.0 / NUMTESTS * 100);
			printf("PLAYER HAND COUNT: %.2f%%\n", e.metric2 * 1.0 / NUMTESTS * 100);
			printf("DECK COUNT: %.2f%%\n", e.metric3 * 1.0 / NUMTESTS * 100);
			printf("OPPONENT CARD COUNT: %.2f%%\n", e.metric4 * 1.0 / NUMTESTS * 100);
			printf("**************************\n\n");
		#endif
	}
    else{
		//If no failures print all tests passed 
		#if (NOISY_TEST == 1)
		printf(">>> ALL %d TESTS PASSED\n", NUMTESTS);
		printf("**************************\n\n");
		#endif
	}
		
    return 0;
}
