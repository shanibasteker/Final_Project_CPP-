//311318075
//shanibasteker@gmail.com

#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"

using namespace std;

string card_descriptions[] = {
    "Advance to Go (Collect $200)",
    "Bank pays you dividend of $50",
    "Go back 3 spaces",
    "Go directly to Jail (No $200)",
    "Pay poor tax of $15",
    "Trip to Reading Railroad",
    "Walk on Boardwalk",
    "Elected Chairman (Pay $50 to each player)",
    "Building loan matures (Collect $150)",
    "Get Out of Jail Free card",
    "Advance to Illinois Avenue",
    "Advance to St. Charles Place",
    "Advance to nearest Utility",
    "Advance to nearest Railroad",
    "Bank error in your favor (Collect $200)",
    "Doctor's fee (Pay $50)",
    "Sale of stock (Collect $50)",
    "Holiday fund matures (Collect $100)",
    "Income tax refund (Collect $20)",
    "It's your birthday (Collect $10 from each player)",
    "Life insurance matures (Collect $100)",
    "Pay hospital fees of $100",
    "Pay school fees of $50",
    "Receive consultancy fee ($25)",
    "Win beauty contest (Collect $10)",
    "Inheritance (Collect $100)"
};

// Enum for Card Types
enum class CardType
{
    ADVANCE_TO_GO,
    BANK_PAYS_DIVIDEND,
    GO_BACK_3_SPACES,
    GO_DIRECTLY_TO_JAIL,
    PAY_POOR_TAX,
    TRIP_TO_READING_RR,
    WALK_ON_BOARDWALK,
    ELECTED_CHAIRMAN,
    BUILDING_LOAN_MATURES,
    GET_OUT_OF_JAIL_FREE,
    ADVANCE_TO_ILLINOIS,
    ADVANCE_TO_ST_CHARLES,
    NEAREST_UTILITY,
    NEAREST_RAILROAD,
    BANK_ERROR_IN_YOUR_FAVOR,
    DOCTORS_FEE,
    SALE_OF_STOCK,
    HOLIDAY_FUND,
    INCOME_TAX_REFUND,
    BIRTHDAY,
    LIFE_INSURANCE_MATURES,
    PAY_HOSPITAL_FEES,
    PAY_SCHOOL_FEES,
    CONSULTANCY_FEE,
    BEAUTY_CONTEST,
    INHERITANCE
};

/*

Advance to Go (Collect $200)
Bank pays you dividend of $50
Go back 3 spaces
Go to Jail (Directly to jail, no $200)
Pay poor tax of $15
Trip to Reading Railroad
Advance to nearest Railroad
Advance to nearest Utility
Elected Chairman (Pay $50 to each player)
Building Loan Matures (Collect $150)
Bank error in your favor (Collect $200)
Doctor's fee (Pay $50)
Sale of stock (Collect $50)
Holiday fund matures (Collect $100)
Income tax refund (Collect $20)
It's your birthday (Collect $10 from each player)
Life insurance matures (Collect $100)
Pay hospital fees of $100
Pay school fees of $50
Receive consultancy fee ($25)
Win beauty contest (Collect $10)
Inherit $100

*/

class Card
{
private:
    string description;       // Description of the card
    CardType cardType;        // Type of the card

public:
    Texture texture;    //  Texture
    Sprite sprite;      //  Sprite

    // Constructor
    Card(string description, CardType cardType, bool keepCard = false)
        : description(description), cardType(cardType){}

