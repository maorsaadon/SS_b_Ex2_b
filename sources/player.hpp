#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <vector>
using namespace std;

namespace ariel{
  class Player {
    private:
      // Private members
      string name;
      vector<Card> myPile;
      int ownCardCount;
      int counterTurnWin;
      bool onGame;
      

    public:
      // Constructor
      Player(string name);

      string getName();
      bool pileIsEmpty();
      void incOwnCardCount(int size);
      void placeBottom(Card card);
      int cardesTaken();
      int stacksize(); 
      int getCounterTurnWin();
      int incCounterTurnWin(); 
      bool getOnGame();
      void setOnGame(bool sign);
      Card play();

  };
};

#endif // PLAYER_HPP
