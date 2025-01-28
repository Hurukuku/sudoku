#include "main.h"
#include <ncurses.h>


// rekurencyjny algorytm do tworzenia plansz
bool Sudoku::chooseNumber(int x, int y) {
  // najpierw "tasujemy" zbior mozliwych liczb
  std::random_device rd;  
  std::mt19937 g(rd());
  int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::shuffle(std::begin(nums), std::end(nums), g);

  // potem probojemy kazda liczbe w naszym zbiorze
  for (auto num : nums) {
    currentBoard[x][y] = num;
    if (validateBoard()) { // jesli liczba moze zostac w danym polu postawiona, rekursywnie wybieramy kolejna
      bool n;
      if (x == 8 && y == 8) {
        return true;
      } else if (x == 8) {
        n = chooseNumber(0, y + 1);
      } else {
        n = chooseNumber(x + 1, y);
      }
      if (!n) { // jesli zadna liczba w kolejnym przejsciu nie jest prawidlowa, to cofamy sie o jedno wykonanie i probojemy dla kolejnej liczby 
        continue;
      } else {  
        return true; 
      }
    }
  }
  currentBoard[x][y] = 0; // gdy zadna liczba nie pasuje ustawiamy ja spowrotem na 0 aby nie mieszac ze sprawdzaniem
  return false;
}

void Sudoku::genBoard() {
  chooseNumber(0, 0); // generujemy plansze naszym algorytmem
  for (int n = 0; n < 8; n++) {
    for (int m = 0; m < 8; m++) {
      solvedBoard[n][m] = currentBoard[n][m]; // ustawiamy nasza "Ukonczona plansze"  - w sumie nigdzie nie zostala potem uzyta
    }
  }
  for (int i = 0; i < 15; i++) {  // losujemy 15 liczb do usuniecia z planszy.
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> ds(0, 8);
    while (true) {
      int x = ds(g);
      int y = ds(g);
      if (currentBoard[x][y] == 0) {
        continue;
      } else {
        currentBoard[x][y] = 0;
        isCellEmpty[x][y] = 1;
        break;
      }
    }
  }
}


void Sudoku::printBoard(int x, int y, int screen[2]) {
  if ((screen[0] > 85 and screen[1] > 15) or (screen[0] > 30 and screen[1] > 28) ) { // sprawdzamy czy okno jest wystarczajaco duze aby wyswietlic 
    int k = 3;
   
    int max_y = 8;
    int max_x = 27;
    int start_y = screen[1] / 2 - max_y/2;
    int start_x = screen[0] / 2 - max_x/2 - 1;
    int ly = 0;
     if (isComplete() && validateBoard()){  // jak plansza jest zapelniona i poprawna zmieniamy kolor na wpisanych liczb i linii na zielony i wypisujemy "Gratulacje!" 
      k = 4;
      mvprintw(start_y - 3, screen[0]/2 - 5, "Gratulacje!");
      mvprintw(start_y - 2, screen[0]/2 - 13, "Udalo ci sie ulozyc sudoku");
       
     } 
    for (int row = 0; row < 9; ++row) {
					
      int line_y = start_y + row;
      if (row % 3 == 0 && row != 0) {
        attron(COLOR_PAIR(k));
        mvprintw(line_y + ly, start_x + 2, "---------|---------|---------"); // dodajemy linie rozdzielajace
        ly += 1;  // obnizamy kolejne linie o 1 aby zrobic miejsce dla linii rozdzielajacych
      }
      for (int col = 0; col < 9; ++col) {
        int cell_x = start_x + 3 + col * 3;
        if (row == x && col == y) {
          attron(COLOR_PAIR(2));  // podswietlamy wybrana komorke
        } else if (isCellEmpty[row][col] == 1) {
          attron(COLOR_PAIR(k));  // liczby wpisane przez gracza sa czerwone / zielone zaleznie od stanu gry
        } else {
          attron(COLOR_PAIR(1));  // reszta liczb jest biala
        }
        if (currentBoard[row][col] == 0) {   // wypisujemy liczby na planszy
          mvprintw(line_y + ly, cell_x, "   ");
        } else {
          mvprintw(line_y + ly, cell_x, " %d ", currentBoard[row][col]);
        }
      }
    }
    int menu_x, menu_y, inc;
    if (screen[0] < 85) {     // ustawiamy pozycje startowa interfejsu zaleznie od wielkosci okna
      menu_x = start_x + 3;
      menu_y = max_y - 5;
      inc = 1;
    } else {
      menu_x = 2;
      menu_y = start_y;
      inc = 2;
    }

    // wypisujemy pomocnicze menu
    attron(COLOR_PAIR(3));
    mvprintw(menu_y, menu_x + 3, "6");
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 8, " <- Twoje liczby");
    menu_y += inc;
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 3, "6");
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 8, " <- Stale liczby");
    menu_y += inc;
    attron(COLOR_PAIR(2));
    mvprintw(menu_y, menu_x + 2, " 6 ");
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 8, " <- Kursor");
    menu_y += inc;
    mvprintw(menu_y, menu_x, "Strzalki <- Poruszanie");
    menu_y += inc;
    mvprintw(menu_y, menu_x, "   Q     <- Wyjscie");
    menu_y += inc;

    attron(COLOR_PAIR(1));
    refresh();
  } else { // jesli okno jest za male wyswietlamy komunikat
    attron(COLOR_PAIR(3));
    clear();
    printw("Okno jest za male!");
  }
}

// sprawdzamy czy pole jest przeznaczone do ustawienia dla gracza i ustawiamy je na wpisana liczbe  ( 0 usuwa liczbe ) 
void Sudoku::setCellValue(int x, int y, int n) {
  // if (n == 48 and isCellEmpty[x][y] == 1) {
  //   currentBoard[x][y] = 0;
  // }
if (isCellEmpty[x][y] == 1) {
    currentBoard[x][y] = n - 48;
  }
}

bool Sudoku::validateBoard() {
  // kwadraty
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!validateSquare(currentBoard, i * 3, j * 3))
        return false;
    }
  }
  // kolumny
  for (int i = 0; i < 9; i++) {
    if (!validateCol(currentBoard, i)) {
      return false;
    }
  }
  // wiersze
  for (int i = 0; i < 9; i++) {
    if (!validateRow(currentBoard, i)) {
      return false;
    }
  }
  return true;
}

// sprawdza czy plansza jest pelna
bool Sudoku::isComplete() {
  for (auto &x : currentBoard) {
    for (auto y : x) {
      if (y == 0)
        return false;
    }
  }
  return true;
}