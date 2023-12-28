//
//  PegSolitaire.hpp
//  Peg Solitaire Game
//
//  Created by Allen Chien on 12/27/23.
//

#ifndef PegSolitaire_hpp
#define PegSolitaire_hpp

#include <stdio.h>
#include <iostream>


#endif /* PegSolitaire_hpp */

using namespace std;

class PegSolitaire{
private:
    char** board;
    int MaxR;
    int MaxC;
    string Dprompt = "WELCOME TO CS300 PEG SOLITAIRE!\n===============================\n\nBoard Style Menu\n 1) Cross\n 2) Circle\n 3) Triangle\n 4) Simple T\nChoose a board style: ";

public:
    PegSolitaire();
    
    ~PegSolitaire();
    
    PegSolitaire(int boardType);
    
    int readValidInt(istream &in, string prompt, int min, int max);// returns a valid integer from the user
    
    void createBoard(int boardType); // returns an array, initialized according to a specific board type

    void displayBoard();// prints out the contents of a board to for the player to see

    int readValidMove(istream &in); // reads a single peg jump move in from the user

    bool isValidMove(int row, int column, int direction); // checks move validity
    
    void performMove(int row, int column, int direction); // applies move to a board

    int countPegsRemaining();// returns the number of pegs left on a board
    
    int countMovesAvailable();// returns the number of possible moves available on a board
};
