CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out:  dominion.h rngs.h dominion_helpers.h dominion.o rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c
	
	gcc -o unittest1 unittest1.c dominion.o rngs.o -g $(CFLAGS)
	./unittest1
	gcov unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.o rngs.o -g $(CFLAGS)
	./unittest2
	gcov unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.o rngs.o -g $(CFLAGS)
	./unittest3
	gcov unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.o rngs.o -g $(CFLAGS)
	./unittest4
	gcov unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest1
	gcov cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest2
	gcov cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest3
	gcov cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o -g $(CFLAGS)
	./cardtest4
	gcov cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
randomtestcard:  dominion.h rngs.h dominion_helpers.h dominion.o rngs.o
	
	gcc -o randomtestcard randomtestcard.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestcard
	gcov -b randomtestcard.c >> randomtestcard.out
	cat randomtestcard.c.gcov >> randomtestcard.out
	gcov -b dominion.c >> randomtestcard.out
	cat dominion.c.gcov >> randomtestcard.out
	
randomtestadventurer:  dominion.h rngs.h dominion_helpers.h dominion.o rngs.o
	
	gcc -o randomtestadventurer randomtestadventurer.c -g  dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer
	gcov -b randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestcard randomtestadventurer

clean:
	rm -f *.o playdom test player testInit *.exe *.gcov *.gcda *.gcno *.so