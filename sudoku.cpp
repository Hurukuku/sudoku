#include "main.h"

bool Sudoku::chooseNumber(int x, int y) {
  std::random_device rd;
  std::mt19937 g(rd());
  int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::shuffle(std::begin(nums), std::end(nums), g);
  for (auto num : nums) {
    currentBoard[x][y] = num;
    if (validateBoard()) {
      bool n;
      if (x == 8 && y == 8) {
        return true;
      } else if (x == 8) {
        n = chooseNumber(0, y + 1);
      } else {
        n = chooseNumber(x + 1, y);
      }
      if (!n) {
        continue;
      } else {
        return true;
      }
    }
  }
  currentBoard[x][y] = 0;
  return false;
}

void Sudoku::genBoard() {
  chooseNumber(0, 0);
  for (int n = 0; n < 8; n++) {
    for (int m = 0; m < 8; m++) {
      solvedBoard[n][m] = currentBoard[n][m];
    }
  }
  for (int i = 0; i < 15; i++) {
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

void Sudoku::printBoard() {

  int start_y = 1;
  int start_x = 1;
  for (int row = 0; row < 9; ++row) {
    int line_y = start_y + 2 + row;
    for (int col = 0; col < 9; ++col) {
      int cell_x = start_x + 3 + col * 2;
      if (isCellEmpty[row][col] == 1) {
        attron(COLOR_PAIR(4));
      } else {
        attron(COLOR_PAIR(1));
      }
      if (currentBoard[row][col] == 0) {
        mvprintw(line_y, cell_x, " ");
      } else {
        mvprintw(line_y, cell_x, "%d", currentBoard[row][col]);
      }
    }
  }
  attron(COLOR_PAIR(1));
  refresh();
}
void Sudoku::printBoard(int x, int y, int screen[2]) {
  if (screen[0] > 30 and screen[1] > 15) {
    int k = 3;
    if (isComplete() && validateBoard())
      k = 4;
    int start_y = screen[1] / 2 - 7;
    int start_x = screen[0] / 2 - 17;
    int max_y;
    int max_x;
    int lx = 0;
    int ly = 0;
    for (int row = 0; row < 9; ++row) {
					
      int line_y = start_y + row;
      if (row % 3 == 0 && row != 0) {
        attron(COLOR_PAIR(k));
        mvprintw(line_y + ly, start_x + 2, "---------|---------|---------");
        ly += 1;
      }
      for (int col = 0; col < 9; ++col) {
        int cell_x = start_x + 3 + col * 3;
        if (row == x && col == y) {
          attron(COLOR_PAIR(2));
        } else if (isCellEmpty[row][col] == 1) {
          attron(COLOR_PAIR(k));
        } else {
          attron(COLOR_PAIR(1));
        }
        if (currentBoard[row][col] == 0) {
          mvprintw(line_y + ly, cell_x, "   ");
        } else {
          mvprintw(line_y + ly, cell_x, " %d ", currentBoard[row][col]);
        }
        max_x = cell_x - start_x;
      }
      max_y = line_y - start_y;
    }
    // printw(" %d ", screen[0]);
    int menu_x, menu_y;
    if (screen[0] < 85) {
      menu_x = start_x + 3;
      menu_y = max_y - 5;
    } else {
      menu_x = 2;
      menu_y = start_y;
    }
    attron(COLOR_PAIR(3));
    mvprintw(menu_y, menu_x + 3, "6");
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 8, " <- Twoje liczby");
    menu_y += 2;
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 3, "6");
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 8, " <- Stale liczby");
    menu_y += 2;
    attron(COLOR_PAIR(2));
    mvprintw(menu_y, menu_x + 2, " 6 ");
    attron(COLOR_PAIR(1));
    mvprintw(menu_y, menu_x + 8, " <- Kursor");
    menu_y += 2;
    mvprintw(menu_y, menu_x, "Strzalki <- Poruszanie");
    menu_y += 2;
    mvprintw(menu_y, menu_x, "   Q     <- Wyjscie");
    menu_y += 2;
    mvprintw(menu_y, menu_x, "   C     <- Sprawdz");
    // printw("x: %d y: %d", max_x, max_y);
    attron(COLOR_PAIR(1));
    refresh();
  } else {
    attron(COLOR_PAIR(3));
    printw("Okno jest za male!");
  }
}

void Sudoku::setCellValue(int x, int y, int n) {
  if (n == 48) {
    currentBoard[x][y] = 0;
  } else if (isCellEmpty[x][y] == 1) {
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
  for (int i = 0; i < 9; i++) {
    if (!validateRow(currentBoard, i)) {
      return false;
    }
  }
  return true;
}
bool Sudoku::isComplete() {
  for (auto &x : currentBoard) {
    for (auto y : x) {
      if (y == 0)
        return false;
    }
  }
  return true;
}