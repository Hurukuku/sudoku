#include "main.h"
#include <algorithm>
#include <ncurses.h>
#include <random>

bool Plansza::wybierzLiczbe(int x, int y) {
  std::random_device rd;
  std::mt19937 g(rd());
  int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::shuffle(std::begin(nums), std::end(nums), g);
  for (auto num : nums) {
    plansza[x][y] = num;
    if (czyPoprawna()) {
      bool n;
      if (x == 8 && y == 8) {
        return true;
      } else if (x == 8) {
        n = wybierzLiczbe(0, y + 1); 
      } else {
        n = wybierzLiczbe(x + 1, y);
      }
      if (!n) {
        continue;
      } else {
        return true;
      }
    }
  }
  plansza[x][y] = 0;
  return false;
}

void Plansza::generujPlansze() {
  wybierzLiczbe(0, 0);
  for (int n = 0; n < 8; n++) {
    for (int m = 0; m < 8; m++) {
      solved[n][m] = plansza[n][m];
    }
  }
  for (int i = 0; i < 30; i++) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> ds(0, 8);
    while (true) {
      int x = ds(g);
      int y = ds(g);
      if (plansza[x][y] == 0) {
        continue;
      } else {
        plansza[x][y] = 0;
        emptyCells[x][y] = 1;
        break;
      }
    }
  }
}

void Plansza::wypiszPlansze() {

  int start_y = 1;
  int start_x = 1;
  for (int row = 0; row < 9; ++row) {
    int line_y = start_y + 2 + row;
    for (int col = 0; col < 9; ++col) {
      int cell_x = start_x + 3 + col * 2;
      if (emptyCells[row][col] == 1) {
        attron(COLOR_PAIR(4));
      } else {
        attron(COLOR_PAIR(1));
      }
      if (plansza[row][col] == 0) {
        mvprintw(line_y, cell_x, " ");
      } else {
        mvprintw(line_y, cell_x, "%d", plansza[row][col]);
      }
    }
  }
  attron(COLOR_PAIR(1));
  refresh();
}
void Plansza::wypiszPlansze(int x, int y, int screen[2]) {

  int start_y = screen[1]/2 - 7;
  int start_x = screen[0]/2 - 13;
  int max_y;
  int max_x;
  int lx = 0;
  int ly = 0;
  for (int row = 0; row < 9; ++row) {
    
    int line_y = start_y + 2 + row;
    if (row % 3 == 0 && row != 0){
      attron(COLOR_PAIR(3));
      mvprintw(line_y+ly, start_x+2, "---------|---------|---------");
      ly += 1;
    }
    for (int col = 0; col < 9; ++col) {
      int cell_x = start_x + 3 + col * 3;
      if (row == x && col == y) {
        attron(COLOR_PAIR(2));
      } else if (emptyCells[row][col] == 1) {
        attron(COLOR_PAIR(3));
      } else {
        attron(COLOR_PAIR(1));
      }
      if (plansza[row][col] == 0) {
        mvprintw(line_y+ly, cell_x, "   ");
      } else {
        mvprintw(line_y+ly, cell_x, " %d ", plansza[row][col]);
      }
    max_x = cell_x-start_x;
    }
    max_y = line_y-start_y;
  }
  int menu_x = 5;
  int menu_y = start_y + 2;
  attron(COLOR_PAIR(3));
  mvprintw( menu_y, menu_x, "6");
  attron(COLOR_PAIR(1));
  mvprintw(menu_y, menu_x +2 , " <- Twoje liczby");
  menu_y += 2;
  attron(COLOR_PAIR(1));
  mvprintw( menu_y, menu_x, "6");
  attron(COLOR_PAIR(1));
  mvprintw(menu_y, menu_x +2 , " <- Stale liczby");
  menu_y += 2;
  attron(COLOR_PAIR(2));
  mvprintw( menu_y, menu_x-1, " 6 ");
  attron(COLOR_PAIR(1));
  mvprintw(menu_y, menu_x +2 , " <- Kursor");
  // printw("x: %d y: %d", max_x, max_y);
  attron(COLOR_PAIR(1));
  refresh();
}

void Plansza::ustaw(int x, int y, int n) {
  if (n == 48) {
    plansza[x][y] = 0;
  } else if (emptyCells[x][y] == 1) {
    plansza[x][y] = n - 48;
  }
}

bool Plansza::czyPoprawna() {
  // kwadraty
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!sprawdzKwadrat(plansza, i * 3, j * 3))
        return false;
    }
  }
  // kolumny
  for (int i = 0; i < 9; i++) {
    if (!sprawdzKolumne(plansza, i)) {
      return false;
    }
  }
  for (int i = 0; i < 9; i++) {
    if (!sprawdzWiersz(plansza, i)) {
      return false;
    }
  }
  return true;
}