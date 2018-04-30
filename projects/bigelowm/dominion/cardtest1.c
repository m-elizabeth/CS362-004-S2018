#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"


int main() {


    // assert pass/fail function
    void assertTrue(int testResult, int gameResult) {
        if(testResult == gameResult) {
            printf("Assert Passed\n\n");
        }
        else {
            printf("Assert Failed\n\n");
        }
    }

    int newCards = 0;
    int discarded = 1;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    // initialize game state and players' cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing: %s ----------------\n", TESTCARD);
    printf("TEST 1: Draw +3 cards\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    // add three cards to players hand and discard one
    newCards = 3;
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    assertTrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);


    printf("TEST 2: State changes for other players & victory/kingdom card piles\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    // only account for other players, not thisPlayer
    for(int i = 1; i < numPlayers; i++) {
        printf("Player: %d\n", i+1);
        printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
        assertTrue(testG.handCount[i], G.handCount[i]);
        printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
        assertTrue(testG.deckCount[i], G.deckCount[i]);
    }

}