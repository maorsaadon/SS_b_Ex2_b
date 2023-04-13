#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <vector>
using namespace std;

namespace ariel{
  class Player {
    private:
      // Private members
      string name; // The name of the player
      vector<Card> myPile; // The player's pile of cards
      int ownCardCount; // The number of cards in the player's pile
      int counterTurnWin; // The number of turns the player has won
      bool onGame; // A boolean value indicating whether the player is currently playing or not

    public:
      // Constructor
      Player(string name);

      string getName(); // Getter for the player's name
      bool pileIsEmpty(); // A boolean function that returns true if the player's pile is empty
      void incOwnCardCount(int size); // Increases the number of cards in the player's pile
      void placeBottom(Card card); // Places a card at the bottom of the player's pile
      int cardesTaken(); // Returns the number of cards the player has taken in the current turn
      int stacksize(); // Returns the number of cards in the player's pile
      int getCounterTurnWin(); // Getter for the number of turns the player has won
      int incCounterTurnWin(); // Increases the number of turns the player has won
      bool getOnGame(); // Getter for the boolean value indicating whether the player is currently playing or not
      void setOnGame(bool sign); // Setter for the boolean value indicating whether the player is currently playing or not
      Card play(); // Plays a card from the player's pile
  };
};

#endif // PLAYER_HPP
