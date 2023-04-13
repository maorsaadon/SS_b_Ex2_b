#ifndef GAME_HPP
#define GAME_HPP


#include "player.hpp"
using namespace std;

namespace ariel{
  class Game {
    
    private:
      // Private members
      Player* player1; // pointer to player 1 object 
      Player* player2; // pointer to player 2 object
      vector<stringstream> log; // vector of stringstreams to store game log
      vector<Card> fullPile(); // private method to generate a full deck of cards
      void shuffle(vector<Card>& pile); // private method to shuffle a deck of cards
      void deal(vector<Card> pile); // private method to deal cards to the players
      

    public:

      // Constructor
      Game(Player& player1, Player& player2);
    
      // Public methods
      void playTurn(); // method to play a single turn of the game
      void printLastTurn(); // method to print the last turn played
      int buttle (int value1, int value2);  // method to determine the winner of a round                                         
      void playAll(); // method to play the entire game
      void printWiner(); // method to print the winner of the game
      void printLog(); // method to print the game log
      void printStats(); // method to print the statistics of the game
                      
  };
};

  #endif // GAME_HPP
