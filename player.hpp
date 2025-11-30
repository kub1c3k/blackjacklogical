#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "card.hpp"

class Player {
private:
    int score;
    

public:
    std::vector<Card> hand; 
    int balance;
    Player(int b) : balance(b), score(0) {}

    int calculateScore() const; 

    void takeCard(const Card& card);

     
};

#endif 