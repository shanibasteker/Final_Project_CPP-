//311318075
//shanibasteker@gmail.com

#pragma once

#include "Menu.h"
#include "Board.h"
#include "Player.h"
#include "Deck.h"

class Game
{

private:

	bool running;
	int mouse_x, mouse_y;

	int numPlayers;

	RenderWindow* window;
	Texture bg_Tex;      // Create texture for the background
	Sprite bgSprite;     // Create sprite for the background

	vector<Player*> players;
	bool playersPlaying[8];
	Board* board;
	Deck* deck;

	int turn;
	int diceRolls;
	bool rolledDoubles;

	Texture rollTex;
	Texture buyTex;
	Texture buildTex;
	Texture endTex;
	Texture forfeitTex;

	Sprite rollButton;
	Sprite buyButton;
	Sprite buildButton;
	Sprite endButton;
	Sprite forfeitButton;

	Texture playerBoxTex[8];
	Sprite playerBox[8];
	Text playerText[8];

	Texture propertyTagTex[40];
	Sprite propertyTag[40];

	int steps;

	Font font;
	Text message;
	bool displayMessage;

	string currentMessage;

	Menu* menu;

public:

	Game();
	~Game();
	void initialize();
	void initPlayers();
	void rollDice();
	void nextTurn();
	void handleLandEffect();
	void buyProperty();
	void buildHouses();
	void update();
	void ManageEvents();
	void renderHouses();
	void render();
	void clean();
	bool isRunning();
	void Ending();
	void Reset();

};

Game::Game()
{
	running = true;
	mouse_x = 0;
	mouse_y = 0;
	window = NULL;
	board = NULL;
	deck = NULL;
	turn = 0;
	diceRolls = 0;
	rolledDoubles = false;
	steps = 0;
	menu = NULL;
	numPlayers = 0;
	displayMessage = false;

}

Game:: ~Game()
{
	cout << "Game Ended!" << endl;
}

void Game::initialize()
{
	window = new RenderWindow(VideoMode(1280, 720), "Monopoly");
	window->setFramerateLimit(170);	// Set A Fixed FPS

	bg_Tex.loadFromFile("//home//user//Desktop//New folder//images//board.png"); // Load texture for the background
	bgSprite.setTexture(bg_Tex);    // Load texture onto the Sprite
	bgSprite.setScale(0.32, 0.32);

	rollTex.loadFromFile("//home//user//Desktop//New folder//images//rollButton.png");
	buyTex.loadFromFile("//home//user//Desktop//New folder//images//buyButton.png");
	buildTex.loadFromFile("//home//user//Desktop//New folder//images//buildButton.png");
	endTex.loadFromFile("//home//user//Desktop//New folder//images//endButton.png");
	forfeitTex.loadFromFile("//home//user//Desktop//New folder//images//forfiet.png");

	rollButton.setTexture(rollTex);
	buyButton.setTexture(buyTex);
	buildButton.setTexture(buildTex);
	endButton.setTexture(endTex);
	forfeitButton.setTexture(forfeitTex);

	Vector2u textureSize = rollTex.getSize();  // Get the size of the texture
	rollButton.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center

	textureSize = buyTex.getSize();  // Get the size of the texture
	buyButton.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center

	textureSize = buildTex.getSize();  // Get the size of the texture
	buildButton.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center

	textureSize = endTex.getSize();  // Get the size of the texture
	endButton.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center

	textureSize = forfeitTex.getSize();  // Get the size of the texture
	forfeitButton.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center

	rollButton.setScale(0.32, 0.32);
	buyButton.setScale(0.32, 0.32);
	buildButton.setScale(0.32, 0.32);
	endButton.setScale(0.32, 0.32);
	forfeitButton.setScale(0.32, 0.32);

	rollButton.setPosition(1140, 130);
	buyButton.setPosition(1140, 200);
	buildButton.setPosition(1140, 270);
	endButton.setPosition(1140, 340);
	forfeitButton.setPosition(1140, 410);

	menu = new Menu(window);
	menu->RenderMainMenu(running);

	if (running)
		menu->RenderPlayerMenu(running, numPlayers);

	initPlayers();
	board = new Board();
	board->initializeBoard();

	turn = 0;

	int x = 140;
	int y = 120;

	for (size_t i = 0; i < players.size(); i++)
	{
		string path = "//home//user//Desktop//New folder//images//" + to_string(i + 1) + ".png";
		playerBoxTex[i].loadFromFile(path);
		playerBox[i].setTexture(playerBoxTex[i]);

		textureSize = playerBoxTex[i].getSize();  // Get the size of the texture
		playerBox[i].setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center

		playerBox[i].setPosition(x + 100, y);

		playerBox[i].setScale(0.3, 0.3);
		playerBox[i].setPosition(x, y);
		y += 60;
	}

	for (int i = 0; i < 40; i++)
	{
		propertyTagTex[i].loadFromFile("//home//user//Desktop//New folder//images//nothing2.png");
		propertyTag[i].setTexture(propertyTagTex[i]);
		propertyTag[i].setScale(0.01, 0.01);

		textureSize = propertyTagTex[i].getSize();  // Get the size of the texture
		propertyTag[i].setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);  // Set origin to center

		Vector2f newPos = getTagPosition(i);
		
		if (i < 10)
		{
			newPos.y -= 65;
		}

		else if (i < 20)
		{
			newPos.x += 70;
			propertyTag[i].setRotation(90);
		}

		else if (i < 30)
		{
			newPos.y += 65;		
		}

		else
		{
			newPos.x -= 70;
			propertyTag[i].setRotation(90);
		}

		propertyTag[i].setPosition(newPos);

	}
	string originalMessage = "Player " + to_string(turn+1) + "'s Turn!";
	string wrappedMessage = wrapText(originalMessage, 16);

	font.loadFromFile("//home//user//Desktop//New folder//images//montserrat//Montserrat-Black.otf");
	message.setFont(font);
	message.setString(wrappedMessage);          // Set the string to be displayed
	message.setCharacterSize(20);          // Set the character size
	message.setFillColor(Color::White);    // Set the fill color
	message.setPosition(1050, 500);        // Change these values to position as desired

	x = 60;
	y = 110;

	for (size_t i = 0; i < players.size(); i++)
	{	
		playerText[i].setFont(font);
		string data = "Player " + to_string(i+1) + " -- " + to_string(players[i]->getMoney());
		playerText[i].setString(data);          // Set the string to be displayed
		playerText[i].setCharacterSize(20);          // Set the character size
		playerText[i].setFillColor(Color::Black);    // Set the fill color
		playerText[i].setPosition(x, y);
		y += 60;
	}

	deck = new Deck();
	deck->initialzeDeck();
	
}

