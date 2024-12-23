#include "Calculator.h"

void Calculator::run(){
    
    //game loop with check for mouse and keyboard events(inputs)
    string barDisplay = " ";
    bool running = true;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { //if the user clicks the X
                running = false;
            }
            if(barDisplay.length()<7){ //if the bar is not full allow any key
                if(event.type == SDL_KEYDOWN){
                    switch (event.key.keysym.sym){         
                        case SDLK_1:
                            cout << "Key 1: was pressed\n";
                            barDisplay+="1";
                            break;
                        case SDLK_2:
                            cout << "Key 2: was pressed\n";
                            barDisplay+="2";
                            break;
                        case SDLK_3:
                            cout << "Key 3: was pressed\n";
                            barDisplay+="3";
                            break;
                        case SDLK_4:
                            cout << "Key 4: was pressed\n";
                            barDisplay+="4";
                            break;
                        case SDLK_5:
                            cout << "Key 5: was pressed\n";
                            barDisplay+="5";
                            break;
                        case SDLK_6:
                            cout << "Key 6: was pressed\n";
                            barDisplay+="6";
                            break;
                        case SDLK_7:
                            cout << "Key 7: was pressed\n";
                            barDisplay+="7";
                            break;
                        case SDLK_8:
                            cout << "Key 8: was pressed\n";
                            barDisplay+="8";
                            break;
                        case SDLK_9:
                            cout << "Key 9: was pressed\n";
                            barDisplay+="9";
                            break;
                        case SDLK_0:
                            cout << "Key 0: was pressed\n";
                            barDisplay+="0";
                            break;
                        case SDLK_PLUS:
                            cout << "Key +: was pressed\n";
                            barDisplay+="+";
                            break;
                        case SDLK_MINUS:
                            cout << "Key -: was pressed\n";
                            barDisplay+="-";
                            break;
                        case SDLK_ASTERISK:
                            cout << "Key *: was pressed\n";
                            barDisplay+="*";
                            break;
                        case SDLK_SLASH:
                            cout << "Key /: was pressed\n";
                            barDisplay+="/";
                            break;
                        case SDLK_EQUALS:
                            cout << "Key =: was pressed\n";
                            barDisplay+="=";
                            this->doOperation(barDisplay);
                            break;
                        case SDLK_PERIOD:
                            cout << "Key .: was pressed\n";
                            barDisplay+=".";
                            break;    
                        case SDLK_BACKSPACE:
                            cout << "Key delete: was pressed\n";
                            if(barDisplay.length()==1){ //if there is a single character left, delete it and add a white space
                                barDisplay = " ";
                            }
                            else{
                                barDisplay.pop_back();    
                            }
                            break;    
                    }
                }
            }
            else if(barDisplay.length()>=7){ //if the bar is full only allow the delete key,
                if(event.type == SDL_KEYDOWN){
                    switch (event.key.keysym.sym){  
                        case SDLK_BACKSPACE:
                            cout << "Key delete: was pressed\n";
                            barDisplay.pop_back();
                            break;  
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                pressButton(x, y, barDisplay);
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 36, 36, 36, 0); //background color
        SDL_RenderClear(renderer);
            
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        for(int i = 0;i<rects.size(); i++){
            SDL_RenderFillRect(renderer,&rects[i]);
        }
        //for loading in the buttons
        for(int i = 0; i < rects.size(); i++){
            auto iter = mapper.find(rects[i]);
            surfaceMessage = TTF_RenderText_Solid(font, iter->second.c_str(), WHITE);
            buttonMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_FreeSurface(surfaceMessage); // Free the surface to avoid memory leaks
            SDL_RenderCopy(renderer, buttonMessage, NULL, &rects[i]);
            SDL_DestroyTexture(buttonMessage); // Free the texture after rendering
        }
        
        SDL_SetRenderDrawColor(renderer, 110, 110, 110, 0); //the color we are about to render
        SDL_RenderFillRect(renderer,&bar); //color above to this is rendered into the bar
        
        surfaceMessage = TTF_RenderText_Solid(font, barDisplay.c_str(), WHITE); //sub back for two upper lines
        barMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //message itself;
        SDL_GetClipRect(surfaceMessage, &bar); //this will handle the text so it doesnt get smooshed
        SDL_RenderCopy(renderer, barMessage, NULL, &bar);

        //to revert, take what is in the else and delete the if and else
        SDL_DestroyTexture(barMessage); //free the message for the bar so it doesnt get overwritten
        SDL_FreeSurface(surfaceMessage);

        SDL_RenderPresent(renderer);
        if(barDisplay == "ERROR!!!"){
            SDL_Delay(700);
            barDisplay = " "; 
        }
        
    }
}


void Calculator::pressButton(int MouseX, int MouseY, string &barMessage)
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
            barMessage+=iter->second;
            if(iter->second == "="){
                this->doOperation(barMessage);
            }
        }
           
    }
}

void Calculator::doOperation(string& barDisplay){
    //check that +-=/ do not come one after another
    //check that a decimal sign must be between two numbers
    //decimal cannot show up more than once in a string, because we can have multiple of the other operations
    double res;
    int count = 0;
    if([&](string s) { for(char c:s){ if(c == '.'){count++;}} return count; }(barDisplay) > 1){
        barDisplay = "ERROR!!!";
    }
    else if(!this->validTwoPointerCheck(barDisplay)){
        barDisplay = "ERROR!!!";
    }
    else{
        this->parseValidInput(barDisplay);
    }
}

bool Calculator::validTwoPointerCheck(string s){
    string operations[4] = {"+","-","*","/"};
    //will use this function to check if any of the operator chars come back to back
    //if check if the string is only a single character(cant be only a single char) then that character must not be in the list of operations, we actually dont need to check this as they need 
    //type at least two character, something and = or equal by itself
    
    if(s == "=" ){ //if theu user only enters the equal sign
        return true;
    }//checks if the first character is an operator
    else if(s[1] == operations[0][0] ||s[1] == operations[1][0] ||s[1] == operations[2][0] ||s[1] == operations[3][0]){ //checks that the first element of the input is not an operation
        return false;
    }//thing before and after operator must be two numbers
    //else if()
    else{ //checks that none of the operations come back to back
        int first = 0;
        int next = first+1;
        while(next < s.length()){
            for(int i = 0; i <4; i++){ //checks if two consecutive characters both are also within the operations array
                if(s[first] == operations[i][0] && (s[next] == operations[0][0] || s[next] == operations[1][0] ||s[next] == operations[2][0] ||s[next] == operations[3][0])){ 
                    return false;
                }
            }   
            first++;
            next++;
        }
        return true;
    }   
}

void Calculator::parseValidInput(string &s){
    //all the logic to do the actual computation on a valid user input
    s = "VALID!!!";
    //PEMDAS
}
