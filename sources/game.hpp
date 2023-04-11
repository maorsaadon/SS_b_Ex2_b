#ifndef GAME_HPP
#define GAME_HPP


#include "player.hpp"
using namespace std;

namespace ariel{
  class Game {
    
    private:
      // Private members
      Player* player1; 
      Player* player2;
      vector<stringstream> log;
      vector<Card> fullPile();
      void shuffle(vector<Card>& pile);
      void deal(vector<Card> pile);
      

    public:

      // Constructor
      Game(Player& player1, Player& player2);
    
      // Public methods
      void playTurn();
      void printLastTurn(); 
      int buttle (int value1, int value2);                                            
      void playAll();
      void printWiner();
      void printLog();
      void printStats();
                      
  };
};

  #endif // GAME_HPP