void Game::initPlayers()
{
	int x = 940;
	int y = 640;

	for (int i = 0; i < numPlayers; i++)
	{
		if (i + 1 == 5)
		{
			x = 970;
			y = 640;
		}		
		players.push_back(new Player(i+1));		
		players[i]->sprite.setPosition(x,y);
		y += 20;
	}

	for (int i = 0; i < numPlayers; i++)
		playersPlaying[i] = true;
}

void Game::rollDice()
{
	int dice1 = 1 + rand() % 6;
	int dice2 = 1 + rand() % 6;
	steps = dice1 + dice2;

	if (dice1 == dice2)
		rolledDoubles = true;
	
	cout << "Player " << turn << " Rolled " << dice1 << " and " << dice2 << endl;
	
	players[turn]->move(steps);
	cout << "Player " << turn << " Landed On: " << board->locationNames[players[turn]->getPosition()] << endl;
	currentMessage += " Player " + to_string(turn+1) + " Landed On : " + board->locationNames[players[turn]->getPosition()]+ " ";


}

void Game::handleLandEffect()
{
	
	if (players[turn]->getPosition() == 0) // Landed on GO
	{
		players[turn]->addMoney(200);  // Collect $200 for passing GO
		currentMessage += " Landed on Go. Recieve $200! ";
	}

	else if(players[turn]->getPosition() == 4) 
	{
		players[turn]->payRent(200);  // Pay $200 for Tax
		currentMessage += " Pay $200 Tax! ";
	}

	else if (players[turn]->getPosition() == 38) 
	{
		players[turn]->payRent(100);  // Pay $100 for Tax
		currentMessage += " Pay $100 Tax! ";
	}

	else if (players[turn]->getPosition() == 2 || players[turn]->getPosition() == 7 || players[turn]->getPosition() == 17 || players[turn]->getPosition() == 22 || players[turn]->getPosition() == 33 || players[turn]->getPosition() == 36)
	{
		int drawCard = deck->generateCard();
		deck->cards[drawCard]->applyEffect(players[turn], *board, players);
		currentMessage += " Draw Card! " + deck->cards[drawCard]->getDescription() + " ";
	}

	Street* street = board->getStreet(players[turn]->getPosition());
	Utility* utility = board->getUtility(players[turn]->getPosition());
	Railroad* railroad = board->getRailroad(players[turn]->getPosition());

	Player* owner = NULL;

	if (street != NULL)
	{
		owner = street->getOwner();

		if (owner != NULL)
		{
			int rent = street->calculateRent();
			players[turn]->payRent(rent);
			owner->addMoney(rent);
			currentMessage += " Pay Rent: " + to_string(rent) + " ";
		}
	}

	else if (utility != NULL)
	{
		owner = utility->getOwner();

		if (owner != NULL)
		{
			int count = owner->getNumUtilities();
			int rent = utility->calculateRent(steps, count);
			players[turn]->payRent(rent);
			owner->addMoney(rent);
			currentMessage += " Pay Rent: " + to_string(rent) + " ";
		}
	}

	else if (railroad != NULL)
	{
		owner = railroad->getOwner();

		if (owner != NULL)
		{
			int count = owner->getNumRailroads();
			int rent = railroad->calculateRent(count);
			players[turn]->payRent(rent);
			owner->addMoney(rent);
			currentMessage += " Pay Rent: " + to_string(rent) + " ";
		}
	}

	cout << "Player " << turn << " Money: " << players[turn]->getMoney() << endl;
}

