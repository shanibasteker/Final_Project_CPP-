//311318075
//shanibasteker@gmail.com

#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player;

Vector2f getBoardPosition(int position);

Vector2f getTagPosition(int position)
{
    // Define coordinates for all 40 board spaces
    static Vector2f boardPositions[] = {
        {950, 680},     // GO
        {875, 680},
        {815, 680},
        {758, 680},
        {700, 680},
        {640, 680},
        {580, 680},
        {520, 680},
        {460, 680},
        {404, 680},
        {300, 700},     // Visiting Jail
        {315, 596},
        {315, 535},
        {315, 475},
        {315, 420},
        {315, 360},
        {315, 300},
        {315, 240},
        {315, 180},
        {315, 124},
        {330, 45},      // Free Parking
        {404, 40},
        {460, 40},
        {520, 40},
        {580, 40},
        {640, 40},
        {700, 40},
        {760, 40},
        {820, 40},
        {876, 40},
        {950, 40},      // Goto Jail
        {965, 124},
        {965, 180},
        {965, 240},
        {965, 300},
        {965, 360},
        {965, 420},
        {965, 480},
        {965, 540},
        {965, 596},
    };

    return boardPositions[position];
}

class Street	// Street Class
{
private:
	int colorGroup;		// Stores Color Group
	string name;		// Stores Street Name
	int price;			// Stores Street Price
	int rent;			// Stores Street Rent
	int housePrice;		// Stores House Price
	int numHouses;		// Stores Number of Houses Built
    Player* owner;      // Stores Owner Details

public:
    bool hasHotel;		// Stores Hotel Status
    int position;       // Stores Postition
    Sprite house[4];
    Texture tex[4];
  
    Street(string name, int colorGroup, int price, int rent, int housePrice, int position): name(name), colorGroup(colorGroup), price(price), rent(rent), housePrice(housePrice), numHouses(0), hasHotel(false) ,position(position)
    {
        for (int i = 0; i < 4; i++) {
            tex[i].loadFromFile("//home//user//Desktop//New folder//images//house.png");

            house[i].setTexture(tex[i]);
            Vector2u textureSize = tex[i].getSize();  // Get the size of the texture
            house[i].setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center
            house[i].setScale(0.05, 0.05);
            house[i].setPosition(3000, 3000);
        }
        owner=NULL; 
        setHouse();
    }

    void setHouse()
    {
        Vector2f pos = getBoardPosition(position);

        float x = pos.x;
        float y = pos.y;

        if (y == 680)
        {
            y -= 45;
            x -= 19;
        }

        else if (x == 315)
        {
            for (int i = 0; i < 4; i++)
                house[i].setRotation(90);
            y -= 22;
            x += 48;
        }

        else if (y == 40)
        {
            for (int i = 0; i < 4; i++)
                house[i].setRotation(180);
            y += 42;
            x -= 20;
        }

        else if (x == 965)
        {
            for (int i = 0; i < 4; i++)
                house[i].setRotation(270);

            y += 17;
            x -= 50;
        }

        for (int i = 0; i < 4; i++)
        {
            house[i].setPosition(x, y);         
        }
    }

    void buildHouse()
    {

        if (numHouses < 4)
            numHouses++;

        else
            hasHotel = true;
    }

    int calculateRent() // Calculates Rent
    {
        int currRent = rent;
        if (hasHotel)
            currRent = currRent + 4 * housePrice + 100;
        else if (numHouses >= 1)
            currRent = currRent + rent * pow(2, numHouses);
        return currRent;
    }

    // Getter Functions
    int getPrice() const
    {
        return price;
    }

    int getNumHouses() const
    {
        return numHouses;
    }

    int getHousePrice() const
    {
        return housePrice;
    }

    string getName() const
    {
        return name;
    }

    Player* getOwner()
    {
        return owner;
    }

    // Setter Functions
    void setOwner(Player* owner)
    {
        this->owner = owner;
    }

};