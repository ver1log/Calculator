all:
	g++ -Isrc/Include -I/usr/include/SDL2 -c Calculator.cpp -o Calculator.o
	g++ -Isrc/Include -I/usr/include/SDL2 -c main.cpp -o main.o
	g++ -Isrc/Include -Lsrc/lib main.o Calculator.o -o main.exe -lmingw32 -lSDL2main -lSDL2
clean:
	del -f *.o main.exe