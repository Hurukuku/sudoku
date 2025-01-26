#include "main.h"
#include <ncurses.h>

void printMenu(const int screen[2], int selected) {
  int start_x = screen[0] / 2 - 5;
  int start_y = screen[1] / 2 - 5;
  for (int i = 0; i < 3; i++) {
    attron(COLOR_PAIR(1));
    if (i == selected)
      attron(COLOR_PAIR(2));
    mvprintw(start_y + i + 2, start_x, menuItems[i].c_str());
  }
  refresh();
}

void menu() {
  clear();
  int key;
  int screen[2];
  getmaxyx(stdscr, screen[1], screen[0]);
  int x = 0;
  while (1) {
    int newscreen[2];
    getmaxyx(stdscr, newscreen[1], newscreen[0]);
    if (newscreen[0] != screen[0] or newscreen[1] != screen[1]) {
      screen[0] = newscreen[0];
      screen[1] = newscreen[1];
      clear();
    }
    printMenu(screen, x);
    // printw("x: %d y: %d", screen[0], screen[1]);
    key = wgetch(stdscr);
    switch (key) {
    case KEY_UP:
      if (x != 0) {
        x--;
      }
      break;
    case KEY_DOWN:
      if (x != 2) {
        x++;
      }
      break;
    case 10:
      switch (x) {
      case 0:
        gra(0);
        clear();
        break;
      case 1:
        break;
      case 2:
        x = 99;
        break;
      }
      break;
    case 113:
      x = 99;
      break;

    default:
      // printw("%d", key);

      break;
    }
    if (x == 99) {
      break;
    }
  }
}
