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

//I used the following websites
//https://cis.temple.edu/~wolfgang/cis542/Week02.pdf
//https://github.com/Class-Warfare/War-Card-Game


namespace ariel
{

    // Constructor
    Game::Game(Player &player1, Player &player2)
    {
        
        // Check if both players are available to start a new game
        if (player1.getOnGame())
        {
            throw invalid_argument(player1.getName() + "is allready in another war card game !");
        }
        if (player2.getOnGame())
        {
            throw invalid_argument(player2.getName() + "is allready in another war card game !");
        }

         // Set pointers to players and flag that they are currently playing the game
        this->player1 = &player1;
        this->player2 = &player2;
        this->player1->setOnGame(true);
        this->player2->setOnGame(true);
        
        // Start the game by dealing the cards
        deal(fullPile());
    }

    // Creates a full deck of cards
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

    // Shuffle the deck of cards
    void Game::shuffle(vector<Card> &pile)
    {
        // Seed random number generator with current time and pile size
        srand((unsigned long)time(0) + pile.size());
        
        // Shuffle by randomly selecting a new location for each card
        for (uint i = 0; i < pile.size(); i++)
        {
            unsigned long newIndex = (unsigned long)rand() % pile.size();
            pile.insert(pile.begin() + (int)newIndex, pile.at(i));
            pile.erase(pile.begin() + i);
        }
    }

    void Game::deal(vector<Card> pile)
    {
        // Shuffle the pile before dealing
        shuffle(pile);

        // Deal cards to each player's deck, alternating between players
        for (uint i = 0; i < pile.size() - 1; i++)
        {
            this->player1->placeBottom(pile.at(i++));
            this->player2->placeBottom(pile.at(i));
        }
    }

    // Play a single turn of the game
    void Game::playTurn()
    {
        
        // Check that the game has two players
        if (this->player1 == this->player2)
        {
            throw invalid_argument("this is not a game to single player !");
        }

        // Check if both players have run out of cards
        if (this->player1->stacksize() == 0 && this->player2->stacksize() == 0)
        {
             // Check if the game is over because one player has taken more cards than the other
            if (this->player1->cardesTaken() != this->player2->cardesTaken() && (this->player1->cardesTaken() + this->player2->cardesTaken() == 52))
            {
                this->player1->setOnGame(false);
                this->player2->setOnGame(false);
                throw invalid_argument("game over");
            }
            if (this->player1->cardesTaken() == this->player2->cardesTaken() && (this->player1->cardesTaken() + this->player2->cardesTaken() == 52))
            {
                this->player1->setOnGame(false);
                this->player2->setOnGame(false);
                throw invalid_argument("game over its a tie");
            }
        }
        
         // Create string streams for recording the turn's details and the winner
        stringstream turn1;
        stringstream turn2;
        
        // Initialize variables for tracking the number of cards the winner has taken
        int counterWinnerPile = 0;
        string winner = "none";

        // Play one card from each player
        Card card1 = this->player1->play();
        Card card2 = this->player2->play();
        
        // Add the two cards to the counter for the winner pile
        counterWinnerPile += 2;

        // If the two cards have the same value, initiate a "war"
        while ((buttle(card1.getValue(), card2.getValue()) == 0) && (this->player1->stacksize() != 0 && this->player2->stacksize() != 0))
        {
            
            // Play one card face down and one card face up from each player
            this->player1->play();
            this->player2->play();
            
            // Add the four cards to the counter for the winner pile
            counterWinnerPile += 2;

            // Play another card from each player
            if (this->player1->stacksize() != 0 && this->player2->stacksize() != 0)
            {
                card1 = player1->play();
                card2 = player2->play();
                
                // Add the two cards to the counter for the winner pile
                counterWinnerPile += 2;
                
                // Record the turn's details
                turn1 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
                
                 // Add the turn's details to the log
                this->log.emplace_back(turn1.str());
            }
            else
            {
                // If one player runs out of cards during a "war", the other player takes all the cards in the winner pile
                this->player1->incOwnCardCount(counterWinnerPile / 2);
                this->player1->incOwnCardCount(counterWinnerPile / 2);
                counterWinnerPile = 0;
            }
        }

        if (buttle(card1.getValue(), card2.getValue()) == 1)
        {
            this->player1->incCounterTurnWin();
            winner = this->player1->getName();
            this->player1->incOwnCardCount(counterWinnerPile);
            counterWinnerPile = 0;
            turn2 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
            this->log.emplace_back(turn2.str());
        }
        else if (buttle(card1.getValue(), card2.getValue()) == 2)
        {
            this->player2->incCounterTurnWin();
            winner = this->player2->getName();
            this->player2->incOwnCardCount(counterWinnerPile);
            counterWinnerPile = 0;
            turn2 << this->player1->getName() << " played " << card1.getValue() << " of " << card1.getSuit() << " " << this->player2->getName() << " played " << card2.getValue() << " of " << card2.getSuit() << ". " << winner << " wins.";
            this->log.emplace_back(turn2.str());
        }

        if (this->player1->stacksize() == 0 && this->player2->stacksize() == 0 && (this->player1->cardesTaken() + this->player2->cardesTaken() == 52))
        {
            this->player1->setOnGame(false);
            this->player2->setOnGame(false);
        }
    }

