#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include <memory>
using namespace std;


namespace ariel{
	// Class for representing a playing card
	class Card {
		private:
			string suit; // The suit of the card (e.g. "hearts", "spades", "diamonds", "clubs")
			int value;  // The value of the card (e.g. 2, 3, 4, ..., 10, J, Q, K, A)
		public:
			// Constructor that initializes the suit and value of the card
			Card (int value, string suit);
			
			// Getter method for the suit of the card
			string getSuit();

			// Getter method for the value of the card
			int getValue();

	};
};

#endif