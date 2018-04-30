#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"


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

    int treasureCards = 0;
    int discarded = 1;
    int discardRevealed = 0;
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

    printf("TEST 1: Draw two treasure cards and put in hand\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // Add two treasure cards to hand and discard one card
    treasureCards = 2;

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + treasureCards - discarded);
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + treasureCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - treasureCards);
    assertTrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - treasureCards);

// ------------------------- Test Case 2 ----------------------

    printf("TEST 2: Discard revealed cards from deck\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // Reveal cards from deck until two treasures are found counting non-treasure cards to discard
    i = 0;
    j = 1;
    while(i < 2) {
        int revealedCard = G.hand[thisPlayer][G.handCount[thisPlayer]-j];
        if (revealedCard == copper || revealedCard == silver || revealedCard == gold)
          i++;
        else{
          discardRevealed++;
        }
        j++;
    }

    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - discardRevealed);
    assertTrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - discardRevealed);

// ------------------- Test Case 3 -----------------------

    printf("TEST 3: State changes for other players & victory/kingdom card piles\n");

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // only account for other players, not thisPlayer
    for(int i = 1; i < numPlayers; i++) {
        printf("Player: %d\n", i+1);
        printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
        assertTrue(testG.handCount[i], G.handCount[i]);
        printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
        assertTrue(testG.deckCount[i], G.deckCount[i]);
    }




}