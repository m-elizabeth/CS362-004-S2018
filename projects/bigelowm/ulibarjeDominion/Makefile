CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

randomtestcard1.out: randomtestcard1
	echo "randomtestcard1 results: " >> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c -b -f >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	echo "randomtestcard2 results: " >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c -b -f >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer
	echo "randomtestadventurer results: " >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c -b -f >> randomtestadventurer.out

unittestresults.out: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Card Test Results:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "" >> unittestresults.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.c rngs.c
	gcc -o cardtest1 -g cardtest1.c dominion.c rngs.c $(CFLAGS)

cardtest2: cardtest2.c dominion.c rngs.c
	gcc -o cardtest2 -g cardtest2.c dominion.c rngs.c $(CFLAGS)

cardtest3: cardtest3.c dominion.c rngs.c
	gcc -o cardtest3 -g cardtest3.c dominion.c rngs.c $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.c rngs.c $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestadventurer
