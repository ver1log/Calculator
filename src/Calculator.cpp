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
            if(barDisplay.length()<9){ //if the bar is not full allow any key
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
                            //barDisplay+="=";
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
            else if(barDisplay.length()>=9){ //if the bar is full only allow the delete key,
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
        SDL_RenderFillRect(renderer, &delRect); //fill the delete buttons color
        //for loading in the buttons
        for(int i = 0; i < rects.size()-1; i++){ //stop one early, before the delete button
            auto iter = mapper.find(rects[i]);
            surfaceMessage = TTF_RenderText_Solid(font, iter->second.c_str(), WHITE);
            buttonMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_FreeSurface(surfaceMessage); // Free the surface to avoid memory leaks
            SDL_RenderCopy(renderer, buttonMessage, NULL, &rects[i]);
            SDL_DestroyTexture(buttonMessage); // Free the texture after rendering
        }
        //rendering the delete button
        surfaceMessage = TTF_RenderText_Solid(font, "DEL", WHITE);
        buttonMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_RenderCopy(renderer, buttonMessage, NULL, &delRect);
        SDL_DestroyTexture(buttonMessage); // Free the texture after rendering
        SDL_FreeSurface(surfaceMessage); // Free the surface to avoid memory leaks
        //render clear button
        surfaceMessage = TTF_RenderText_Solid(font, "CLR", WHITE);
        buttonMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_RenderCopy(renderer, buttonMessage, NULL, &clrRect);
        SDL_DestroyTexture(buttonMessage); // Free the texture after rendering
        SDL_FreeSurface(surfaceMessage); // Free the surface to avoid memory leaks
        //render negative button
        surfaceMessage = TTF_RenderText_Solid(font, "NEG", WHITE);
        buttonMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_RenderCopy(renderer, buttonMessage, NULL, &negRect);
        SDL_DestroyTexture(buttonMessage); // Free the texture after rendering
        SDL_FreeSurface(surfaceMessage); // Free the surface to avoid memory leaks

        //rendering the user bar
        SDL_SetRenderDrawColor(renderer, 110, 110, 110, 0); //the color we are about to render
        SDL_RenderFillRect(renderer,&bar); //color above to this is rendered into the bar
        surfaceMessage = TTF_RenderText_Solid(font, barDisplay.c_str(), WHITE); //sub back for two upper lines
        barMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //message itself;
        if(barDisplay == " "){
            SDL_RenderCopy(renderer, barMessage, NULL, &bar);
        }
        else{
            SDL_GetClipRect(surfaceMessage, &bar); //this will handle the text so it doesnt get smooshed
            SDL_RenderCopy(renderer, barMessage, NULL, &bar);
        }
        
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
            if(barMessage.length() < 9){ //allow any key
                if(iter->second == "DEL"){
                   if(barMessage.length()==1){ //if there is a single character left, delete it and add a white space
                            barMessage = " ";
                        }
                    else{
                        barMessage.pop_back();    
                    }
                    return; 
                }
                else if(iter->second == "CLR"){
                    barMessage = " ";
                    return;
                }
                else if(iter->second == "NEG"){
                    barMessage+="N";
                    return;
                }
                barMessage+=iter->second;
                if(iter->second == "="){
                    barMessage.pop_back();
                    this->doOperation(barMessage);
                } 
            }
            else if(barMessage.length() >= 9){ //only allow the delete and clear button
                if(iter->second == "DEL"){
                    barMessage.pop_back();
                } 
                else if(iter->second == "CLR"){
                    barMessage = " ";
                }
            }
        }
           
    }
}

void Calculator::doOperation(string& barDisplay){
    //check that +-=/ do not come one after another
    //check that a decimal sign must be between two numbers
    //decimal cannot show up more than once in a string, because we can have multiple of the other operations
    if(!this->isValidInput(barDisplay)){
        barDisplay = "ERROR!!!";
    }
    else{
        this->parseValidInput(barDisplay);
    }
}

bool Calculator::isValidInput(string s){
    string operations[5] = {"+","-","*","/","."};
    //will use this function to check if any of the operator chars come back to back
    //if check if the string is only a single character(cant be only a single char) then that character must not be in the list of operations, we actually dont need to check this as they need 
    //type at least two character, something and = or equal by itself
    
    if(s == " =" ){ //if the user only enters the equal sign
        return true;
    }//checks if the first character is an operator(except the ".")
    else if(s[1] == operations[0][0] ||s[1] == operations[1][0] ||s[1] == operations[2][0] ||s[1] == operations[3][0]){ //checks that the first element of the input is not an operation
        return false;
    }//checks if the last character is an operator(including the ".")
    else if(s[s.length()-1] == operations[0][0] ||s[s.length()-1] == operations[1][0] ||s[s.length()-1] == operations[2][0] ||s[s.length()-1] == operations[3][0] || s[s.length()-1] == operations[4][0]){
        //cout << ":" << s << endl;
        return false;
    }
    else if(s.find('N') != std::string::npos){
        for(int i = 0; i< s.length(); i++){
            if(s[i] == 'N' && i == s.length()-1){
                return false;
            }
            else if(s[i] == 'N' && i != s.length()-1 && i != 0){
                if(s[i] == operations[0][0] ||s[i] == operations[1][0] ||s[i] == operations[2][0] ||s[i] == operations[3][0]){
                    return false;
                }
            }
        }
        if(s.length() == 1){
            return false;
        }
        return true;
    }
    //figure out a way to handle the case where a decimal comes right before a operator->invalid, if it comes after it is valid
    else{ //checks that none of the operations come back to back
        //cout << ":" << s << "|\n";
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
        //the number of decimals should be at most equal to the number of operators+1, if not it is invalid   
        int count = 0;
        //get the number of decimals
        int numberofDecimals = [&](string str){ for(char c:s){ if(c == '.'){count++;}} return count; }(s);
        count = 0;
        //get the number of operators and using
        for(int i = 0; i<s.length(); i++){
            if(s[i] == operations[0][0] ||s[i] == operations[1][0] ||s[i] == operations[2][0] ||s[i] == operations[3][0]){
                count++;
            }
        }
        int numberofOperations = count;
        //compare the number of decimals to the number of operations,
        if(numberofDecimals-1 > numberofOperations){
            return false;
        }
        //last check, if a decimal appears its next element should not be an operation or it must be a number
        int index = 0; //start initially
        //example: string 1.7+3.+4
        while((index = s.find('.',index)) != std::string::npos){
            //cout << "decimal @ index: " << index << endl;
            if(!isdigit(s[index+1])){//(operations[0][0] )){||operations[1][0] || operations[2][0] || operations[3][0])){
                return false;
            }
            index+=s.find('.',index);
        }
        return true;
        //for example 1.3+7.0-5.7, 3 decimals ma
    }
    
}

void Calculator::parseValidInput(string &s){
    //all the logic to do the actual computation on a valid user input
    //break the string into elements of a vector<string>
    //loop until there is only one element left inside the vector
        //we will loop until we find an element of highest presence and then switch the element we are looking for once we no longer see that element
        //evaluate the element before and after the operator in respect to the operator, ex 2+3 the two elements would be 2 and 3 
        //once those three elements are evaluated place the output inside the element where the operator was and shift everything to the left, to shift convert to string
        //check the next operator with highest presedence
    //repeat this process until a single non-empty element remains or there a single actual element remains
    

    //precedence arrays
    string MD[2] = {"*","/"}; //set these elements to 0 when they no longer appear in the array, this tells us to 
    string AS[2] = {"+","-"};
    vector<string> str = convertToList(s);
    if(str.size() == 1){
        return;
    }
    //last checking, for undefined
    for(int i = 0; i<str.size(); i++){
        if(str[i] == "/"){
            if(str[i+1] == "0"){
                s = " UNDEF!!!";
                return;
            }
        }
    }

    for(string e:str){
        cout << e << ",";
    }
    cout << endl;
    string placeHolder = "";
    double res = 0;
    while(str.size() != 1){ //continue while we did not get the final result
    cout << "entered whole\n";
        int operatorIndex = 0;
        while(MD[0] != "0" && MD[1] != "0"){ //do the multpily and divide operation until there are still 
            //loop until either of the operators are encountered
            //do the actual operation
            //put the result inside the position of the operator
            //place "" in the index before and after
            //convert to a string 
            //convert back to a list
            for(int i = 0; i <str.size(); i++){
                if(str[i] == "*"){ //if the operator is encountered
                cout << "entered mul\n";
                    operatorIndex = i;
                    if(str[i-1][1] == 'N' && str[i+1][0] == 'N'){
                        str[i-1][1] = str[i+1][0] = ' '; 
                        res += ((-stod(str[i-1]))*(-stod(str[i+1])));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0;
                    }
                    else if(str[i-1][1] == 'N'){ 
                        str[i-1][1] = ' '; 
                        res += ((-stod(str[i-1]))*(stod(str[i+1])));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0;
                    }
                    else if(str[i+1][0] == 'N'){
                        str[i+1][0] = ' '; 
                        res += ((stod(str[i-1]))*(-stod(str[i+1])));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0;
                    }
                    else{
                        res += (stod(str[i-1])*stod(str[i+1])   );
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0; 
                    }
                    
                } 
                else if(str[i] == "/"){
                    cout << "entered div\n";
                    operatorIndex = i;
                    if(str[i-1][1] == 'N' && str[i+1][0] == 'N'){
                        str[i-1][1] = str[i+1][0] = ' '; 
                        res += ((-stod(str[i-1]))/(-stod(str[i+1])));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0;
                    }
                    else if(str[i-1][1] == 'N'){
                        str[i-1][1] = ' '; 
                        res += ((-stod(str[i-1]))/(stod(str[i+1])));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0;
                    }
                    else if(str[i+1][0] == 'N'){
                        str[i+1][0] = ' '; 
                        res += ((stod(str[i-1]))/(-stod(str[i+1])));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0;
                    }
                    else{
                        res += (stod(str[i-1])/stod(str[i+1])   );
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i = 0; 
                    }
                    
                }
                placeHolder = convertToString(str);
                str = convertToList(placeHolder);
                res = 0; //reset the temp value
                if(count(str.begin(),str.end(), "*") == 0){
                    MD[0] = "0";
                }
                if(count(str.begin(),str.end(), "/") == 0){
                    MD[1] = "0";
                }
                cout <<"Mul/div operation"<< endl;
                    for(string e:str){
                        cout << e << " , ";
                    }
            }
        }
        if(MD[0] == "0" && MD[1] == "0"){ //start doing the add and sub operation once the multiply and divide operator are not in the list
            while(AS[0] != "0" && AS[1] != "0"){
                for(int i = 0; i <str.size(); i++){
                    if(str[i] == "+"){
                        cout << "entered add\n";
                        operatorIndex = i;
                        if(str[i-1][1] == 'N' && str[i+1][0] == 'N'){
                            str[i-1][1] = str[i+1][0] = ' '; 
                            res += ((-stod(str[i-1]))+((-stod(str[i+1]))));
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0;
                        }
                        else if(str[i-1][1] == 'N'){ 
                            str[i-1][1] =  ' ';
                            res += ((-stod(str[i-1]))+(stod(str[i+1])));
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0;
                        }
                        else if(str[i+1][0] == 'N'){
                            str[i+1][0] = ' ';
                            res += ((stod(str[i-1]))+((-stod(str[i+1]))));
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0;
                        }
                        else{
                            res += (stod(str[i-1])+stod(str[i+1])   );
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0; 
                        }
                        /*
                        operatorIndex = i;
                        res += (stod(str[i-1])+stod(str[i+1]));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i=0;
                        */
                    }
                    else if(str[i] == "-"){
                        cout << "entered sub\n";
                        operatorIndex = i;
                        if(str[i-1][1] == 'N' && str[i+1][0] == 'N'){
                            str[i-1][1] = str[i+1][0] = ' ';
                            res += ((-stod(str[i-1]))-((-stod(str[i+1]))));
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0;
                        }
                        else if(str[i-1][1] == 'N'){ 
                            str[i-1][1] =  ' ';
                            res += ((-stod(str[i-1]))-(stod(str[i+1])));
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0;
                        }
                        else if(str[i+1][0] == 'N'){
                            str[i+1][0] = ' ';
                            res += ((stod(str[i-1]))-((-stod(str[i+1]))));
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0;
                        }
                        else{
                            res += (stod(str[i-1])-stod(str[i+1]));
                            str[i-1] = str[i+1] = "";
                            str[operatorIndex] = to_string(res);
                            i = 0; 
                        }
                        /*
                        operatorIndex = i;
                        res += (stod(str[i-1])-stod(str[i+1]));
                        str[i-1] = str[i+1] = "";
                        str[operatorIndex] = to_string(res);
                        i=0;
                        */
                    }
                    placeHolder = convertToString(str);
                    str = convertToList(placeHolder);
                    res = 0; //reset the temp value
                    if(count(str.begin(),str.end(), "+") == 0){
                        AS[0] = "0";
                    }
                    if(count(str.begin(),str.end(), "-") == 0){
                        AS[1] = "0";
                    }
                    cout <<"Add/sub operation"<< endl;
                    for(string e:str){
                        cout << e << " , ";
                    }
                }
            }
        }
        placeHolder = " " + convertToString(str);
        str = convertToList(placeHolder);    
    }
    if(placeHolder.length()>8){
        placeHolder = placeHolder.erase(8); 
    }
    /*
    if(auto i = placeHolder.find('N') != std::string::npos){
        placeHolder[i] = '-';
    }
    */
    s = placeHolder;
    //PEMDAS
}

