#include "game.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include <memory>
using namespace std;


namespace ariel{

    
    // Constructor
    Game::Game(Player& player1, Player& player2)
    { 
        if (player1.isEqual(player2))
        {
            throw invalid_argument("this is not a game to single player !");
        }
        if (player1.getOnGame())
        {
            throw invalid_argument(player1.getName() + "is allready in another war card game !");
        }
        if (player2.getOnGame())
        {
            throw invalid_argument(player2.getName() + "is allready in another war card game !");
        }
        
        this->player1 = &player1;
        this->player2 = &player2;
        this->player1->setOnGame(true);
        this->player2->setOnGame(true);
        deal(fullPile());
    }

    vector<Card> Game::fullPile()
    {
        //Create a Hand with a full deck of cards
        vector<Card> pile;
        string suit[4] = {"clubs", "diamonds", "hearts", "spades"};
        int value[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                pile.push_back(Card(value[j], suit[i]));
            }
        }

        return pile;
    }

    void Game::shuffle(vector<Card>& pile)
    {
        srand((unsigned long)time(0) + pile.size());
        //Select a new random location for each card
        for (uint i = 0; i < pile.size(); i++)
        {
            unsigned long newIndex = (unsigned long)rand()%pile.size();
            pile.insert(pile.begin() + (int)newIndex, pile.at(i));
            pile.erase(pile.begin() + i);
        }
    }

    void Game::deal(vector<Card> pile)
    {
        shuffle(pile);
        
        for(uint i = 0; i < pile.size()-1; i++)
            {
                this->player1->placeBottom(pile.at(i++));
                this->player2->placeBottom(pile.at(i));
            }
    }

    void Game::playTurn() 
    {
        stringstream turn;
        int counterWinnerPile =0;
        string winner = "none";

        if (this->player1->stacksize() == 0 && this->player2->stacksize() == 0  )
        {
            if(this->cashRegister.empty()){
                if(this->player1->cardesTaken() != this->player2->cardesTaken() && (this->player1->cardesTaken() + this->player2->cardesTaken() == 52))
                {
                this->player1->setOnGame(false);
                this->player2->setOnGame(false);
                this->cashRegister.clear();
                cout << "game over" << endl;
                return;
                }
                if(this->player1->cardesTaken() == this->player2->cardesTaken() && (this->player1->cardesTaken() + this->player2->cardesTaken() == 52))
                {
                    this->player1->setOnGame(false);
                    this->player2->setOnGame(false);
                    this->cashRegister.clear();
                    cout << "the game is over its a tie" << endl;
                    return;
                }

            }
            else 
            {
                if(this->player1->cardesTaken() == this->player2->cardesTaken())
                {
                    if(this->cashRegister.size() == 2)
                    {
                        Card card1 = this->cashRegister.back();
                        this->cashRegister.erase(this->cashRegister.end());
                        Card card2 = this->cashRegister.back();
                        this->cashRegister.erase(this->cashRegister.end());
                        if(card1.getValue() == card2.getValue())
                        {
                            this->player1->setOnGame(false);
                            this->player2->setOnGame(false);
                            this->player1->incOwnCardCount(1);
                            this->player2->incOwnCardCount(1);
                            this->cashRegister.clear();
                            return;
                        }
                        if(card1.getValue() > card2.getValue())
                        {
                            this->player1->incOwnCardCount(2);
                            winner = this->player1->getName();
                            turn << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
                            this->log.emplace_back(turn.str());
                            this->player1->setOnGame(false);
                            this->player2->setOnGame(false);
                            this->cashRegister.clear();
                            return;
                        }
                        else
                        {
                            this->player2->incOwnCardCount(2);
                            winner = this->player1->getName();
                            turn << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
                            this->log.emplace_back(turn.str());
                            this->player1->setOnGame(false);
                            this->player2->setOnGame(false);
                            this->cashRegister.clear();
                            return;
                        }
                    }
                    else
                    {
                        deal(this->cashRegister);
                        this->cashRegister.clear();
                    }
                }
            }
            
        }
        
        stringstream turn1;
        Card card1 = this->player1->play();
        Card card2 = this->player2->play();
        this->cashRegister.push_back(card1);
        this->cashRegister.push_back(card2);
        counterWinnerPile += 2;
    
        
        while(card1.getValue() == card2.getValue() && (this->player1->stacksize() != 0 && this->player2->stacksize() != 0 ))
        {
            
            this->cashRegister.push_back(this->player1->play());
            this->cashRegister.push_back(this->player2->play());
            counterWinnerPile += 2;
            
            if (this->player1->stacksize() != 0 && this->player2->stacksize() != 0  ){
                card1 = player1->play();
                this->cashRegister.push_back(card1);
                card2 = player2->play();
                this->cashRegister.push_back(card2);
                counterWinnerPile += 2;
                turn1 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
                this->log.emplace_back(turn1.str());
            }
            else
            {
               
                deal(this->cashRegister);
                this->cashRegister.clear();
            }
        }
        
        stringstream turn2;
        if(card1.getValue() == 1 && card2.getValue() != 2 )
        {
             this->player1->incCounterTurnWin();
            winner = this->player1->getName();
            this->player1->incOwnCardCount(counterWinnerPile);
            this->cashRegister.clear();
            turn2 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
            this->log.emplace_back(turn2.str());
        }
        else if(card1.getValue() == 1 && card2.getValue() != 2 )
        {
            this->player2->incCounterTurnWin();
            winner = this->player2->getName();
            this->player2->incOwnCardCount(counterWinnerPile);
            this->cashRegister.clear();
            turn2 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
            this->log.emplace_back(turn2.str());
        }
        else if(card1.getValue()> card2.getValue())
        {
            this->player1->incCounterTurnWin();
            winner = this->player1->getName();
            this->player1->incOwnCardCount(counterWinnerPile);
            this->cashRegister.clear();
            turn2 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
            this->log.emplace_back(turn2.str());
        }
        else
        {
            this->player2->incCounterTurnWin();
            winner = this->player2->getName();
            this->player2->incOwnCardCount(counterWinnerPile);
            this->cashRegister.clear();
            turn2 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
            this->log.emplace_back(turn2.str());
        }
        

        if (this->player1->stacksize() == 0 && this->player2->stacksize() == 0 && (this->player1->cardesTaken() + this->player2->cardesTaken() == 52) && this->cashRegister.empty())
        {
            this->player1->setOnGame(false);
            this->player2->setOnGame(false);
            this->cashRegister.clear();
        }
            
        
    }

    void Game::printLastTurn()
    {
        if (this->log.size() == 0) 
        {
            throw invalid_argument("The game is not start yet");
        }
        cout << this->log.back().str() << endl;
    
    }

    void Game::playAll() 
    {
        if(!(this->player1->getOnGame()) && !(this->player2->getOnGame())) 
        {
            throw invalid_argument("game over");
        }
        while(this->player1->getOnGame() && this->player2->getOnGame()) 
        {
            playTurn();
        } 
        
        

        
    }

    void Game::printWiner()
    {
        if (this->log.size() == 0) 
        {
            throw invalid_argument("The game is not start yet");
        }
       
        if(this->player1->cardesTaken() > this->player2->cardesTaken()) {cout << this->player1->getName() << endl;}
        if(this->player2->cardesTaken() > this->player1->cardesTaken()) {cout << this->player2->getName() << endl;}
        else
        {
            throw invalid_argument("there is no winners this time");
        }
        
        
    }
    void Game::printLog()
    {
        if (this->log.size() == 0) 
        {
            throw invalid_argument("the game is not start yet");
        }
        for(uint i = 0; i < this->log.size(); i++)
        {
            cout << this->log.at(i).str() << endl;
        }
    }

    void Game::printStats()
    {
        stringstream ss1;
        ss1 << this->player1->getName() << " won " << this->player1->getCounterTurnWin() << " turns of " << this->log.size() << " and wons " << this->player1->cardesTaken() << " cards.";
        cout << ss1.str() << endl;
        stringstream ss2;
        ss2 << this->player2->getName() << " won " << this->player2->getCounterTurnWin() << " turns of " << this->log.size() << " and wons " << this->player2->cardesTaken() << " cards.";
        cout << ss2.str() << endl;
    }
    
};
