
#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <stdexcept> 
#include <iostream>  

class Card {
private:
    std::string suit;
    std::string rank;
   
                 
public:
    Card(std::string r, std::string s) : rank(r), suit(s) {}

    int getValue() const;
    std::string getRank() const { return rank; }
    std::string getSuit() const { return suit; }
};

#endif 