#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include "card.hpp"
#include "dealer.hpp"
#include "player.hpp"

void printRules();
void slowPrint(const std::string& text, int delayMs = 30);
void pause(int milliseconds);
void dealCardAnimation(const Card& card, const std::string& recipient);

int main() {
    Dealer dealer;
    slowPrint("═══════════════════════════════════════\n", 20);
    slowPrint("  Vítam ťa v logickom BlackJacku! \n", 40);
    slowPrint("═══════════════════════════════════════\n\n", 20);
    printRules();

    std::cout << "\nZvoľ obtiažnosť (1–5): ";
    int difficulty;
    std::cin >> difficulty;

    int startingMoney = 0;

    switch (difficulty) {
        case 1: startingMoney = 5000; break;
        case 2: startingMoney = 2500; break;
        case 3: startingMoney = 1250; break;
        case 4: startingMoney = 750; break;
        case 5: startingMoney = 250; break;
        default:
            std::cout << "Neplatná voľba → nastavujem EASY.\n";
            startingMoney = 5000;
    }

    Player player(startingMoney);
    slowPrint("\n💰 Tvoj začiatočný balanc: ", 30);
    std::cout << startingMoney << " €\n";
    pause(800);

    while (player.balance > 0) {
        std::cout << "\n";
        slowPrint("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n", 15);
        slowPrint("        NOVÁ HRA\n", 30);
        slowPrint("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n", 15);
        pause(500);
        
        dealer.shuffle();
        pause(800);
        player.hand.clear();
        dealer.dealerHand.clear();

        std::cout << "\n💵 Tvoj aktuálny balanc: " << player.balance << " €\n";
        int bet;
        std::cout << "Zadaj svoju stávku: ";
        std::cin >> bet;

        if (bet > player.balance || bet <= 0) {
            slowPrint("❌ Neplatná stávka.\n", 30);
            pause(500);
            continue;
        }

        slowPrint("\n🃏 Rozdávam karty", 50);
        std::cout << std::flush;
        for (int i = 0; i < 3; i++) {
            pause(300);
            std::cout << "." << std::flush;
        }
        std::cout << "\n\n";
        pause(500);

        Card card1 = dealer.dealCard();
        dealCardAnimation(card1, "TY");
        player.takeCard(card1);
        
        Card card2 = dealer.dealCard();
        dealCardAnimation(card2, "TY");
        player.takeCard(card2);

        Card hidden = dealer.dealCard();
        dealer.dealerHand.push_back(hidden);
        slowPrint("\n🂠 DEALER: [SKRYTÁ KARTA]\n", 30);
        pause(600);

        Card visible = dealer.dealCard();
        dealer.dealerHand.push_back(visible);
        dealCardAnimation(visible, "DEALER");
        
        pause(800);
        std::cout << "\n";
        slowPrint("═══════════════════════════════════════\n", 15);
        slowPrint("          TVOJA RUKA\n", 30);
        slowPrint("═══════════════════════════════════════\n", 15);
        for (auto &c : player.hand) {
            std::cout << "  🃏 " << c.getRank() << " of " << c.getSuit() << "\n";
            pause(200);
        }

        slowPrint("\n🎯 Dealerova viditeľná karta:\n", 30);
        std::cout << "  🃏 " << visible.getRank() << " of " << visible.getSuit() << "\n";
        pause(500);

        bool roundEnded = false;

        while (true) {
            int score = player.calculateScore();
            std::cout << "\n";
            slowPrint("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n", 10);
            std::cout << "📊 Tvoje skóre: " << score << "\n";
            slowPrint("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n", 10);

            if (score > 21) {
                pause(500);
                slowPrint("\n💥 BUST! Prehral si.\n", 50);
                pause(1000);
                player.balance -= bet;
                roundEnded = true;
                break;
            }

            std::cout << "\n🤔 Chceš ďalšiu kartu? (h = hit, s = stand): ";
            char choice;
            std::cin >> choice;

            if (choice == 'h' || choice == 'H') {
                pause(300);
                slowPrint("\n🎴 Berieš kartu", 50);
                for (int i = 0; i < 3; i++) {
                    pause(300);
                    std::cout << "." << std::flush;
                }
                std::cout << "\n";
                pause(500);
                
                Card newCard = dealer.dealCard();
                std::cout << "\n  ➜ Zobral si: " << newCard.getRank() 
                          << " of " << newCard.getSuit() << "\n";
                pause(800);
                player.takeCard(newCard);
            } else {
                pause(300);
                slowPrint("\n✋ Zostávaš so svojimi kartami.\n", 40);
                pause(800);
                break; 
            }
        }

        if (!roundEnded) {
            std::cout << "\n";
            slowPrint("═══════════════════════════════════════\n", 15);
            slowPrint("        DEALER NA ŤAHU\n", 35);
            slowPrint("═══════════════════════════════════════\n", 15);
            pause(1000);
            
            slowPrint("\n🎴 Dealer odhaľuje skrytú kartu", 50);
            for (int i = 0; i < 3; i++) {
                pause(400);
                std::cout << "." << std::flush;
            }
            std::cout << "\n\n";
            pause(600);
            
            slowPrint("Dealerove karty:\n", 30);
            for (auto &c : dealer.dealerHand) {
                std::cout << "  🃏 " << c.getRank() << " of " << c.getSuit() << "\n";
                pause(400);
            }

            pause(800);
            
            while (true) {
                int dealerScore = dealer.calculateScore();
                std::cout << "\n📊 Dealer skóre: " << dealerScore << "\n";
                pause(800);

                if (dealerScore > 21) {
                    pause(500);
                    slowPrint("\n💥 Dealer BUST! Vyhral si! 🎉\n", 50);
                    pause(1200);
                    player.balance += bet;
                    roundEnded = true;
                    break;
                }

                if (dealerScore < 17) {
                    pause(600);
                    slowPrint("\n🎴 Dealer musí zobrať kartu", 50);
                    for (int i = 0; i < 3; i++) {
                        pause(300);
                        std::cout << "." << std::flush;
                    }
                    std::cout << "\n";
                    pause(500);
                    
                    Card dealerCard = dealer.dealCard();
                    std::cout << "  ➜ Dealer zobral: " << dealerCard.getRank() 
                              << " of " << dealerCard.getSuit() << "\n";
                    dealer.dealerHand.push_back(dealerCard);
                    pause(1000);
                } else {
                    pause(500);
                    slowPrint("\n✋ Dealer zostáva na " + std::to_string(dealerScore) + ".\n", 40);
                    pause(800);
                    break; 
                }
            }
        }

        if (!roundEnded) {
            int playerScore = player.calculateScore();
            int dealerScore = dealer.calculateScore();

            std::cout << "\n";
            slowPrint("═══════════════════════════════════════\n", 15);
            slowPrint("        FINÁLNE SKÓRE\n", 35);
            slowPrint("═══════════════════════════════════════\n", 15);
            pause(800);
            
            std::cout << "\n  TY:     " << playerScore << "\n";
            pause(400);
            std::cout << "  DEALER: " << dealerScore << "\n\n";
            pause(1000);

            slowPrint("Vyhodnocovanie", 50);
            for (int i = 0; i < 3; i++) {
                pause(400);
                std::cout << "." << std::flush;
            }
            std::cout << "\n\n";
            pause(800);

            if (playerScore > dealerScore) {
                slowPrint("🎉 VYHRAL SI! 🎉\n", 50);
                pause(500);
                std::cout << "💰 Získavaš +" << bet << " €\n";
                player.balance += bet;
            }
            else if (playerScore < dealerScore) {
                slowPrint("😞 Prehral si.\n", 50);
                pause(500);
                std::cout << "💸 Stráca si -" << bet << " €\n";
                player.balance -= bet;
            }
            else {
                slowPrint("🤝 Remíza! Stávka sa vracia.\n", 50);
            }
            pause(1000);
        }

        std::cout << "\n";
        slowPrint("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n", 10);
        std::cout << "💰 Tvoj balanc: " << player.balance << " €\n";
        slowPrint("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n", 10);
        pause(1000);

        if (player.balance <= 0) {
            std::cout << "\n";
            slowPrint("═══════════════════════════════════════\n", 15);
            slowPrint("     💸 GAME OVER 💸\n", 50);
            slowPrint("  Nemáš už žiadne peniaze!\n", 40);
            slowPrint("═══════════════════════════════════════\n", 15);
            pause(1500);
            break;
        }

        std::cout << "\n🎲 Chceš hrať znova? (y/n): ";
        char again;
        std::cin >> again;
        if (again != 'y' && again != 'Y') {
            slowPrint("\n👋 Ďakujem za hru! Ahoj!\n", 40);
            pause(500);
            break;
        }
    }

    return 0;
}

void printRules() {
    slowPrint("Cieľ hry je jednoduchý, nahraj 10 000 euro!\n", 25);
    pause(300);
    slowPrint("Nehráš s reálnymi peniazmi, ale s fiktívnymi.\n\n", 25);
    pause(300);
    slowPrint("Tu sú dané obtiažnosti:\n", 30);
    pause(200);
    std::cout << "  1. Easy   - Balanc 5000 €\n";
    pause(150);
    std::cout << "  2. OK     - Balanc 2500 €\n";
    pause(150);
    std::cout << "  3. Mid    - Balanc 1250 €\n";
    pause(150);
    std::cout << "  4. Hard   - Balanc 750 €\n";
    pause(150);
    std::cout << "  5. Insane - Balanc 250 €\n";
    pause(300);
}

void slowPrint(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        pause(delayMs);
    }
}

void pause(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void dealCardAnimation(const Card& card, const std::string& recipient) {
    slowPrint("\n🎴 Karta pre " + recipient + ": ", 30);
    pause(400);
    std::cout << card.getRank() << " of " << card.getSuit() << "\n";
    pause(600);
}