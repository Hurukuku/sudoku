#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <string>


const std::string MENU_ITEMS[3] = {
  "  Graj!   ",
  "  Zasady  ",
  "  Wyjdz   "
};

struct Sudoku {
  int solvedBoard[9][9] = {{0}};
  int isCellEmpty[9][9] = {{0}};
  int currentBoard[9][9] = {{0}};
  bool validateBoard();
  void genBoard();
  void printBoard();
  void printBoard(int x, int y, int screen[2]);
  bool chooseNumber(int x, int y);
  void setCellValue(int x, int y, int n);
  bool isComplete();
};

bool validateSquare(int board[9][9], int x, int y);
bool validateCol(int board[9][9], int x);
bool validateRow(int board[9][9], int y);
void startGame();
void menu();
void printMenu(const int screen[2], int selected);