vector<string> Calculator::convertToList(string s)
{
    //second parameter of substr is the number of elements foward we will be accounting for 
    vector<string> result;
    int lookupIndex = 0; //index to look ahead will be incremented each iteration
    int currentIndex = 0; //will only be incremented to the lookup index when special char is encountered
    int countOperations = 0;
    while(lookupIndex < s.length()){ //while we can still look at the elements
        if(s[lookupIndex] == '*' || s[lookupIndex] == '/' || s[lookupIndex] == '+' || s[lookupIndex] == '-'){ //if we encouter the special characters
            result.push_back(s.substr(currentIndex,(lookupIndex-currentIndex))); //add the substring of where our current pointer is at to the element before the operation ones to the vector
            result.push_back(string(1, s[lookupIndex])); //add the operation to the vector
            //s.replace(currentIndex,lookupIndex,""); //set the substring that we added to vector from the string to empty
            lookupIndex++; //increment the looking ahead index to the next element
            currentIndex = lookupIndex; //set the current to the index after the operation element
            countOperations++;
        }
        else{ //if we dont encounter an operand, only increment the looking ahead index, current stays in the same position
            lookupIndex++;
        }
    }
    //the number of elements in the vector is (number of operand+number of numbers(operands+1))
    if(result.size() != (countOperations+countOperations+1)){
        cout << "test!\n";
        result.push_back(s.substr(currentIndex,s.length() - currentIndex)); //push the remaining part of the string onto the vector
    }
    return result;
}

string Calculator::convertToString(vector<string> vect)
{
    string res = "";
    for(int i = 0; i<vect.size(); i++){
        if(vect[i].length() > 1 && vect[i][0] == '-'){
            vect[i][0] = 'N';
        }
        res+=vect[i];
    }
    return res;
}
