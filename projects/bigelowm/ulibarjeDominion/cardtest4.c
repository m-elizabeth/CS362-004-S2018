#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "seahag"


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

    int discarded = 1;

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

// ------------------------ Test Case 1 ----------------------------

    printf("TEST 1: All other players discards the top card of their deck\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);

    // for other players only, discard one from deck
    for(int i = 1; i < numPlayers; i++) {
        if(i != thisPlayer) {
            printf("Player: %d\n", i+1);
            printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
            assertTrue(testG.handCount[i], G.handCount[i]);
            printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i] - discarded);
            assertTrue(testG.deckCount[i], G.deckCount[i] - discarded);
        }
    }

    // ------------------ Test Case 2 ----------------------

    printf("TEST 2: Other players gain a curse card on top of their deck\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);

    // only account for other players and make top deck card a curse card
    for(int i = 1; i < numPlayers; i++) {
        if(i != thisPlayer) {
            printf("Player: %d\n", i+1);
            printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
            assertTrue(testG.handCount[i], G.handCount[i]);
            printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
            assertTrue(testG.deckCount[i], G.deckCount[i]);
            printf("deck top card = %d, expected = %d\n", testG.deck[i][testG.deckCount[i]--], G.deck[i][G.deckCount[i]--] = curse);
            assertTrue(testG.deck[i][testG.deckCount[i]--], G.deck[i][G.deckCount[i]--] = curse);

        }
    }

}