    int Game::buttle(int value1, int value2)
    {
        // Determine the winner of a battle based on the values of two cards
        if (value1 == 1 && value2 != 2)
            return 1;
        else if (value2 == 1 && value1 != 2)
            return 2;
        else if (value1 > value2)
            return 1;
        else if (value2 > value1)
            return 2;
        // If the values are equal, return 0 to indicate a tie
        return 0;
        
    }

    void Game::printLastTurn()
    {
        // Check if there are any turns in the log
        if (this->log.size() == 0)
        {
            throw invalid_argument("The game is not start yet");
        }
        // Print the last turn in the log
        cout << this->log.back().str() << endl;
    }

    void Game::playAll()
    {
         // Check if both players are still in the game
        if (!(this->player1->getOnGame()) && !(this->player2->getOnGame()))
        {
            throw invalid_argument("game over");
        }
        // Keep playing turns until one or both players lose
        while (this->player1->getOnGame() && this->player2->getOnGame())
        {
            playTurn();
        }
    }

    void Game::printWiner()
    {
        // Check if there are any turns in the log
        if (this->log.size() == 0)
        {
            throw invalid_argument("The game is not start yet");
        }

        // Check which player won the game based on the number of cards they took
        if (this->player1->cardesTaken() > this->player2->cardesTaken())
        {
            cout << this->player1->getName() << endl;
        }
        if (this->player2->cardesTaken() > this->player1->cardesTaken())
        {
            cout << this->player2->getName() << endl;
        }
        else
        {
            cout << "there is no winners this time" << endl;
        }
    }
    
    void Game::printLog()
    {
        // Check if there are any turns in the log
        if (this->log.size() == 0)
        {
            throw invalid_argument("the game is not start yet");
        }
         // Print all the turns in the log
        for (uint i = 0; i < this->log.size(); i++)
        {
            cout << this->log.at(i).str() << endl;
        }
    }

    void Game::printStats()
    {
        // Print statistics for each player
        stringstream ss1;
        ss1 << this->player1->getName() << " won " << this->player1->getCounterTurnWin() << " turns of " << this->log.size() << " and wons " << this->player1->cardesTaken() << " cards.";
        cout << ss1.str() << endl;
        stringstream ss2;
        ss2 << this->player2->getName() << " won " << this->player2->getCounterTurnWin() << " turns of " << this->log.size() << " and wons " << this->player2->cardesTaken() << " cards.";
        cout << ss2.str() << endl;
    }

};
