all:
	g++ -Isdl/Include -I/usr/include/SDL2 -c src/Calculator.cpp -o Calculator.o
	g++ -Isdl/Include -I/usr/include/SDL2 -c src/main.cpp -o main.o
	g++ -Isdl/Include -Lsdl/lib main.o Calculator.o -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
clean:
	del -f *.o main.exe