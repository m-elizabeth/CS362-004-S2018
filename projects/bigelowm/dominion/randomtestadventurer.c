#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    srand(time(NULL));

    int treasureCards = 2;
    int discarded = 1;
    int discardRevealed = 0;

    int p, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;


    int numCards = 10;
    int k[numCards];

    // set random kingdom cards picked from 12 cards
    j = 12;
    p = 0;

    void setKingdomCardsRandom() {
        const char *kCards[13];
        kCards[0] = adventurer;
        kCards[1] = gardens;
        kCards[2] = embargo;
        kCards[3] = village;
        kCards[4] = smithy;
        kCards[5] = minion;
        kCards[6] = mine;
        kCards[7] = cutpurse;
        kCards[8] = tribute;
        kCards[9] = sea_hag;
        kCards[10] = great_hall;
        kCards[11] = steward;
        kCards[12] = baron;

        for(int i = 0; i < numCards; i++) {
            m = kCards[rand() % (j - 1) + 1]; // get random kingdom card from kCards
            for(int x = 0; x < numCards; x++) { // check if card has already been chosen
                if(m == k[x]) {
                    p++;
                }
            }
            if(p == 0) { // if selected card has not been chosen, add to kingdom cards
                k[i] = m;
            }
            else { // otherwise try again
                p = 0;
                i--;
            }
        }

    }

//    for(int i = 0; i < numCards; i++) {
//        printf("Card: %d\n", k[i]);
//    }

    printf("----------------- Random Testing: %s ----------------\n\n", TESTCARD);


    // set the random kingdom cards
    setKingdomCardsRandom();

    // initialize game state and random kingdom cards
    initializeGame(numPlayers, k, seed, &G);

    // set players hands a random number between 1 and 5
    void setPlayerHandsRandom() {
        int drawCardNum = rand() % 4 + 1;
        // set other players hands
        for(int i = 1; i < numPlayers; i++) {
            for(int k = 0; k < drawCardNum; k++) {
                drawCard(i, &G);
            }
            //printf("Player %d: %d hand & %d deck\n\n", i+1, G.handCount[i], G.deckCount[i]);
        }

        // set current players hand
        G.handCount[thisPlayer] = 0;
        G.deckCount[thisPlayer] = 10;
        drawCardNum = rand() % 4 +1;
        for(int i = 0; i < drawCardNum; i++) {
            drawCard(thisPlayer, &G);
        }
        //printf("Player 1: %d hand & %d deck\n\n", G.handCount[thisPlayer], G.deckCount[thisPlayer]);
    }

    // set the players' handCounts
    setPlayerHandsRandom();

    // make copy of game state for testing
    memcpy(&testG, &G, sizeof(struct gameState));

    // check state changes for other players
    printf("----- Testing Other Players' State Changes -----\n\n");

    for(int i = 1; i < numPlayers; i++) {
        printf("Player %d >> hand count: %d, expected: %d\n", i, testG.handCount[i], G.handCount[i]);
        assertTrue(testG.handCount[i], G.handCount[i]);
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // check state changes for current player
    printf("----- Testing Current Player's State Changes -----\n\n");

    // Reveal cards from deck until two treasures are found counting non-treasure cards to discard
    int i = 0;
    int index = 1;
    while(i < treasureCards) {
        int revealedCard = G.hand[thisPlayer][G.handCount[thisPlayer]-index];
        if (revealedCard == copper || revealedCard == silver || revealedCard == gold)
          i++;
        else{
          discardRevealed++;
        }
        index++;
    }

    // add new cards to players hand and discard one
    printf("hand count: %d, expected: %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + treasureCards - discarded);
    assertTrue(testG.handCount[thisPlayer], G.handCount[thisPlayer] + treasureCards - discarded);
    printf("deck count: %d, expected: %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - (treasureCards + discardRevealed));
    assertTrue(testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - (treasureCards + discardRevealed));
}