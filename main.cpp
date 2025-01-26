#include "main.h"
#include <cmath>
int main() {
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
  menu();
  endwin();

  return 0;
}

void gra(int poziom) {
  int key;
  Sudoku sudoku;
  sudoku.genBoard();
  int screen[2];
  getmaxyx(stdscr, screen[1], screen[0]);
  int x = 0;
  int y = 0;
  sudoku.printBoard(x, y, screen);
  while (1) {
    int newscreen[2];
    getmaxyx(stdscr, newscreen[1], newscreen[0]);
    if (newscreen[0] != screen[0] or newscreen[1] != screen[1]) {
      screen[0] = newscreen[0];
      screen[1] = newscreen[1];
      clear();
      sudoku.printBoard(x, y, screen);
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
    case 113:
      x = 99;
      break;
    case 99:
      if (sudoku.validateBoard()) {
        printw("    1");
      } else {
        printw("    2");
      }

    default:
      if (key > 47 and key < 58) {
        sudoku.setCellValue(x, y, key);
      }
      // printw("%d", key);

      break;
    }
    if (x == 99) {
      break;
    }
    sudoku.printBoard(x, y, screen);
  }
}
