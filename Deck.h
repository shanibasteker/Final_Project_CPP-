//311318075
//shanibasteker@gmail.com

#pragma once
#include "Card.h"

const CardType allCardTypes[] = {
    CardType::ADVANCE_TO_GO,
    CardType::BANK_PAYS_DIVIDEND,
    CardType::GO_BACK_3_SPACES,
    CardType::GO_DIRECTLY_TO_JAIL,
    CardType::PAY_POOR_TAX,
    CardType::TRIP_TO_READING_RR,
    CardType::WALK_ON_BOARDWALK,
    CardType::ELECTED_CHAIRMAN,
    CardType::BUILDING_LOAN_MATURES,
    CardType::GET_OUT_OF_JAIL_FREE,
    CardType::ADVANCE_TO_ILLINOIS,
    CardType::ADVANCE_TO_ST_CHARLES,
    CardType::NEAREST_UTILITY,
    CardType::NEAREST_RAILROAD,
    CardType::BANK_ERROR_IN_YOUR_FAVOR,
    CardType::DOCTORS_FEE,
    CardType::SALE_OF_STOCK,
    CardType::HOLIDAY_FUND,
    CardType::INCOME_TAX_REFUND,
    CardType::BIRTHDAY,
    CardType::LIFE_INSURANCE_MATURES,
    CardType::PAY_HOSPITAL_FEES,
    CardType::PAY_SCHOOL_FEES,
    CardType::CONSULTANCY_FEE,
    CardType::BEAUTY_CONTEST,
    CardType::INHERITANCE
};

class Deck
{
    
public:
    Card* cards[26];

    Deck()
    {
        for (int i = 0; i < 26; i++)
        {
            cards[i] = NULL;
        }
    }

    void initialzeDeck()
    {
        for (int i = 0; i < 26; i++)
        {
            CardType cardType = allCardTypes[i];
            cards[i] = new Card(card_descriptions[i], cardType);
        }
    }

    int generateCard()
    {
        return rand() % 26;
    }
};