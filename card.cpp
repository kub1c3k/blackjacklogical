
#include "card.hpp"

int Card::getValue() const {
    if (this->rank == "Jack" || this->rank == "Queen" || this->rank == "King") {
        return 10;
    } 
    else if (this->rank == "Ace") {
        return 11;
    }
    else {
        try {
            return std::stoi(this->rank);
        }
        catch (const std::exception& e) {
            std::cerr << "Problem pri ranku (Invalid Rank String): " << this->rank << std::endl;
            return 0; 
        }
    }
}