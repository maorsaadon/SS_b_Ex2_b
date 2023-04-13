#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "player.hpp"
#include "card.hpp"

namespace ariel
{
	
	Player::Player(string name)
	{
		// Constructor that takes in a player name and initializes various properties
		if (name == "")
		{
			throw invalid_argument("put a name player");  // Throw an exception if the player name is empty
		}
		this->name = name;
		this->ownCardCount = 0;
		this->counterTurnWin = 0;
		this->onGame = false;
	}

	string Player::getName()
	{
		return this->name; // Return the name of the player
	}

	bool Player::pileIsEmpty()
	{
		return this->myPile.empty(); // Check if the player's pile of cards is empty
	}

	void Player::incOwnCardCount(int size)
	{
		this->ownCardCount += size; // Increment the number of cards owned by the player
	}

	void Player::placeBottom(Card card)
	{
		this->myPile.push_back(card); // Add a card to the bottom of the player's pile
	}

	bool Player::getOnGame()
	{
		return this->onGame; // Get the onGame status of the player
	}

	void Player::setOnGame(bool sign)
	{
		this->onGame = sign; // Set the onGame status of the player
	}

	int Player::cardesTaken()
	{
		return this->ownCardCount; // Return the number of cards taken by the player
	}

	int Player::stacksize()
	{
		return this->myPile.size(); // Return the size of the player's pile
	}

	int Player::getCounterTurnWin()
	{
		return this->counterTurnWin;  // Return the number of turns won by the player
	}

	int Player::incCounterTurnWin()
	{
		return this->counterTurnWin++; // Increment and return the number of turns won by the player
	}

	Card Player::play()
	{
		if (this->myPile.size() == 0)
		{
			throw invalid_argument("out of card"); // Throw an exception if the player has no cards left

		}

		Card drawnCard = this->myPile.at(0); // Draw a card from the top of the player's pile
		this->myPile.erase(this->myPile.begin()); // Remove the drawn card from the player's pile
		return drawnCard; // Return the drawn card
	}

};
