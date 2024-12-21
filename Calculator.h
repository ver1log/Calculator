#ifndef CALC_H
#define CALC_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int WIDTH = 440;
const int HEIGHT = 500;
const int DELTA = 1;
const int BLOCKWIDTH = 80;
const int BLOCKHEIGHT = 80;
const SDL_Color WHITE = {255, 255, 255};
class Calculator{
    private:
        vector<string> keys;
        SDL_Window* window= nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Event event; //event object
        TTF_Font* font = nullptr;
        SDL_Surface* surfaceMessage = nullptr;
        SDL_Texture* barMessage = nullptr;
        SDL_Texture* buttonMessage = nullptr;
        //set some rectangle fields
        vector<SDL_Rect> rects;
        SDL_Rect bar{10,10,420,50};
        SDL_Rect rect1{0,70,80,80};
        SDL_Rect rect2{121,70,80,80};
        SDL_Rect rect3{241,70,80,80};
        SDL_Rect rect4{361,70,80,80};
        SDL_Rect rect5{0,181,80,80};
        SDL_Rect rect6{121,181,80,80};
        SDL_Rect rect7{241,181,80,80};
        SDL_Rect rect8{361,181,80,80};
        SDL_Rect rect9{0,291,80,80};
        SDL_Rect rect10{121,291,80,80};
        SDL_Rect rect11{241,291,80,80};
        SDL_Rect rect12{361,291,80,80};
        SDL_Rect rect13{0,401,80,80};
        SDL_Rect rect14{121,401,80,80};
        SDL_Rect rect15{241,401,80,80};
        SDL_Rect rect16{361,401,80,80};
        struct SDL_RectComparator
        {
            bool operator()(const SDL_Rect& a, const SDL_Rect& b) const
            {
                if (a.x != b.x) return a.x < b.x;
                if (a.y != b.y) return a.y < b.y;
                if (a.w != b.w) return a.w < b.w;
                return a.h < b.h;
            }
        };
         std::map<SDL_Rect, std::string, SDL_RectComparator> mapper;
    public:
    Calculator(){
        //to get a screen we need both a window and renderer
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
            std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        }
        //init window
        window = SDL_CreateWindow("Calculator", 
                                                SDL_WINDOWPOS_CENTERED, 
                                                SDL_WINDOWPOS_CENTERED, 
                                                WIDTH, HEIGHT, 0);
        if (!window) {
            std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
        //init renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
        rects.push_back(rect1);
        rects.push_back(rect2);
        rects.push_back(rect3);
        rects.push_back(rect4);
        rects.push_back(rect5);
        rects.push_back(rect6);
        rects.push_back(rect7);
        rects.push_back(rect8);
        rects.push_back(rect9);
        rects.push_back(rect10);
        rects.push_back(rect11);
        rects.push_back(rect12);
        rects.push_back(rect13);
        rects.push_back(rect14);
        rects.push_back(rect15);
        rects.push_back(rect16);
        
        mapper.insert(std::make_pair(rect1, "1"));
        mapper.insert(std::make_pair(rect2, "2"));
        mapper.insert(std::make_pair(rect3, "3"));
        mapper.insert(std::make_pair(rect4, "4"));
        mapper.insert(std::make_pair(rect5, "5"));
        mapper.insert(std::make_pair(rect6, "6"));
        mapper.insert(std::make_pair(rect7, "7"));
        mapper.insert(std::make_pair(rect8, "8"));
        mapper.insert(std::make_pair(rect9, "9"));
        mapper.insert(std::make_pair(rect10, "0"));
        mapper.insert(std::make_pair(rect11, "."));
        mapper.insert(std::make_pair(rect12, "+"));
        mapper.insert(std::make_pair(rect13, "-"));
        mapper.insert(std::make_pair(rect14, "*"));
        mapper.insert(std::make_pair(rect15, "/"));
        mapper.insert(std::make_pair(rect16, "="));

        //text stuff
        TTF_Init();
        font = TTF_OpenFont("C:/Users/Main/Desktop/C++ Projects/Calculator/Sans.ttf", 100); //font
        if(!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
            exit(1);
        }
        
        
    }
    ~Calculator(){
        for(int i = keys.size()-1; i<0; i--){
            keys.pop_back();
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(barMessage);
        SDL_DestroyTexture(buttonMessage);
        TTF_CloseFont(font);
        SDL_Quit();
    }
        void addKey(string input); //when a user hits a key
        string removeKey(); //when a user deletes the last inputted key
        void displayKeys() const;
        void run();
        void pressButton(int, int);
};
#endif