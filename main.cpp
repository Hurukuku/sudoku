#include "main.h"
#include <cmath>
int main() {
  // uruchamiamy biblioteke ncurses
  initscr();
  keypad(stdscr, TRUE); // wlaczamy zbieranie przyciskow z okna
  raw();  // konsola ignoruje specjalne klawisze / kombinacje
  noecho();  // wylaczamy wyswietlanie w konsoli poza naszym ncurses
  curs_set(0); // wylaczamy konsolowy kursor
  start_color(); // wlaczamy wsparcie dla kolorow
  // ustawiamy kolorki
  init_pair(1, COLOR_WHITE, COLOR_BLACK);       // biale litery na czarnym tle - normalne
  init_pair(2, COLOR_BLACK, COLOR_WHITE);       // czarne na bialym - dla kursora
  init_pair(3, COLOR_RED, COLOR_BLACK);         // czerwone na czarnym
  init_pair(4, COLOR_GREEN, COLOR_BLACK);       // zielone na czarnym
  menu(); // wyswietlamy menu
  endwin(); // zamykamy ncurses i konczymy program

  return 0;
}

void startGame() {
  clear();
  int key;
  Sudoku sudoku;
  sudoku.genBoard();
  // zbieramy rozmiar okna
  int screen[2];
  getmaxyx(stdscr, screen[1], screen[0]); 
  int x = 0;
  int y = 0;
  sudoku.printBoard(x, y, screen);
  while (1) {
    int newscreen[2];
    getmaxyx(stdscr, newscreen[1], newscreen[0]);
    if (newscreen[0] != screen[0] or newscreen[1] != screen[1]) { // jesli rozmiar okna sie zmienil czyscimy ekran
      screen[0] = newscreen[0];
      screen[1] = newscreen[1];
      clear();
      sudoku.printBoard(x, y, screen);
    }
    // zbieramy nacisniety przycisk i przypisujemy do akcji
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
    case 113: // litera "Q"
      x = 99;
      break;
    default:
      if (key > 47 and key < 58) {
        sudoku.setCellValue(x, y, key);
      }
      break;
    }
    if (x == 99) { // 99 jest niemozliwym wynikiem za pomoca normalnej nawigacji, wiec uzywamy tego jako warunku wyjscia
      break;
    }
    sudoku.printBoard(x, y, screen);
  }
}
