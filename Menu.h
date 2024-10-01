//311318075
//shanibasteker@gmail.com

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>  // For setprecision
#include <sstream>  // For ostringstream

#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

bool isMouseOverText(const Text& text, RenderWindow& window)
{
	Vector2i mousePosition = Mouse::getPosition(window); // Get the current mouse position
	FloatRect bounds = text.getGlobalBounds(); // Get the global bounds of the text
	return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)); // Check if the mouse position is within the bounds of the text
}

bool isMouseOver(const Sprite& sprite, RenderWindow& window)    // Check if Mouse is Over a Button
{
    Vector2i mousePosition = Mouse::getPosition(window); // Get the current mouse position
    FloatRect bounds = sprite.getGlobalBounds(); // Get the global bounds of the sprite
    return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)); // Check if the mouse position is within the bounds of the sprite
}

string wrapText(const std::string& input, unsigned int lineLength)
{
	std::istringstream stream(input); // Create a stream from the input string
	std::string word;
	std::string result;
	unsigned int currentLineLength = 0;

	while (stream >> word) // Read words from the stream
	{
		// If the word itself is longer than the lineLength, push it to a new line
		if (word.length() > lineLength)
		{
			// If result isn't empty, add a newline before adding the long word
			if (!result.empty())
			{
				result += '\n';
			}
			result += word; // Add the long word directly to the result
			currentLineLength = 0; // Reset line length counter
		}
		else
		{
			// Check if adding this word would exceed the line length
			if (currentLineLength + word.length() > lineLength)
			{
				// If it does, add a newline and reset the length counter
				if (!result.empty())
				{
					result += '\n';
				}
				result += word; // Start a new line with this word
				currentLineLength = word.length(); // Reset to the current word's length
			}
			else
			{
				// If there's space, add the word to the current line
				if (currentLineLength > 0)
				{
					result += ' '; // Add a space if it's not the first word
				}
				result += word;
				currentLineLength += word.length() + 1; // Update the length (include the space)
			}
		}
	}

	return result;
}

class Menu
{
private:

	Texture bg_Tex;      // Create a texture for the background
	Sprite bgSprite;    // Create a sprite for the background

	RenderWindow* window;

public:
	Menu(RenderWindow* win);
	~Menu();

	void RenderMainMenu(bool& running);
	void RenderPlayerMenu(bool& running, int& players);
	void RenderControls(bool& runningMain);
	void RenderPropertiesMenu(bool& runningGame, const vector<string>& ownedProperties, string& selectedProperty);
};

Menu::Menu(RenderWindow* win)
{
	window = win;

	bg_Tex.loadFromFile("//home//user//Desktop//New folder//images//mainMenu.png"); // Load a texture for the background
	bgSprite.setTexture(bg_Tex);    // Load the texture onto the Sprite
	bgSprite.setScale(0.32, 0.32);
}

Menu::~Menu()
{
	window = NULL;
}

void Menu::RenderMainMenu(bool& runningGame)
{
	bool running = true;

	Texture start_button_tex;      // Create a texture for the Start Button
	Sprite start_button;    // Create a sprite for the Start Button

	Texture exit_button_tex;      // Create a texture for the Exit Button
	Sprite exit_button;    // Create a sprite for the Exit Button

	Texture controls_button_tex;      // Create a texture for the Exit Button
	Sprite controls_button;    // Create a sprite for the Exit Button

	start_button_tex.loadFromFile("//home//user//Desktop//New folder//images//start.png");
	exit_button_tex.loadFromFile("//home//user//Desktop//New folder//images//quit.png");
	controls_button_tex.loadFromFile("//home//user//Desktop//New folder//images//controls.png");

	start_button.setTexture(start_button_tex);
	exit_button.setTexture(exit_button_tex);
	controls_button.setTexture(controls_button_tex);

	start_button.setScale(0.3, 0.3);
	exit_button.setScale(0.3, 0.3);
	controls_button.setScale(0.3, 0.3);

	start_button.setPosition(420 , 480 );
	exit_button.setPosition(1150 , 0 );
	controls_button.setPosition(430, 580);

	while (running)
	{
		Event event;
		if (window->pollEvent(event))
		{
			if (event.type == Event::Closed) // Check if window is closed
			{
				cout << "Exiting Main Menu!" << endl;
				running = false;
				runningGame = false;
				window->close();
			}

			else if (event.type == Event::KeyPressed) // Check if key is pressed (X key to exit)
			{
				if (event.key.code == Keyboard::X)
				{
					cout << "Exiting Main Menu!" << endl;
					running = false;
					runningGame = false;
					window->close();
				}
			}

			else if (event.type == Event::MouseButtonPressed) // Check if mouse button is pressed
			{
			    if (event.mouseButton.button == Mouse::Left) // Check if left mouse button is pressed
			    { 
			        if (isMouseOver(exit_button, *window))   // Check if mouse is over the exit button
			        {
			            cout << "Exit Button Clicked!" << endl;
						running = false;
						runningGame = false;
			            window->close();
			        }		        
			
			        else if (isMouseOver(start_button, *window))   // Check if mouse is over the Play button
			        {
			            cout << "Play Button Clicked!" << endl;
						running = false;					
			        }

					else if (isMouseOver(controls_button, *window))   // Check if mouse is over the Play button
					{
						cout << "Controls Button Clicked!" << endl;
						running = false;
						RenderControls(runningGame);
					}
			    }
			}
		}

		window->clear();     // Clear screen
		window->draw(bgSprite);  // Draw Background
		window->draw(start_button);
		window->draw(controls_button);
		window->draw(exit_button);
		window->display();   // Update the window
	}
	
}

