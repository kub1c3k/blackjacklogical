#include "dealer.hpp"
#include <iostream>
#include <algorithm>
#include <random>    
#include <chrono>    
#include <stdexcept>


const std::string Dealer::ALL_SUITS[4] = {
    "Diamonds", "Spades", "Clubs", "Hearts"
};

const std::string Dealer::ALL_RANKS[13] = {
    "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
};

void Dealer::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(cards.begin(), cards.end(), rng);
    std::cout << "Dealer shuffles the deck." << std::endl;
}

Card Dealer::dealCard() {
    if (cards.empty()) {
        throw std::out_of_range("Dealer cannot deal card: Deck is empty.");
    }
    
    Card dealtCard = cards.back(); 

    cards.pop_back(); 

    return dealtCard;
}


