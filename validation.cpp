#include "main.h"

bool validateSquare(int board[9][9], int x, int y) {

  int num[9] = {0}; // przechowywanie czy dana liczba juz istnieje
  for (int i = x; i < 3 + x; i++) {
    for (int j = y; j < 3 + y; j++) {
      if (board[i][j] != 0) {          // 0 - puste pole - ignorujemy
        if (num[board[i][j] - 1] == 0) // jezeli liczba nie mamy w naszej liscie to ja tam dodajemy
          num[board[i][j] - 1] = 1;  
        else{ 
          return false;       // jak juz istnieje to zwracamy falsz
        }
      }
    }
  }
  return true;
}
bool validateCol(int board[9][9], int x) {
  int num[9] = {0};
  for (int i = 0; i < 9; i++) {
    if (board[i][x] != 0) {
      if (num[board[i][x] - 1] == 0) {
        num[board[i][x] - 1] = 1;
      } else {
        return false;
      }
    }
  }
  return true;
}

bool validateRow(int board[9][9], int y) {
  int num[9] = {0};
  for (int i = 0; i < 9; i++) {
    if (board[y][i] != 0) {
      if (num[board[y][i] - 1] == 0) {
        num[board[y][i] - 1] = 1;
      } else {
        return false;
      }
    }
  }
  return true;
}

bool validateBoard(int board[9][9]) {
  // kwadraty
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!validateSquare(board, i * 3, j * 3))
        return false;
    }
  }
  // kolumny
  for (int i = 0; i < 9; i++) {
    if (!validateCol(board, i)) {
      return false;
    }
  }
  for (int i = 0; i < 9; i++) {
    if (!validateRow(board, i)) {
      return false;
    }
  }
  return true;
}


