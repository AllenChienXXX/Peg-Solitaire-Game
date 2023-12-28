//
//  PegSolitaire.cpp
//  Peg Solitaire Game
//
//  Created by Allen Chien on 12/27/23.
//

#include "PegSolitaire.hpp"

PegSolitaire::PegSolitaire(){
    createBoard(readValidInt(cin, Dprompt, 1, 4));
    displayBoard();
    readValidMove(cin);
}

PegSolitaire::~PegSolitaire(){
    delete [] board;
}



// returns a valid integer from the user
int PegSolitaire::readValidInt(istream &in, string prompt, int min, int max){
    int num;
    cout << prompt;
    while(true){
        try{
            in >> num;
            if(num<min)
                throw invalid_argument("Please select number from "+to_string(min)+" to "+to_string(max));
            else if(num>max)
                throw invalid_argument("Please select number from "+to_string(min)+" to "+to_string(max));
            else break;
        }catch(const exception& e){
            cout << e.what() << endl;
        }
    }
    return num;
}


// returns an array, initialized according to a specific board type
void PegSolitaire::createBoard(int boardType){
    string Nboard[10];
    switch (boardType) {
        case 1: {
            string Cross[7] = {"###@@@###","###@@@###","@@@@@@@@@","@@@@-@@@@","@@@@@@@@@","###@@@###","###@@@###"};
            MaxR = 7;
            MaxC = 9;
            board = new char*[MaxR];
            for (int i = 0; i < MaxC; ++i) {
                board[i] = new char[MaxC];
            }
            for (int i = 0; i < MaxR; ++i) {
                for (int j = 0; j < MaxC; ++j) {
                    board[i][j] = Cross[i][j];
                }
            }
            break;}
        case 2:{
            string Circle[6] = {"#-@@-#","-@@@@-","@@@@@@","@@@@@@","-@@@@-","#-@@-#"};
            MaxR = 6;
            MaxC = 6;
            board = new char*[MaxR];
            for (int i = 0; i < MaxC; ++i) {
                board[i] = new char[MaxC];
            }
            for (int i = 0; i < MaxR; ++i) {
                for (int j = 0; j < MaxC; ++j) {
                    board[i][j] = Circle[i][j];
                }
            }
            break;}
        case 3:{
            string Triangle[4] = {"###-@-###","##-@@@-##","#-@@-@@-#","-@@@@@@@-"};
            MaxR = 4;
            MaxC = 9;
            board = new char*[MaxR];
            for (int i = 0; i < MaxC; ++i) {
                board[i] = new char[MaxC];
            }
            for (int i = 0; i < MaxR; ++i) {
                for (int j = 0; j < MaxC; ++j) {
                    board[i][j] = Triangle[i][j];
                }
            }
            break;}
        case 4:{
            string SimpleT[5] = {"-----","-@@@-","--@--","--@--","-----"};
            MaxR = 5;
            MaxC = 5;
            
            board = new char*[MaxR];
            for (int i = 0; i < MaxC; ++i) {
                board[i] = new char[MaxC];
            }
            for (int i = 0; i < MaxR; ++i) {
                for (int j = 0; j < MaxC; ++j) {
                    board[i][j] = SimpleT[i][j];
                }
            }
            break;}
        default:
            break;
    }
//    displayBoard();
}

//prints out the contents of a board to for the player to see
void PegSolitaire::displayBoard(){
    cout<<"  ";
    for (int k = 0; k < MaxC; ++k) cout<<k+1;
    cout<<endl;
    for (int i = 0; i < MaxR; ++i) {
        cout<<i+1<<" ";
        for (int j = 0; j < MaxC; ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
    cout<<endl;
}

// reads a single peg jump move in from the user
int PegSolitaire::readValidMove(istream &in){
    while(true){
        int Cloc = readValidInt(in, "Choose the COLUMN of a peg you'd like to move: ", 1, MaxC);
        int Rloc = readValidInt(in, "Choose the ROW of a peg you'd like to move: ", 1, MaxR);
        int Dir = readValidInt(in, "Choose a DIRECTION to move that peg 1) UP, 2) DOWN, 3) LEFT, or 4) RIGHT: ", 1, 4);
        if(isValidMove(Rloc, Cloc, Dir)){
            performMove(Rloc, Cloc, Dir);
            displayBoard();
            if(countPegsRemaining()==1){
                cout<<"Congrats! You won!"<<endl;
                break;
            }else if(countMovesAvailable()==0){
                cout<<"You Lost!"<<endl;
                break;
            }
            continue;
        }else
            cout<<"Invalid Move, Please Try Again."<<endl;
    }
    
    
    return 0;
}

// checks move validity
bool PegSolitaire::isValidMove(int row, int column, int direction){
    if(row-1<0||row-1>MaxR||column-1<0||column-1>MaxC)
        return false;

    if(board[row-1][column-1]!='@')
        return false;
    
    switch (direction) {
        case 1:{
            if(row-2<0||row-2>MaxR||row-3<0||row-3>MaxR)
                return false;
            if(board[row-2][column-1]!='@'||board[row-3][column-1]!='-')
                return false;
            break;}
        case 2:{
            if(row<0||row>MaxR||row+1<0||row+1>MaxR)
                return false;
            if(board[row][column-1]!='@'||board[row+1][column-1]!='-')
                return false;
            break;}
        case 3:{
            if(column-2<0||column-2>MaxC||column-3<0||column-3>MaxC)
                return false;
            if(board[row-1][column-2]!='@'||board[row-1][column-3]!='-')
                return false;
            break;}
        case 4:{
            if(column<0||column>MaxC||column+1<0||column+1>MaxC)
                return false;
            if(board[row-1][column]!='@'||board[row-1][column+1]!='-')
                return false;
            break;}
        default:
            break;
    }
    
    return true;
}

// applies move to a board
void PegSolitaire::performMove(int row, int column, int direction){
    board[row-1][column-1] = '-';
    switch (direction) {
        case 1:{
            board[row-2][column-1] = '-';
            board[row-3][column-1] = '@';
            break;}
        case 2:{
            board[row][column-1] = '-';
            board[row+1][column-1] = '@';
            break;}
        case 3:{
            board[row-1][column-2] = '-';
            board[row-1][column-3] = '@';
            break;}
        case 4:{
            board[row-1][column] = '-';
            board[row-1][column+1] = '@';
            break;}
        default:
            break;
    }
}

// returns the number of pegs left on a board
int PegSolitaire::countPegsRemaining(){
    int count = 0;
    for (int i = 0; i < MaxR; ++i) {
        for (int j = 0; j < MaxC; ++j) {
            if(board[i][j]=='@')
                count++;
        }
    }
    return count;
}

// returns the number of possible moves available on a board
int PegSolitaire::countMovesAvailable(){
    int Mcount = 0;
    for (int i = 1; i <= MaxR; ++i) {
        for (int j = 1; j <= MaxC; ++j) {
            for(int k=1;k<=4;k++){
                if(isValidMove(i, j, k))
                    Mcount++;
            }
        }
    }
    return Mcount;
}