    // Apply Card Effect
    void applyEffect(Player* currentPlayer, Board& board, vector<Player*>& allPlayers)
    {
        switch (cardType)
        {
        case CardType::ADVANCE_TO_GO:
            currentPlayer->moveTo(0);     // Move to "Go"
            currentPlayer->addMoney(200); // Collect $200
            break;

        case CardType::BANK_PAYS_DIVIDEND:
            currentPlayer->addMoney(50); // Add $50
            break;

        case CardType::GO_BACK_3_SPACES:
            currentPlayer->move(-3); // Move back 3 spaces
            break;

        case CardType::GO_DIRECTLY_TO_JAIL:
            currentPlayer->goToJail(); // Send the player to jail
            break;

        case CardType::PAY_POOR_TAX:
            currentPlayer->payRent(15); // Pay $15 poor tax
            break;

        case CardType::TRIP_TO_READING_RR:
            currentPlayer->moveTo(board.getRailroadPosition("Reading Railroad"));
            currentPlayer->addMoney(200); // Collect $200 if they pass "Go"
            break;

        case CardType::WALK_ON_BOARDWALK:
            currentPlayer->moveTo(board.getBoardwalkPosition()); // Move to Boardwalk
            break;

        case CardType::ELECTED_CHAIRMAN:
            payEachPlayer(currentPlayer, allPlayers, 50); // Pay $50 to each player
            break;

        case CardType::BUILDING_LOAN_MATURES:
            currentPlayer->addMoney(150); // Collect $150
            break;

        case CardType::GET_OUT_OF_JAIL_FREE:
            currentPlayer->giveJailFreeCard();
            break;

        case CardType::ADVANCE_TO_ILLINOIS:
            currentPlayer->moveTo(board.getPropertyPosition("Illinois Ave"));
            currentPlayer->addMoney(200); // Collect $200 if they pass "Go"
            break;

        case CardType::ADVANCE_TO_ST_CHARLES:
            currentPlayer->moveTo(board.getPropertyPosition("St. Charles Place"));
            currentPlayer->addMoney(200); // Collect $200 if they pass "Go"
            break;

        case CardType::NEAREST_UTILITY:
            moveToNearestUtility(currentPlayer, board); // Move to nearest utility
            break;

        case CardType::NEAREST_RAILROAD:
            moveToNearestRailroad(currentPlayer, board); // Move to nearest railroad
            break;

        case CardType::BANK_ERROR_IN_YOUR_FAVOR:
            currentPlayer->addMoney(200); // Collect $200
            break;

        case CardType::DOCTORS_FEE:
            currentPlayer->payRent(50); // Pay $50
            break;

        case CardType::SALE_OF_STOCK:
            currentPlayer->addMoney(50); // Collect $50
            break;

        case CardType::HOLIDAY_FUND:
            currentPlayer->addMoney(100); // Collect $100
            break;

        case CardType::INCOME_TAX_REFUND:
            currentPlayer->addMoney(20); // Collect $20
            break;

        case CardType::BIRTHDAY:
            for (Player* player : allPlayers)
            {
                if (player != currentPlayer)
                {
                    currentPlayer->addMoney(10);
                    player->payRent(10);
                }
            }
            break;

        case CardType::LIFE_INSURANCE_MATURES:
            currentPlayer->addMoney(100); // Collect $100
            break;

        case CardType::PAY_HOSPITAL_FEES:
            currentPlayer->payRent(100); // Pay $100 hospital fees
            break;

        case CardType::PAY_SCHOOL_FEES:
            currentPlayer->payRent(50); // Pay $50 school fees
            break;

        case CardType::CONSULTANCY_FEE:
            currentPlayer->addMoney(25); // Collect $25 consultancy fee
            break;

        case CardType::BEAUTY_CONTEST:
            currentPlayer->addMoney(10); // Collect $10 for winning beauty contest
            break;

        case CardType::INHERITANCE:
            currentPlayer->addMoney(100); // Collect $100 inheritance
            break;
        }
    }

    void payEachPlayer(Player* currentPlayer, vector<Player*>& allPlayers, int amount)
    {
        for (Player* player : allPlayers)
        {
            if (player != currentPlayer)
            {
                currentPlayer->payRent(amount);
                player->addMoney(amount);
            }
        }
    }

    void moveToNearestUtility(Player* player, Board& board)
    {
        int nearestUtility = board.findNearestUtility(player->getPosition());
        player->moveTo(nearestUtility);
    }

    void moveToNearestRailroad(Player* player, Board& board)
    {
        int nearestRailroad = board.findNearestRailroad(player->getPosition());
        player->moveTo(nearestRailroad);
    }

    // Getter for Card Description
    string getDescription() const
    {
        return description;
    }
};
