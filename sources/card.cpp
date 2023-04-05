#include "card.hpp"
using namespace std;

namespace ariel{
	Card::Card (int value, string suit)
	{
		this->suit = suit;
		this->value = value;
	}
	string Card::getSuit() { return this->suit; }
	int Card::getValue() { return this->value; }
};


