#include <algorithm>
#include <ncurses.h>
#include <random>
#include <string>

// elementy menu
const std::string MENU_ITEMS[3] = {
  "  Graj!   ",
  "  Zasady  ",
  "  Wyjdz   "
};

//struct do zarzadzania gra i plansza
struct Sudoku {
  int solvedBoard[9][9] = {{0}};          // ulozona plansza
  int isCellEmpty[9][9] = {{0}};          // lista "wyczyszczonych" pól - do uzupelnienia przez gracza
  int currentBoard[9][9] = {{0}};         // aktualny stan planszy
  bool validateBoard();                           // sprawdza czy plansza jest poprawna / nie lamie zadnych zasad sudoku
  void genBoard();                                // generuje plansze
  void printBoard(int x, int y, int screen[2]);   // wyswietla plansze
  bool chooseNumber(int x, int y);                // rekursywny algorytm generowania plansz sudoku
  void setCellValue(int x, int y, int n);         // ustawia wartosc pola
  bool isComplete();
};


// funkcje pomocnicze do sprawdzania poprawnosci planszy
bool validateSquare(int board[9][9], int x, int y);
bool validateCol(int board[9][9], int x);
bool validateRow(int board[9][9], int y);


// funckje do uruchomienia rozgrywki i zarzadzania menu
void startGame();
void menu();
void printMenu(const int screen[2], int selected);
void printRules(int screen[2]);