void Game::nextTurn()
{
	 turn = (turn + 1) % players.size(); // Move to the next player
 		int checkEnd = 0;
  	for(size_t i=0; i<players.size(); i++) 
  		{ 
	if(playersPlaying[i] == true) 
	checkEnd++;
  		} 
	 		if(checkEnd == 1) 
	 		{
		 running = false;
		  return;
		}
		   if (!playersPlaying[turn])
		    nextTurn(); 
			cout << "Player " << turn << "'s Turn" << endl;
}


void Game::buyProperty()
{
	Street* street = board->getStreet(players[turn]->getPosition());
	Utility* utility = board->getUtility(players[turn]->getPosition());
	Railroad* railroad = board->getRailroad(players[turn]->getPosition());

	if (street != NULL)
	{
		if (street->getOwner() == NULL)
		{
			if (players[turn]->getMoney() >= street->getPrice())
			{
				players[turn]->buyStreet(street);
				string path = "//home//user//Desktop//New folder//images//" + to_string(turn + 1) + ".png";
				propertyTagTex[street->position].loadFromFile(path);
				propertyTag[street->position].setTexture(propertyTagTex[street->position]);
				propertyTag[street->position].setScale(0.08, 0.08);

			}
		}
	}

	else if (utility != NULL)
	{
		if (utility->getOwner() == NULL)
		{
			if (players[turn]->getMoney() >= utility->getPrice())
			{
				players[turn]->buyUtility(utility);
				string path = "//home//user//Desktop//New folder//images//" + to_string(turn + 1) + ".png";
				propertyTagTex[utility->position].loadFromFile(path);
				propertyTag[utility->position].setTexture(propertyTagTex[utility->position]);
				propertyTag[utility->position].setScale(0.08, 0.08);
			}
		}
	}

	else if (railroad != NULL)
	{
		if (railroad->getOwner() == NULL)
		{
			if (players[turn]->getMoney() >= railroad->getPrice())
			{
				players[turn]->buyRailroad(railroad);
				string path = "//home//user//Desktop//New folder//images//" + to_string(turn + 1) + ".png";
				propertyTagTex[railroad->position].loadFromFile(path);
				propertyTag[railroad->position].setTexture(propertyTagTex[railroad->position]);
				propertyTag[railroad->position].setScale(0.08, 0.08);
			}
		}
	}	
		
}

void Game::buildHouses()
{
	string selected = "NULL";
	menu->RenderPropertiesMenu(running,players[turn]->getOwnedProperties(), selected);
	
	
	if (selected != "NULL")
	{
		Street* temp = board->getProperty(selected);
		cout << "RENT: " << temp->calculateRent() << endl;
		temp->buildHouse();
		temp->getOwner()->payRent(temp->getHousePrice());

		cout << "RENT: " << temp->calculateRent() << endl;
	}
	
}


void Game::update()
{
	for (size_t i = 0; i < players.size(); i++)
	{
		string data = "Player " + to_string(i + 1) + " -- " + to_string(players[i]->getMoney());
		playerText[i].setString(data);          // Set the string to be displayed		
	}

	string originalMessage = "Player " + to_string(turn + 1) + "'s Turn!" + currentMessage;
	string wrappedMessage = wrapText(originalMessage, 16);
	
	message.setString(wrappedMessage);          // Set the string to be displayed

	
}

