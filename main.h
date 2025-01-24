#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <random>

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
};

bool sprawdzKwadrat(int plansza[9][9], int x, int y);
bool sprawdzKolumne(int plansza[9][9], int x);
bool sprawdzWiersz(int plansza[9][9], int y);
bool czyPoprawna(int plansza[9][9]);