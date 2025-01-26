#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <string>


const std::string menuItems[3] = {
  "  Graj!   ",
  "  Zasady  ",
  "  Wyjdz   "
};

struct Plansza {
  int solved[9][9] = {{0}};
  int emptyCells[9][9] = {{0}};
  int plansza[9][9] = {{0}};
  bool czyPoprawna();
  void generujPlansze();
  void wypiszPlansze();
  void wypiszPlansze(int x, int y, int screen[2]);
  bool wybierzLiczbe(int x, int y);
  void ustaw(int x, int y, int n);
  bool isComplete();
};

const int test[2] = {0 ,0};

bool sprawdzKwadrat(int plansza[9][9], int x, int y);
bool sprawdzKolumne(int plansza[9][9], int x);
bool sprawdzWiersz(int plansza[9][9], int y);
bool czyPoprawna(int plansza[9][9]);
void gra(int poziom);
void menu();
void printMenu(const int screen[2] = &test[2], int selected = 0);