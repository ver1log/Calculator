# Detect OS, if it is windows it will have an output if on mac or linux it will be linux or darwin for mac
OS := $(shell uname 2>/dev/null || echo Windows_NT)
#if OS is windows
ifeq ($(OS), Windows_NT)
all:
	g++ -Isdl/include -c src/Calculator.cpp -o Calculator.o
	g++ -Isdl/include -c src/main.cpp -o main.o
	g++ -Lsdl/lib main.o Calculator.o -o main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

clean:
	del /f *.o main.exe
#if on linux/mac
else
all:
	g++ -I/usr/include/SDL2 -c src/Calculator.cpp -o Calculator.o
	g++ -I/usr/include/SDL2 -c src/main.cpp -o main.o
	g++ main.o Calculator.o -o main -lSDL2 -lSDL2_ttf

clean:
	rm -f *.o main
endif

#explaining what is done in the first two lines of the all command
# the -I tells the program where to look for the header files which are needed for compliation
#since we are compiling and not linking in the first two lines we use the -c file 
#the reason why the Isld/include, include can be capitalized is that windows is case insensitve
#we only compile the .cpp to object files
#the stucture is : (compiler) (include headers) -c (source file) -o (object file)

#explaining the last line
#the -L in -Lsdl/lib tells the program where the .a and .dll are at for linking(we already complied), these contain all the functions 
#.dll are dynamically linked librarys and are brought in only when they are needed at program runtime 
#while the .a are static and are loaded in when the program is linked in makefile, but during program compile time
#we then link the object files into the execuatble, the linking librarys are needed at this point
#the -l(lowercase L) is used to now link to the specific librarys that were clarified in the sdl/lib directory