#include <iostream>
#include <SDL2/SDL.h>
#include "Calculator.h"
#include <vector>
using namespace std;
///what is my plan
//1.create a 3-4 grid, later will add a row that displays the current operations
        /*
        0 1 2 3 +
        4 5 6 7 -
        8 9 8 / =
        */
//2.allow user clicks and store them somewhere, 
    //calcultor class with a vector of strings that stores in each element the key that was pressed
//3.when they hit enter display the output done with those operations


int main(int argc, char* argv[]) {
    Calculator calc;
    calc.run();
    
    return 0;
}     
