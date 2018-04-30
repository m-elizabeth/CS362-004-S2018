#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"


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

    int newCoins = 0;
    int discarded = 1;
    int newCards = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
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

    printf("TEST 1: Choose +2 coins\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

    newCoins = 2;

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    assertTrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + newCoins);
    assertTrue(testG.coins, G.coins + newCoins);

    // ------------------ Test Case 2 ----------------------

    printf("TEST 2: No state changes for other players & victory/kingdom card piles after +2 coin\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

    // only account for other players, not thisPlayer
    for(int i = 1; i < numPlayers; i++) {
        printf("Player: %d\n", i+1);
        printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
        assertTrue(testG.handCount[i], G.handCount[i]);
        printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
        assertTrue(testG.deckCount[i], G.deckCount[i]);
    }

// ------------------------- Test Case 3 ----------------------

    printf("TEST 3: Choose to discard hand, +4 cards\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

    discarded = G.handCount[thisPlayer];
    newCards = 4;

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    assertTrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);

    // ------------------------- Test Case 4 ----------------------

        printf("TEST 4: Choosing to discard hand, +4 cards then all players with >=5 cards in hand discard hand, +4 cards\n");

        // make copy of game state for testing
        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);

        newCards = 4;
        for(int i = 1; i < numPlayers; i++) {
            if(testG.handCount[i] >= 5) {
               discarded = G.handCount[i];
                printf("Player: %d\n", i+1);
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i] + newCards - discarded);
                assertTrue(testG.handCount[i], G.handCount[i] + newCards - discarded);
                printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i] - newCards);
                assertTrue(testG.deckCount[i], G.deckCount[i] - newCards);
            }
            else {
                printf("Player: %d\n", i+1);
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
                assertTrue(testG.handCount[i], G.handCount[i]);
                printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
                assertTrue(testG.deckCount[i], G.deckCount[i]);

            }

        }
}