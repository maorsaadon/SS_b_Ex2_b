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
	class Card {
		private:
			string suit;
			int value;
		public:
			Card (int value, string suit);
			
			string getSuit();
			int getValue();

	};
};

#endif