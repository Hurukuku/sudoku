#include "main.h"

bool sprawdzKwadrat(int plansza[9][9], int x, int y) {

  int num[9] = {0}; // przechowywanie czy dana liczba juz istnieje
  for (int i = x; i < 3 + x; i++) {
    for (int j = y; j < 3 + y; j++) {
      if (plansza[i][j] != 0) {          // 0 - puste pole - ignorujemy
        if (num[plansza[i][j] - 1] == 0) // jezeli liczba nie istnieje,
          num[plansza[i][j] - 1] = 1;
        else{
          return false;
        }
      }
    }
  }
  return true;
}
bool sprawdzKolumne(int plansza[9][9], int x) {
  int num[9] = {0};
  for (int i = 0; i < 9; i++) {
    if (plansza[i][x] != 0) {
      if (num[plansza[i][x] - 1] == 0) {
        num[plansza[i][x] - 1] = 1;
      } else {
        return false;
      }
    }
  }
  return true;
}

bool sprawdzWiersz(int plansza[9][9], int y) {
  int num[9] = {0};
  for (int i = 0; i < 9; i++) {
    if (plansza[y][i] != 0) {
      if (num[plansza[y][i] - 1] == 0) {
        num[plansza[y][i] - 1] = 1;
      } else {
        return false;
      }
    }
  }
  return true;
}

bool czyPoprawna(int plansza[9][9]) {
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


