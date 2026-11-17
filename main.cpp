// Standard input/output and string headers
#include <iostream>
#include<string>
// Custom calculator header containing Calculate, History, and Controller classes
#include "Calculate.h"

// Application entry point
int main(){
    
    // Instantiate the main Controller object to manage state and execution flow
    Controller user;
    // Launch the interactive CLI calculator menu loop
    user.manager();

    // Exit program cleanly
    return 0;
}