void Menu::RenderPlayerMenu(bool& runningGame, int& players)
{
	bool running = true;

	bg_Tex.loadFromFile("//home//user//Desktop//New folder//images//playerMenu.png"); // Load a texture for the background
	bgSprite.setTexture(bg_Tex);    // Load the texture onto the Sprite

	Texture buttonTex[7];
	Sprite button[7];

	int x = 500;
	int y = 220;

	for (int i = 0; i < 7; i++)
	{
		buttonTex[i].loadFromFile("//home//user//Desktop//New folder//images//" + to_string(i + 2) + "players.png");
		button[i].setTexture(buttonTex[i]);
		button[i].setScale(0.25, 0.25);
		button[i].setPosition(x, y);
		y += 70;
	}

	while (running)
	{
		Event event;
		if (window->pollEvent(event))
		{
			if (event.type == Event::Closed) // Check if window is closed
			{
				cout << "Exiting Main Menu!" << endl;
				running = false;
				runningGame = false;
				window->close();
			}

			else if (event.type == Event::KeyPressed) // Check if key is pressed (X key to exit)
			{
				if (event.key.code == Keyboard::X)
				{
					cout << "Exiting Main Menu!" << endl;
					running = false;
					runningGame = false;
					window->close();
				}
			}

			else if (event.type == Event::MouseButtonPressed) // Check if mouse button is pressed
			{
				if (event.mouseButton.button == Mouse::Left) // Check if left mouse button is pressed
				{
					if (isMouseOver(button[0], *window))   // Check if mouse is over the button
					{					
						running = false;
						players = 2;
					}

					else if (isMouseOver(button[1], *window))   // Check if mouse is over the button
					{
						running = false;
						players = 3;
					}

					else if (isMouseOver(button[2], *window))   // Check if mouse is over the button
					{				
						running = false;
						players = 4;
					}

					else if (isMouseOver(button[3], *window))   // Check if mouse is over the button
					{					
						running = false;
						players = 5;
					}

					else if (isMouseOver(button[4], *window))   // Check if mouse is over the button
					{					
						running = false;
						players = 6;
					}

					else if (isMouseOver(button[5], *window))   // Check if mouse is over the button
					{			
						running = false;
						players = 7;
					}

					else if (isMouseOver(button[6], *window))   // Check if mouse is over the button
					{				
						running = false;
						players = 8;
					}
			
				}
			}
		}

		window->clear();     // Clear screen
		window->draw(bgSprite);  // Draw Background

		for (int i = 0; i < 7; i++)
		{
			window->draw(button[i]);
		}

		window->display();   // Update the window
	}

}

