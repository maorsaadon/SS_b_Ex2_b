#include "card.hpp"
using namespace std;

namespace ariel{
	// Constructor that initializes the suit and value of the card
	Card::Card (int value, string suit)
	{
		this->suit = suit;
		this->value = value;
	}
	
	// Getter method for the suit of the card
	string Card::getSuit() { return this->suit; }
	
	// Getter method for the value of the card
	int Card::getValue() { return this->value; }
};


