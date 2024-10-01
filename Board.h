//311318075
//shanibasteker@gmail.com

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Street.h"
#include "Utility.h"
#include "Railroad.h"

using namespace std;

class Board
{
public:
    vector<Street*> streets;      // List of streets   
    vector<Utility*> utilities;   // List of utilities 
    vector<Railroad*> railroads;  // List of railroads 
    vector<string> locationNames; // List of board locations

    // Constructor
    Board()
    {
        streets.clear();
        utilities.clear();
        railroads.clear();
        locationNames.clear();
    }

    // Destructor
    ~Board()
    {
        // Clean dynamically allocated memory for streets
        for (size_t i = 0; i < streets.size(); i++)
            delete streets[i];

        // Clean dynamic  memory for utilities
        for (size_t i = 0; i < utilities.size(); i++)
            delete utilities[i];

        // Clean up dynamic memory for railroads
        for (size_t i = 0; i < railroads.size(); i++)
            delete railroads[i];
    }

    // Initialize the board with properties
    void initializeBoard()
    {
        // Clear the vectors before initializing
        streets.clear();
        utilities.clear();
        railroads.clear();
        locationNames.clear();

        // Initialize location names
        locationNames = {
            "GO",
            "Mediterranean Avenue",
            "Community Chest",
            "Baltic Avenue",
            "Income Tax",
            "Reading Railroad",
            "Oriental Avenue",
            "Chance",
            "Vermont Avenue",
            "Connecticut Avenue",
            "Jail",
            "St. Charles Place",
            "Electric Company",
            "States Avenue",
            "Virginia Avenue",
            "Pennsylvania Railroad",
            "St. James Place",
            "Community Chest",
            "Tennessee Avenue",
            "New York Avenue",
            "Free Parking",
            "Kentucky Avenue",
            "Chance",
            "Indiana Avenue",
            "Illinois Avenue",
            "B. & O. Railroad",
            "Atlantic Avenue",
            "Ventnor Avenue",
            "Water Works",
            "Marvin Gardens",
            "Go to Jail",
            "Pacific Avenue",
            "North Carolina Avenue",
            "Community Chest",
            "Pennsylvania Avenue",
            "Short Line",
            "Chance",
            "Park Place",
            "Luxury Tax",
            "Boardwalk",
        };

        // Brown Properties
        streets.push_back(new Street("Mediterranean Avenue", 1, 60, 2, 50, 1));
        streets.push_back(new Street("Baltic Avenue", 1, 60, 4, 50, 3));

        // Light Blue Properties
        streets.push_back(new Street("Oriental Avenue", 2, 100, 6, 50, 6));
        streets.push_back(new Street("Vermont Avenue", 2, 100, 6, 50, 8));
        streets.push_back(new Street("Connecticut Avenue", 2, 120, 8, 50, 9));

        // Pink Properties
        streets.push_back(new Street("St. Charles Place", 3, 140, 10, 100, 11));
        streets.push_back(new Street("States Avenue", 3, 140, 10, 100, 13));
        streets.push_back(new Street("Virginia Avenue", 3, 160, 12, 100, 14));

        // Orange Properties
        streets.push_back(new Street("St. James Place", 4, 180, 14, 100, 16));
        streets.push_back(new Street("Tennessee Avenue", 4, 180, 14, 100, 18));
        streets.push_back(new Street("New York Avenue", 4, 200, 16, 100, 19));

        // Red Properties
        streets.push_back(new Street("Kentucky Avenue", 5, 220, 18, 150, 21));
        streets.push_back(new Street("Indiana Avenue", 5, 220, 18, 150, 23));
        streets.push_back(new Street("Illinois Avenue", 5, 240, 20, 150, 24));

        // Yellow Properties
        streets.push_back(new Street("Atlantic Avenue", 6, 260, 22, 150, 26));
        streets.push_back(new Street("Ventnor Avenue", 6, 260, 22, 150, 27));
        streets.push_back(new Street("Marvin Gardens", 6, 280, 24, 150, 29));

        // Green Properties
        streets.push_back(new Street("Pacific Avenue", 7, 300, 26, 200, 31));
        streets.push_back(new Street("North Carolina Avenue", 7, 300, 26, 200, 32));
        streets.push_back(new Street("Pennsylvania Avenue", 7, 320, 28, 200, 34));

        // Dark Blue Properties
        streets.push_back(new Street("Park Place", 8, 350, 35, 200, 37));
        streets.push_back(new Street("Boardwalk", 8, 400, 50, 200, 39));

        // Utilities
        utilities.push_back(new Utility("Electric Company", 150, 12));
        utilities.push_back(new Utility("Water Works", 150, 28));

        // Railroads
        railroads.push_back(new Railroad("Reading Railroad", 200, 5));
        railroads.push_back(new Railroad("Pennsylvania Railroad", 200, 15));
        railroads.push_back(new Railroad("B. & O. Railroad", 200, 25));
        railroads.push_back(new Railroad("Short Line", 200, 35));
    }

    // Find the position of a specific property
    int getPropertyPosition(const string& propertyName)
    {
        for (size_t i = 0; i < streets.size(); i++)
        {
            if (streets[i]->getName() == propertyName)
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    Street* getProperty(const string& propertyName)
    {
        for (size_t i = 0; i < streets.size(); i++)
        {
            if (streets[i]->getName() == propertyName)
            {
                return streets[i];
            }
        }
        return NULL;
    }

    // Get the position of Boardwalk
    int getBoardwalkPosition()
    {
        return getPropertyPosition("Boardwalk");
    }

    // Get the position of a specific railroad
    int getRailroadPosition(const string& railroadName)
    {
        for (size_t i = 0; i < railroads.size(); i++)
        {
            if (railroads[i]->getName() == railroadName)
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    // Get the nearest utility based on current position
    int findNearestUtility(int currentPosition)
    {
        int nearestUtility = 59;

        for (size_t i = 0; i < utilities.size(); i++)
        {
            if (abs(utilities[i]->position - currentPosition) <= abs(nearestUtility - currentPosition))
                nearestUtility = utilities[i]->position;
        }

        if (nearestUtility != 59)
            return nearestUtility;

        return 0;
    }

    // Get the nearest railroad based on current position
    int findNearestRailroad(int currentPosition)
    {
        int nearestRoad = 59;

        for (size_t i = 0; i < utilities.size(); i++)
        {
            if (abs(railroads[i]->position - currentPosition) <= abs(nearestRoad - currentPosition))
                nearestRoad = railroads[i]->position;
        }

        if (nearestRoad != 59)
            return nearestRoad;

        return 0;
    }

    Street* getStreet(int position)
    {
        int i;
        for (i = 0; i < streets.size(); i++)
        {
            if (streets[i]->position == position)
            {
                return streets[i];
            }
        }
        return NULL;
    }

    Utility* getUtility(int position)
    {
        int i;
        for (i = 0; i < utilities.size(); i++)
        {
            if (utilities[i]->position == position)
            {
                return utilities[i];
            }
        }
        return NULL;
    }

    Railroad* getRailroad(int position)
    {
        int i;
        for (i = 0; i < railroads.size(); i++)
        {
            if (railroads[i]->position == position)
            {
                return railroads[i];
            }
        }
        return NULL;
    }
};
