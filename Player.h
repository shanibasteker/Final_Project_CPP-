//311318075
//shanibasteker@gmail.com

#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Vector2f getBoardPosition(int position)
{
    // Define coordinates for all 40 board spaces
    static Vector2f boardPositions[] = {
        {950, 680},     // GO
        {875, 680},
        {815, 680},
        {755, 680},
        {700, 680},
        {640, 680},
        {580, 680},
        {520, 680},
        {460, 680},
        {400, 680},
        {300, 700},     // Visiting Jail
        {315, 600},
        {315, 535},
        {315, 475},
        {315, 420},
        {315, 360},
        {315, 300},
        {315, 240},
        {315, 180},
        {315, 120},
        {330, 45},      // Free Parking
        {400, 40},
        {460, 40},
        {520, 40},
        {580, 40},
        {640, 40},
        {700, 40},
        {760, 40},
        {820, 40},
        {880, 40},
        {950, 40},      // Goto Jail
        {965, 120},
        {965, 180},
        {965, 240},
        {965, 300},
        {965, 360},
        {965, 420},
        {965, 480},
        {965, 540},
        {965, 600},
    };

    return boardPositions[position];
}

class Player 
{
private:
    int ID;                             // Stores Player's ID
    int money;                          // Stores Player's Money
    int position;                       // Stores Player's Current Position on Board
    vector<Street*> ownedStreets;       // List of streets Owned
    vector<Utility*> ownedUtilities;    // List of utilities Owned
    vector<Railroad*> ownedRailroads;   // List of railroads Owned
    bool inJail;                        // Jail Status of the Player
    int jailTurns;                      // Number of Turns in Jail
    bool hasGetOutOfJailCard;           // "Get Out of Jail Free" Card Status

public:
    Texture texture;                    // Stores Texture
    Sprite sprite;                      // Stores Sprite
    int xPosition;                      // Stores Player's Current X Position
    int yPosition;                      // Stores Player's Current X Position

    // Constructor
    Player(int id) : ID(id), money(1500), position(0), inJail(false), jailTurns(0), hasGetOutOfJailCard(false)
    {
        initTexture();
        xPosition = 0;
        yPosition = 0;       
    }

    void initTexture()
    {
        string id = to_string(ID);
        string path = "//home//user//Desktop//New folder//images//player" + id + ".png";
        texture.loadFromFile(path);
        sprite.setTexture(texture);
        Vector2u textureSize = texture.getSize();  // Get the size of the texture
        sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center
        sprite.setScale(0.1, 0.1);
    }

    // Move Player
    void move(int steps) 
    {
        if ((position + steps) / 40 > 0)
        {
            money += 200;   // Pass Go
        }

        position = (position + steps) % 40;
        
        // Update sprite position based on board space
        Vector2f newPos = getBoardPosition(position);
        sprite.setPosition(newPos);
    }

    // Goto Position Player
    void moveTo(int pos)
    {
        position = pos;
    }

    // Buy a Street
    void buyStreet(Street* street) 
    {
        ownedStreets.push_back(street);
        money -= street->getPrice();
        street->setOwner(this);
    }

    // Buy a Utility
    void buyUtility(Utility* utility) 
    {
        ownedUtilities.push_back(utility);
        money -= utility->getPrice();
        utility->setOwner(this);
    }

    // Buy a Railroad
    void buyRailroad(Railroad* railroad) 
    {
        ownedRailroads.push_back(railroad);
        money -= railroad->getPrice();
        railroad->setOwner(this);
    }

    // Pay Rent
    void payRent(int amount) 
    {
        money -= amount;
    }

    // Send the Player to Jail
    void goToJail() 
    {
        inJail = true;
        jailTurns = 0;
    }

    // Release from Jail
    void releaseFromJail() 
    {
        inJail = false;
        jailTurns = 0;
    }

    // Add Money to Total
    void addMoney(int amount) 
    {
        money += amount;
    }

    // Check if the Player is Bankrupt
    bool isBankrupt() const 
    {
        return money <= 0;
    }

    void giveJailFreeCard()
    {
        hasGetOutOfJailCard = true;
    }

    void resetJailFreeCard()
    {
        hasGetOutOfJailCard = false;
    }

    // Getter Functions
    int getPosition() const // Get the Player's Current Position 
    {
        return position;
    }

    int getID() const // Get the Player's name
    {
        return ID;
    }

    int getMoney() const  // Get the Player's Money
    {
        return money;
    }

    
    int getNumStreets() const // Get the Number of Streets
    {
        return ownedStreets.size();
    }

    
    int getNumUtilities() const // Get the Number of Rtilities
    {
        return ownedUtilities.size();
    }

    int getNumRailroads() const // Get the Number of Railroads
    {
        return ownedRailroads.size();
    }

    vector<string> getOwnedProperties() const
    {
        vector<string> propertyList;

        // Add streets owned by the player
        for (const Street* street : ownedStreets)
        {
            propertyList.push_back(street->getName());        
        }

        return propertyList;
    }

};
