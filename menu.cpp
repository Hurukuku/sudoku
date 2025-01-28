#include "main.h"
#include <ncurses.h>

// wyswietlanie menu
void printMenu(const int screen[2], int selected) {
  int start_x = screen[0] / 2 - 5; // ustawiamy tekst na srodek ekranu
  int start_y = screen[1] / 2 - 5;
  for (int i = 0; i < 3; i++) {
    attron(COLOR_PAIR(1));
    if (i == selected) // podswietlamy tekst jesli kursor znajduje sie na opcji
                       // w menu
      attron(COLOR_PAIR(2));
    mvprintw(start_y + i + 2, start_x, MENU_ITEMS[i].c_str());
  }
  refresh();
}

// funkcja odpowiedzialna za funkcjonalnosc glownego menu
void menu() {
  clear();
  int key;
  int screen[2];
  getmaxyx(stdscr, screen[1], screen[0]);
  int x = 0;
  while (1) {
    int newscreen[2];
    getmaxyx(stdscr, newscreen[1], newscreen[0]); // zbieramy rozmiar okna
    if (newscreen[0] != screen[0] or
        newscreen[1] !=
            screen[1]) { // jesli rozmiar okna sie zmienil czyscimy ekran
      screen[0] = newscreen[0];
      screen[1] = newscreen[1];
      clear();
    }
    printMenu(screen, x);

    // zbieramy nacisniety przycisk i przypisujemy do akcji
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
        startGame();
        clear();
        break;
      case 1:
        printRules(screen);
        break;
      case 2:
        x = 99;
        break;
      }
      break;
    case 113: // Litera "Q"
      x = 99;
      break;
    default:
      break;
    }
    if (x == 99) { // 99 jest niemozliwym wynikiem za pomoca normalnej
                   // nawigacji, wiec uzywamy tego jako warunku wyjscia
      break;
    }
  }
}

// wyswietlamy zasady
void printRules(int screen[2]) {
  clear();
  int my = screen[1] / 2 - 7;
  int mx = screen[0] / 2 - 40;
  mvprintw(my + 1, mx+36, " ZASADY ");
  mvprintw(my + 3, mx, " 1. Wypelnij kazde pole cyfra od 1 do 9.");
  mvprintw(my + 5, mx,
           " 2. W kazdej kolumnie moze znajdowac sie tylko jedna dana cyfra.");
  mvprintw(my + 7, mx,
           " 3. W kazdym wierszu moze znajdowac sie tylko jedna dana cyfra.");
  mvprintw(my + 9, mx,
           " 4. W kazdej z dziewieciu podsiatek (3x3) moze znajdowac sie "
           "tylko jedna dana cyfra.");
  mvprintw(my + 12, mx, "Aby powrocic wcisnij dowolny klawisz.");

  refresh();
  wgetch(stdscr);  // czekamy na jakikolwiek przycisk od gracza aby wrocic do menu
  clear();
}
