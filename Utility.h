//311318075
//shanibasteker@gmail.com

#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player;

class Utility	// Utility Class
{
private:
    string name;		// Stores Utility Name
    int price;			// Stores Utility Price
    Player* owner;		// Stores Utility Owner

public:
    int position;       // Stores Postition

    // Constructor
    Utility(string name, int price, int position)
        : name(name), price(price), owner(nullptr) , position(position){}

    // Calculates Rent for Utility
    int calculateRent(int diceRoll, int numUtilitiesOwned)
    {
        if (numUtilitiesOwned == 1)
            return 4 * diceRoll;	// Rent with one utility
        else
            return 10 * diceRoll;	// Rent with two utilities
    }

    // Getter Functions
    int getPrice() const	// Returns the price of the utility
    {
        return price;
    }

    Player* getOwner() const	// Returns the owner of the utility
    {
        return owner;
    }

    // Setter Functions
    void setOwner(Player* owner)	// Sets the owner of the utility
    {
        this->owner = owner;
    }

    string getName() const	// Returns the name of the utility
    {
        return name;
    }
};
