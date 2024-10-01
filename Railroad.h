//311318075
//shanibasteker@gmail.com

#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player;

class Railroad	// Railroad Class
{
private:
    string name;		// Stores Railroad Name
    int price;			// Stores Railroad Price
    Player* owner;		// Stores Railroad Owner

public:
    int position;       // Stores Postition

    // Constructor
    Railroad(string name, int price, int position)
        : name(name), price(price), owner(nullptr) ,position(position){}

    // Calculates Rent for Railroad
    int calculateRent(int numRailroadsOwned)
    {
        return 50 * numRailroadsOwned;
    }

    // Getter Functions
    int getPrice() const	// Returns the price of the railroad
    {
        return price;
    }

    Player* getOwner() const	// Returns the owner of the railroad
    {
        return owner;
    }

    // Setter Functions
    void setOwner(Player* owner)	// Sets the owner of the railroad
    {
        this->owner = owner;
    }

    string getName() const	// Returns the name of the railroad
    {
        return name;
    }
};