void Game::ManageEvents()
{
	Event event;
	if (window->pollEvent(event))
	{
		if (event.type == Event::Closed) // Check if window is closed
		{
			cout << "Exiting Game!" << endl;
			running = false;
			window->close();
		}

		else if (event.type == Event::KeyPressed) // Check if key is pressed (X key to exit)
		{
			if (event.key.code == Keyboard::X)
			{
				cout << "Exiting Game!" << endl;
				running = false;
				window->close();
			}		
		}

		else if (event.type == Event::MouseButtonPressed) // Check if mouse button is pressed
		{
			if (event.mouseButton.button == Mouse::Left) // Check if left mouse button is pressed
			{
				// Get mouse click coordinates
				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;

				// Print mouse click coordinates
				cout << "Mouse Clicked at: (" << mouseX << ", " << mouseY << ")" << endl;

				if (isMouseOver(rollButton, *window))   // Check if mouse is over the roll button
				{
					if (diceRolls == 0 || rolledDoubles == true)
					{
						rolledDoubles = false;
						cout << "Roll Dice Button Clicked!" << endl;
						rollDice();
						handleLandEffect();
						diceRolls++;
					}				
				}

				else if (isMouseOver(endButton, *window))   // Check if mouse is over the end turn button
				{
					if (diceRolls > 0)
					{
						cout << "End Turn Button Clicked!" << endl;
						nextTurn();
						diceRolls = 0;
						rolledDoubles = false;
						currentMessage = "";
					}					
				}

				else if (isMouseOver(buyButton, *window))   // Check if mouse is over the buy button
				{					
					{
						cout << "Buy Button Clicked!" << endl;
						buyProperty();
					
					}
				}

				else if (isMouseOver(buildButton, *window))   // Check if mouse is over the buy button
				{
					{
						cout << "Build Button Clicked!" << endl;
						buildHouses();
					}
				}

				else if (isMouseOver(forfeitButton, *window))   // Check if mouse is over the buy button
				{
					
						cout << "Forfeit Button Clicked!" << endl;
						playersPlaying[turn] = false;
						nextTurn();
						diceRolls = 0;
						rolledDoubles = false;
						currentMessage = "";
					
				}
			}
		}
	}

}

void Game::renderHouses()
{
	vector<Street*> st = board->streets;

	for (size_t i = 0; i < st.size(); i++)
	{
		if(st[i]->getNumHouses() > 0)
			window->draw(st[i]->house[0]);

		Vector2f pos = getBoardPosition(st[i]->position);
		float x = pos.x;
		float y = pos.y;
		if (y == 680)
		{
			y -= 45;
			x -= 19;
			for (int j = 1; j < st[i]->getNumHouses(); j++)
			{
				x += 12;
				st[i]->house[j].setPosition(x, y);
				window->draw(st[i]->house[j]);
			}
		}

		else if (x == 315)
		{
			y -= 22;
			x += 48;
			for (int j = 1; j < st[i]->getNumHouses(); j++)
			{
				y += 12;
				st[i]->house[j].setPosition(x, y);
				window->draw(st[i]->house[j]);
			}
		}

		else if (y == 40)
		{
			y += 42;
			x -= 20;
			for (int j = 1; j < st[i]->getNumHouses(); j++)
			{
				x += 12;
				st[i]->house[j].setPosition(x, y);
				window->draw(st[i]->house[j]);
			}
		}

		else if (x == 965)
		{
			y += 17;
			x -= 50;
			for (int j = 1; j < st[i]->getNumHouses(); j++)
			{
				y -= 12;
				st[i]->house[j].setPosition(x, y);
				window->draw(st[i]->house[j]);
			}
		}
	}
}

void Game::render()
{
	window->clear();     // Clear screen
	window->draw(bgSprite);  // Draw Background

	window->draw(rollButton);  
	window->draw(buyButton);
	window->draw(buildButton);
	window->draw(endButton);
	window->draw(forfeitButton);

	window->draw(message);
	
	for (size_t i = 0; i < players.size(); i++) 
	{
		if (!playersPlaying[i])
			continue;

		window->draw(players[i]->sprite);
		window->draw(playerBox[i]);
		window->draw(playerText[i]);
	}

	for (int i = 0; i < 40; i++)
	{
		if (i == 0 || i == 10 || i == 20 || i == 30)
			continue;

		window->draw(propertyTag[i]);
	}

	renderHouses();
		
	
	  // Draw Message
	window->display();   // Update the window
}

void Game::clean()
{
	delete window;
	
	window = NULL;

	cout << "Game Cleaned!" << endl;
}

bool Game::isRunning()
{
	return running;
}

void Game::Ending()
{
	render();

	bool run = true;

	while (run)
	{
		Event event;
		if (window->pollEvent(event))
		{
			if (event.type == Event::Closed) // Check if window is closed
			{
				cout << "Exiting Game!" << endl;
				run = false;
				running = false;
			}

			else if (event.type == Event::KeyPressed) // Check if key is pressed (X key to exit)
			{
				if (event.key.code == Keyboard::X)
				{
					cout << "Exiting Game!" << endl;
					run = false;
					running = false;
				}

				if (event.key.code == Keyboard::Enter)
				{
					cout << "Restarting Game!" << endl;
					run = false;
					Reset();
				}
			}
		}
	}
}

void Game::Reset()
{
	clean();

	running = true;
	mouse_x = 0;
	mouse_y = 0;
	window = NULL;
	//menu = NULL;

	initialize();
}
