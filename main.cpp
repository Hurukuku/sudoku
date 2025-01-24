#include "main.h"
#include <ncurses.h>

int main() {
  int plansza1[9][9] = {
      {5, 3, 0, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 7, 9}};
  int plansza2[9][9] = {
      {5, 5, 0, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 2, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 9, 4, 8, 5, 6},
      {4, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 0, 7}};

  Plansza plansza;

  plansza.generujPlansze();
  int screen[2];
  int x = 0;
  int y = 0;
  int key;
  initscr();
  keypad(stdscr, TRUE);
  raw();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  getmaxyx(stdscr, screen[1], screen[0]);
  plansza.wypiszPlansze(x, y, screen);
  while (1) {
    int newscreen[2];
    getmaxyx(stdscr, newscreen[1], newscreen[0]);
    if (newscreen[0] != screen[0] or newscreen[1] != screen[1]) {
      screen[0] = newscreen[0];
      screen[1] = newscreen[1];
      clear();
      plansza.wypiszPlansze(x, y, screen);
    }
    // printw("x: %d y: %d", screen[0], screen[1]);
    key = wgetch(stdscr);
    switch (key) {
    case KEY_UP:
      if (x != 0) {
        x--;
      }
      break;
    case KEY_DOWN:
      if (x != 8) {
        x++;
      }
      break;
    case KEY_LEFT:
      if (y != 0) {
        y--;
      }
      break;
    case KEY_RIGHT:
      if (y != 8) {
        y++;
      }
      break;
    case 27:
      x = 99;
      break;
    case 99:
      if (plansza.czyPoprawna()) {
        printw("    1");
      } else {
        printw("    2");
      }

    default:
      if (key > 47 and key < 58) {
        plansza.ustaw(x, y, key);
      }
      // printw("%d", key);

      break;
    }
    if (x == 99) {
      break;
    }
    plansza.wypiszPlansze(x, y, screen);
  }
  endwin();

  return 0;
}