#include "Calculator.h"

void Calculator::run(){
    //game loop with check for mouse and keyboard events(inputs)
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { //if the user clicks the X
                running = false;
            }
            /*
            else if(event.type == SDL_MOUSEMOTION){
                    SDL_GetMouseState(&rect1.x,&rect1.y);
            }
            */
            else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){         
                    case SDLK_a:
                        cout << "Key A: was pressed\n";
                        rect12.x -= DELTA;
                        break;
                    case SDLK_w:
                        cout << "Key W: was pressed\n";
                        rect12.y -= DELTA;
                        break;
                    case SDLK_d:
                        cout << "Key D: was pressed\n";
                        rect12.x += DELTA;
                        break;
                    case SDLK_s:
                        cout << "Key S: was pressed\n";
                        rect12.y += DELTA;
                        break;
                }
            }
            
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                ToggleRect(x, y);
            }
        }
        SDL_SetRenderDrawColor(renderer, 36, 36, 36, 0); 
        SDL_RenderClear(renderer);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        for(int i = 0;i<rects.size(); i++){
            SDL_RenderFillRect(renderer,&rects[i]);
        }
        SDL_SetRenderDrawColor(renderer, 110, 110, 110, 0); 
        SDL_RenderFillRect(renderer,&bar);
        

        SDL_RenderPresent(renderer);
        //SDL_Delay(10);    
    }
}

void Calculator::ToggleRect(int MouseX, int MouseY)
{
    
    SDL_Point MousePos;
    MousePos.x = MouseX;
    MousePos.y = MouseY;
    for (int i = 0; i < rects.size(); i++)
    {
        if (SDL_PointInRect(&MousePos, &rects[i])) 
        {      
            cout << i << endl;
        }
       
    }
}

void Calculator::addKey(string input){
    keys.push_back(input);
}


string Calculator::removeKey(){
    string key;
    key = keys[keys.size()-1];
    keys.pop_back();
    return key;
}

void Calculator:: displayKeys() const{
    cout << endl;
    for(int i = 0; i<keys.size()-1; i++){
        cout << keys[i] << " ";
    }
}