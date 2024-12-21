#include "Calculator.h"

void Calculator::run(){
    //game loop with check for mouse and keyboard events(inputs)
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { //if the user clicks the X
                running = false;
            }
            else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){         
                    case SDLK_1:
                        cout << "Key 1: was pressed\n";
                        break;
                    case SDLK_2:
                        cout << "Key 2: was pressed\n";
                        break;
                    case SDLK_3:
                        cout << "Key 3: was pressed\n";
                        break;
                    case SDLK_4:
                        cout << "Key 4: was pressed\n";
                        break;
                    case SDLK_5:
                        cout << "Key 5: was pressed\n";
                        break;
                    case SDLK_6:
                        cout << "Key 6: was pressed\n";
                        break;
                    case SDLK_7:
                        cout << "Key 7: was pressed\n";
                        break;
                    case SDLK_8:
                        cout << "Key 8: was pressed\n";
                        break;
                    case SDLK_9:
                        cout << "Key 9: was pressed\n";
                        break;
                    case SDLK_0:
                        cout << "Key 0: was pressed\n";
                        break;
                    case SDLK_PLUS:
                        cout << "Key +: was pressed\n";
                        break;
                    case SDLK_MINUS:
                        cout << "Key -: was pressed\n";
                        break;
                    case SDLK_ASTERISK:
                        cout << "Key *: was pressed\n";
                        break;
                    case SDLK_SLASH:
                        cout << "Key /: was pressed\n";
                        break;
                    case SDLK_EQUALS:
                        cout << "Key =: was pressed\n";
                        break;
                    case SDLK_PERIOD:
                        cout << "Key .: was pressed\n";
                        break;    
                }
            }
            
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                pressButton(x, y);
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


        surfaceMessage = TTF_RenderText_Solid(font, "0000000000000000", WHITE);
        barMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //message itself;
        SDL_RenderCopy(renderer, barMessage, NULL, &bar);
        SDL_DestroyTexture(barMessage); //free the message for the bar so it doesnt get overwritten
          
        for(int i = 0; i < rects.size(); i++){
            auto iter = mapper.find(rects[i]);
            surfaceMessage = TTF_RenderText_Solid(font, iter->second.c_str(), WHITE);
            buttonMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_FreeSurface(surfaceMessage); // Free the surface to avoid memory leaks
            SDL_RenderCopy(renderer, buttonMessage, NULL, &rects[i]);
            SDL_DestroyTexture(buttonMessage); // Free the texture after rendering
        }
        
        SDL_RenderPresent(renderer);
        
    }
}

void Calculator::pressButton(int MouseX, int MouseY)
{
    
    SDL_Point MousePos;
    MousePos.x = MouseX;
    MousePos.y = MouseY;
    for (int i = 0; i < rects.size(); i++)
    {
        if (SDL_PointInRect(&MousePos, &rects[i])) 
        {      
            auto iter = mapper.find(rects[i]);
            cout << iter->second << " was pressed" << endl;
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