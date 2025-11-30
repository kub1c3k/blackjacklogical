#ifndef DEALER_HPP
#define DEALER_HPP

#include <vector>
#include <string>
#include "card.hpp"

class Dealer {
private:
    static const std::string ALL_SUITS[4];
    static const std::string ALL_RANKS[13];
    std::vector<Card> cards;

public:
    std::vector<Card> dealerHand; 
    
    Dealer() {
        for (const std::string& suit : ALL_SUITS) {
            for (const std::string& rank : ALL_RANKS) {
                this->cards.push_back(Card(rank, suit)); 
            }
        }
    }
    
    void shuffle(); 
    Card dealCard();
    
    size_t getDeckSize() const {
        return cards.size();
    }
    
    int calculateScore() const {
        int score = 0;
        int aces = 0;

        for (const auto& card : dealerHand) {
            score += card.getValue();
            if (card.getRank() == "Ace") aces++;
        }

        while (score > 21 && aces > 0) {
            score -= 10;
            aces--;
        }

        return score;
    }
};

#endif 