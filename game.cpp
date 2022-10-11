#include <iostream>

using namespace std;

//By Ryan Veith
//Date: 10/11/2022
//This should let you play a game of tictactoe with a friend
//X goes first, It also Keeps track of total wins

//resetGame just clears the board, new game does a full new game
void resetGame(char board[3][3]);
void printBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
bool checkTie(char board[3][3]);
//new game is pass by reference so all the changes are saved
void newGame(char board[3][3], int xWins, int oWins,
	     char &currentPlayer, bool &win);
void playerTurn(char board[3][3], char player);

int main()
{
  char gameBoard[3][3];
  int xWins = 0;
  int oWins = 0;
  bool win = false;
  resetGame(gameBoard);
  char currentPlayer = 'X';
  while (win == false)
    {
      playerTurn(gameBoard, currentPlayer);
      //did someone win?
      if (checkWin(gameBoard, currentPlayer) == true)
	{
	  //increace total wins
	  if (currentPlayer == 'X')
	    {
	      xWins++;
	    }
	  else
	    {
	      oWins++;
	    }
	  newGame(gameBoard, xWins, oWins, currentPlayer, win);
	}
      if (checkTie(gameBoard) == true)
	{
	  newGame(gameBoard, xWins, oWins, currentPlayer, win);
	}
	  
      //have the other player play
      if (currentPlayer == 'X')
	{
	  currentPlayer = 'O';
	}
      else
      {
	currentPlayer = 'X';
      }
    }
}

//clears the board and does into instuctions
void resetGame(char board[3][3])
{
  for (int a = 0; a < 3; a++)
    {
      for (int b = 0; b < 3; b++)
	{
	  board[a][b] = ' ';
	}	
    }
  cout << "Welcome to TicTacToe" << endl;
}

//prints the board to console
void printBoard(char board[3][3])
{
  //fancy prinout of the board
  cout << "   1   2   3 " << endl;
  cout << "a  " << board[0][0] <<" | "
                << board[1][0] <<" | "
                << board[2][0] <<" " << endl;
  cout << "  -----------" << endl;  
  cout << "b  " << board[0][1] <<" | "
                << board[1][1] <<" | "
                << board[2][1] <<" " << endl;
  cout << "  -----------" << endl;
  cout << "c  " << board[0][2] <<" | "
                << board[1][2] <<" | "
                << board[2][2] <<" " << endl;
}
//checks if one side won
bool checkWin(char board[3][3], char player)
{
  //check row
  for (int a = 0; a < 3; a++)
    {      
      if (board[a][0] == player &&
	  board[a][1] == player &&
	  board[a][2] == player)
	{
	  return true;
	}
    }
  //check colums
  for (int b = 0; b < 3; b++)
    {      
      if (board[0][b] == player &&
	  board[1][b] == player &&
	  board[2][b] == player)
	{
	  return true;
	}
    }
  //check diagnols
  if (board[0][0] == player &&
      board[1][1] == player &&
      board[2][2] == player)
    {
      return true;
    }
  if (board[2][0] == player &&
      board[1][1] == player &&
      board[0][2] == player)
    {
      return true;
    }
  //no matches
  return false;
}

//is every spot full?
bool checkTie(char board[3][3])
{
  for (int a = 0; a < 3; a++)
    {
      for (int b = 0; b < 3; b++)
	{
	  if (board[a][b] == ' ')
	    {
	      return false;
	    }
	}
    }
  cout << "Cat's Game (tie)" << endl;
  return true;
}

//print out win numbers and board and ask if they want to play agian
void newGame(char board[3][3], int xWins, int oWins,
	     char &currentPlayer, bool &win)
{
  //print board and win count
	  printBoard(board);
	  cout << "X wins:" << xWins << " O wins:" << oWins << endl;
	  //play again?
	  cout << "Do you want to play agian? (y/n)" << endl;
	  char input[0];
	  cin.get(input, 2);
	  cin.ignore(1,'\n');
	  if (input[0] == 'y')
	    {
	      //reset
	      resetGame(board);
	      //make it player X agian
	      //switch it to O since at the end of a turn
	      //we change it to the other one so if it is
	      //O now it will be X for next turn
	      currentPlayer = 'O';
	    }
	  else
	    {
	      win = true;
	    }
}

//go though a players tun
//insturions and print borad
//let them play
void playerTurn(char board[3][3], char player) {
  cout << player << endl;
  cout << "It is " << player << "'s turn" << endl;
  cout << "to play type the row then the collum of the intended space" << endl;
  //do this while they havent selected a free space
  bool finished = false;
  while (finished == false)
    {
      //print board
      printBoard(board);
      //get input to play
      char input[2];
      input[0] = ' ';
      input[1] = ' ';
      cin.get(input, 3);
      cin.ignore(2,'\n');
      //turn letters into a numeber
      int inputNum = 3;
      if (input[0] == 'a' || input [0] == 'A')
	{
	  inputNum = 0;
	}
      else if (input[0] == 'b' || input [0] == 'B')
	{
	  inputNum = 1;
	}
      else if (input[0] == 'c' || input [0] == 'C')
	{
	  inputNum = 2;
	}
      //it was not a b or c complain
      else 
	{
	  cout << "you need to type a letter for the row" << endl;
	}
      //if it's not 1 2 or 3 complain
      if (input[1] != '1' && input[1] != '2' && input[1] != '3')
    {
      cout << "you need to type a number for the collum" << endl;
    }
      
      //they gave a ligitamete spot see if it is free
      else if (inputNum != 3)
	{
	  //subtract 48 to turn it into # and 1 to get it to corredt array spot
	  //check if it is free
	  if (board[input[1]-49][inputNum] == ' ')
	    {
	      board[input[1]-49][inputNum] = player;
	      finished = true;
	    }
	  
	  //the spot they played is not free complain
	  else
	    {
	      cout << "you can't play ontop of a differnt space" << endl;
	    }
	}
    }
}
