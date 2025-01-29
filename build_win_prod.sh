g++ ./main.cpp ./validation.cpp ./menu.cpp ./sudoku.cpp ./main.h -o build/main.exe -O3 -DNCURSES_STATIC -I/mingw64/include/ncurses -L/mingw64/lib -static -lncurses
echo "Build!"
./build/main.exe