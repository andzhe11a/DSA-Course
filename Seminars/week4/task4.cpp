#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

unsigned int kittens(const std::string& cards, unsigned int players) {
    std::queue<char> deck;
    for (size_t i = 0; i < cards.length(); ++i) {
        deck.push(cards[i]);
    }

    std::queue<int> playerQueue;
    for (unsigned int i = 1; i <= players; ++i) {
        playerQueue.push(i);
    }

    std::vector<int> defuseCards(players + 1, 0);
    while (playerQueue.size() > 1) {
        int currentPlayer = playerQueue.front();
        playerQueue.pop();

        char currentCard = deck.front();
        deck.pop();

        if (currentCard == 'O') {
            playerQueue.push(currentPlayer);
        }
        else if (currentCard == 'S') {
            defuseCards[currentPlayer]++;
            playerQueue.push(currentPlayer);
        }
        else if (currentCard == 'B') {
            if (defuseCards[currentPlayer] > 0) {
                defuseCards[currentPlayer]--;

                deck.push('B');
                playerQueue.push(currentPlayer);
            } else {}
        }
    }
    return playerQueue.front();
}

int main() {
    std::cout << kittens("BB", 3) << std::endl;
    std::cout << kittens("SSBB", 3) << std::endl;
    std::cout << kittens("SSBBOOOOOOOSBOOOOOOOOOSB", 5) << std::endl;
    std::cout << (kittens("SOOSBBOOOOSOOOSBOSOOBOSOSOOBOSOSOOB", 7)) << std::endl;

    return 0;
}