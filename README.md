# Sudoku - Projekt Zaliczeniowy

## Opis projektu

Program umożliwiający rozgrywkę w sudoku na losowo generowanych planszach.

## Funkcjonalności

- Generowanie losowej planszy sudoku i losowe rozmieszczenie pustych pól.
- Interfejs użytkownika wykonany w bibliotece `ncurses`.
- Gra sudoku – wypełnianie planszy przez gracza.
- Intuicyjne sterowanie strzałkami.
- Program informuje gracza, gdy poprawnie uzupełni planszę.
- Menu główne z możliwością rozpoczęcia rozgrywki i wyświetlenia zasad sudoku.
- Sprawdzanie, czy okno konsoli jest wystarczająco duże, aby wyświetlić interfejs, i odpowiedni komunikat w razie potrzeby.

## Struktura plików

- `main.cpp` - Plik wejściowy programu, odpowiada za inicjalizację biblioteki `ncurses`, uruchomienie menu głównego oraz sterowanie rozgrywką.
- `menu.cpp` - Funkcje związane z menu programu.
- `sudoku.cpp` - Logika rozgrywki, generowanie plansz, sprawdzanie poprawności i ich wyświetlanie.
- `validation.cpp` - Funkcje sprawdzające poprawność planszy.
- `main.h` - Plik nagłówkowy łączący cały program.

## Algorytmy

### Generowanie planszy Sudoku (rekurencyjnie):
1. Zaczynamy od indeksu `[0, 0]`.
2. Tasujemy zbiór możliwych liczb `[1-9]`.
3. Próbujemy wpisać każdą liczbę po kolei do pola.
4. Jeśli plansza jest poprawna, wywołujemy rekurencyjnie funkcję dla kolejnego pola.
5. Jeśli żadna liczba nie pasuje, cofamy się i próbujemy ponownie.
6. Po wygenerowaniu planszy losowo usuwane są liczby, aby gracz miał co uzupełniać.

### Sprawdzanie poprawności planszy:
1. Sprawdzenie powtórzeń w kwadratach 3x3.
2. Sprawdzenie powtórzeń w kolumnach.
3. Sprawdzenie powtórzeń w wierszach.

## Biblioteki

- `ncurses` - Tworzenie interfejsu TUI.
- `string` - Obsługa typu `string`.
- `algorithm` - Algorytm `std::shuffle` do tasowania liczb.
- `random` - Generatory liczb pseudolosowych.

## Instrukcja użytkownika

### Kompilacja programu

#### Linux
1. Wymagana biblioteka `ncurses` oraz kompilator `g++`.
2. Użyj skryptu `build.sh`:
   ```bash
   ./build.sh
   ```
   lub uruchom wcześniej skompilowaną wersję.

#### Windows
1. Wymagany `MinGW` oraz biblioteka `ncurses`.
2. Użyj skryptu `build_win_prod.sh`:
   ```bash
   ./build_win_prod.sh
   ```
   Skrypt w teorii kompiluje dla Windowsa, jednak wymaga dodatkowej pracy i edycji, aby kompilator znalazł bibliotekę `ncurses`.

### Obsługa menu
- Nawigacja strzałkami, potwierdzenie wyborem `Enter`.
- Opcja "Zasady" pozwala zapoznać się z zasadami.
- Opcja "Graj!" rozpoczyna rozgrywkę.

### Sterowanie w trakcie gry
- Wybór pola strzałkami.
- Wpisanie liczby `1-9`, `0` do wyczyszczenia pola.
- Stałe liczby są białe, liczby wpisane przez użytkownika są czerwone.
- `Q` - Powrót do menu.
- Po poprawnym uzupełnieniu planszy pojawia się komunikat "Gratulacje!".
- `Q` pozwala wrócić do menu lub rozpocząć nową rozgrywkę.
- Opcja "Wyjdź" kończy działanie programu.

## Podsumowanie i wnioski

Projekt pozwolił na samodzielne stworzenie algorytmu generowania plansz sudoku oraz interfejsu w `ncurses`. Program działa poprawnie na systemie Linux, jednak występują problemy ze skalowaniem interfejsu w Windows 11.
