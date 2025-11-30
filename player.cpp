#include "player.hpp"
#include <iostream>
#include "card.hpp"

int Player::calculateScore() const {
    int currentScore = 0;
    int aceCount = 0;

    for (const Card& card : hand) {
        std::string rank = card.getRank();
        
        if (rank == "Ace") {
            currentScore += 11;
            aceCount++;
        } else if (rank == "King" || rank == "Queen" || rank == "Jack" || rank == "10") {
            currentScore += 10;
        } else {
            try {
                currentScore += std::stoi(rank); 
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error calculating score: Unknown rank '" << rank << "'\n";
            } catch (const std::out_of_range& e) {
                std::cerr << "Error calculating score: Rank value out of range\n";
            }
        }
    }

    while (currentScore > 21 && aceCount > 0) {
        currentScore -= 10;
        aceCount--;
    }

    return currentScore;
}

void Player::takeCard(const Card& card) {
    hand.push_back(card);
}