void Menu::RenderControls(bool& runningMain)
{
	bool running = true;

	bg_Tex.loadFromFile("//home//user//Desktop//New folder//images//controlsMenu.png"); // Load a texture for the background
	bgSprite.setTexture(bg_Tex);    // Load the texture onto the Sprite

	Texture b1_tex;      // Create a texture for the Button
	Sprite b1;    // Create a sprite for the Button

	Texture b2_tex;      // Create a texture for the Button
	Sprite b2;    // Create a sprite for the Button

	b1_tex.loadFromFile("//home//user//Desktop//New folder//images//start.png");
	b2_tex.loadFromFile("//home//user//Desktop//New folder//images//quit.png");

	b1.setTexture(b1_tex);
	b2.setTexture(b2_tex);

	b1.setScale(0.3, 0.3);
	b2.setScale(0.3, 0.3);

	b1.setPosition(450, 580);
	b2.setPosition(1150, 0);

	while (running)
	{
		Event event;
		if (window->pollEvent(event))
		{
			if (event.type == Event::Closed) // Check if window is closed
			{
				cout << "Exiting Main Menu!" << endl;
				running = false;
				runningMain = false;
				window->close();
			}

			else if (event.type == Event::KeyPressed) // Check if key is pressed (X key to exit)
			{
				if (event.key.code == Keyboard::X)
				{
					cout << "Exiting Main Menu!" << endl;
					running = false;
					runningMain = false;
					window->close();
				}
			}

			else if (event.type == Event::MouseButtonPressed) // Check if mouse button is pressed
			{
				if (event.mouseButton.button == Mouse::Left) // Check if left mouse button is pressed
				{
					if (isMouseOver(b1, *window))   // Check if mouse is over the button
					{
						running = false;
					}

					else if (isMouseOver(b2, *window))   // Check if mouse is over the button
					{
						running = false;
						runningMain = false;
						window->close();
					}
				}
			}

			window->clear();     // Clear screen
			window->draw(bgSprite);  // Draw Background
			window->draw(b1);
			window->draw(b2);
			window->display();   // Update the window
		}

	}
}

void Menu::RenderPropertiesMenu(bool& runningGame, const vector<string>& ownedProperties, string& selectedProperty)
{
	bool running = true;

	// Load a font for displaying text
	Font font;
	if (!font.loadFromFile("//home//user//Desktop//New folder//images//montserrat//Montserrat-Black.otf"))  // Ensure you have a font file available
	{
		cout << "Error loading font!" << endl;
		return;
	}

	Texture b2_tex;      // Create a texture for the Button
	Sprite b2;    // Create a sprite for the Button

	b2_tex.loadFromFile("//home//user//Desktop//New folder//images//quit.png");
	b2.setTexture(b2_tex);
	b2.setScale(0.3, 0.3);
	b2.setPosition(1150, 0);

	
	bg_Tex.loadFromFile("//home//user//Desktop//New folder//images//propertyMenu.png");
	bgSprite.setTexture(bg_Tex);
	

	// Create a vector of Text objects to represent each property
	vector<Text> propertyTexts(ownedProperties.size());

	int x = 200; // Initial x position for property text
	int y = 300; // Initial y position for property text

	for (size_t i = 0; i < ownedProperties.size(); i++)
	{
		propertyTexts[i].setFont(font); // Set the font for each property text
		propertyTexts[i].setString(ownedProperties[i]);  // Set the property name as the text
		propertyTexts[i].setCharacterSize(24);  // Font size
		propertyTexts[i].setFillColor(Color::White);  // Text color

		// Position the text on the screen
		propertyTexts[i].setPosition(x, y);

		// Adjust positions (e.g., for a vertical layout)
		y += 50;  // Move down for the next property
		if (y > 600)  // If going off the bottom, move right and reset y
		{
			y = 300;
			x += 300;
		}
	}

	// Main loop for the property menu
	while (running)
	{
		Event event;
		if (window->pollEvent(event))
		{
			if (event.type == Event::Closed)  // Close the menu
			{
				running = false;
				runningGame = false;
				window->close();
			}

			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (isMouseOver(b2, *window))   // Check if mouse is over the button
					{
						running = false;
						return;
					}

					// Check if the mouse is over any of the property text items
					for (size_t i = 0; i < ownedProperties.size(); i++)
					{
						if (isMouseOverText(propertyTexts[i], *window))  // If mouse is over a property text
						{
							selectedProperty = ownedProperties[i];
							cout << "Selected Property: " << selectedProperty << endl;
							running = false;  // Exit the property menu
						}
					}

					
				}
			}
		}

		window->clear();
		window->draw(bgSprite);  
		window->draw(b2);

		// Draw all the property texts
		for (const auto& text : propertyTexts)
		{
			window->draw(text);
		}

		window->display();
	}
};