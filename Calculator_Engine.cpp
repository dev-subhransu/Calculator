#include <iostream>
#include <string>
#include "Calculate.h"

// Shorthand macro for standard console output
#define print(x) std::cout << x

// ============================================================================
// Calculate Class Methods
// ============================================================================

// Adds number_1 and number_2, updates result, and displays the answer
double Calculate::Addition(){
    result = number_1 + number_2;
    print("Answer: " << result << "\n");
    return result;
}

// Subtracts number_2 from number_1, updates result, and displays the answer
double Calculate::Substraction(){
    result = number_1 - number_2;
    print("Answer: " << result << "\n");
    return result;
}

// Multiplies number_1 and number_2, updates result, and displays the answer
double Calculate::Multiplication(){
    result = number_1 * number_2;
    print("Answer: " << result << "\n");
    return result;
}

// Divides number_1 by number_2 while guarding against division by zero
double Calculate::Division(){
    if (number_2 == 0){
        print("Cannot divide by Zero" << "\n");
    }else{
        result = (number_1/number_2);
        print("Answer: " << result << "\n");
    }
    return result;
}

// Casts operands to integers and computes remainder, guarding against modulus by zero
int Calculate::Modulus(){
     if (number_2 == 0){
        print("Cannot divide by Zero" << "\n");
    }else{
        result = static_cast<int>(number_1)%static_cast<int>(number_2);
        print("Answer: " << result << "\n");
        return result;
    }
}

// Resets the active calculation result to 0
double Calculate::reset_result(){
    result = 0;
    return result;
}

// Returns the current stored calculation result
double Calculate::get_result(){
    result;
    return result;
}

// ============================================================================
// History Class Methods
// ============================================================================

// Converts numeric operands into string representations for history storage
void History::cast_numbers(){
    if (count == 0){
        // First operation requires casting both initial operands
        casted_number1 = std::to_string(number_1);
        casted_number2 = std::to_string(number_2);
    }else{
        // Chained operations only need the newly entered second operand
        casted_number2 = std::to_string(number_2);
    }
}

// Dynamically resizes the raw pointer array and appends the latest operation
void History::store_history(){
    if(count == 0){
        // Initial allocation stores the starting operand and first operator+operand pair
        Temp_history = new std::string[count + 2];
        Temp_history[0] = casted_number1;
        Temp_history[1] = operation + casted_number2;
    }else{
        // Copy existing history into a larger temporary buffer and free old memory
        Temp_history = new std::string[count + 2];
        for (int i = 0; i <= count; i++ ){
            Temp_history[i] = user_history[i]; 
        }
        delete[] user_history;
        user_history = nullptr;
        Temp_history[count + 1] = operation + casted_number2;
    }
    // Commit resized buffer back to user_history and clean up temporary pointer
    user_history = new std::string[count + 2];
    for (int i = 0; i <= count + 1; i++){
        user_history[i] = Temp_history[i];
    }
    delete[] Temp_history;
    Temp_history = nullptr;
    count++;
}

// Displays all stored calculation steps or prompts user if history is empty
void History::show_history(){

    if(count == 0){
        print("Bro, history doesn't appear out of thin air. Calculate something first!" << "\n");
    }else{
        print("Total Number of Operations: " << count << "\n");
        for (int i = 0; i <= count; i++)
        {
            print("Operand No: " << i << ": " << user_history[i] << "\n");
        }
    }
}

// Deallocates dynamic history array from heap memory and resets counter
void History::delete_history(){
    delete[] user_history;
    user_history = nullptr;
    count = 0;
}

// Returns the total count of valid operations recorded
int History::get_count(){
    count;
    return count;
}

// ============================================================================
// Controller Class Methods
// ============================================================================

// Captures operands and operator; intercepts invalid operators immediately
void Controller::get_user_expression(){
    if(get_count() == 0){
        // Fresh calculation mode: prompt for both operands
        print("\nEnter number 1: ");
        std::cin >> Calculate::number_1;
        print("\nChoose an operation(+, -, *, /, %): ");
        std::cin >> Calculate::operation;
        if(Controller::get_enum_op() == Operations::INVALID){
            return;
        }
        print("\nEnter number 2: ");
        std::cin >> Calculate::number_2;
    }else{
        // Chained calculation mode: carry forward previous result as number_1
        number_1 = get_result();
        print("\nNumber 1: " << get_result());
        print("\nChoose an operation(+, -, *, /, %): ");
        std::cin >> Calculate::operation;
        if(Controller::get_enum_op() == Operations::INVALID){
            return;
        }
        print("\nEnter number 2: ");
        std::cin >> Calculate::number_2;
    }
}

// Maps the user's string operator input to a strongly-typed Operations enum
Controller::Operations Controller::get_enum_op(){
    if (Calculate::operation == "+"){
        return Operations::ADD;
    }else if (Calculate::operation == "-"){
        return Operations::SUB;
    }else if (Calculate::operation == "*"){
        return Operations::MULTI;
    }else if (Calculate::operation == "/"){
        return Operations::DIV;
    }else if (Calculate::operation == "%"){
        return Operations::MOD;
    }else{
        return Operations::INVALID;
    }   
}

// Dispatches execution to the appropriate arithmetic method based on enum value
void Controller::do_calculations(){
    switch (Controller::get_enum_op()){
        case Operations::ADD:
            Calculate::Addition();
            break;
        case Operations::SUB:
            Calculate::Substraction();
            break;
        case Operations::MULTI:
            Calculate::Multiplication();
            break;
        case Operations::DIV:
            Calculate::Division();
            break;
        case Operations::MOD:
            Calculate::Modulus();
            break;
        default:
            Operations::INVALID;
            print("\nCan't you read? It literally says (+, -, *, /, %) right there!\n");
            break;
    }
}

// Filters out invalid operators and division/modulus-by-zero traps from history
bool Controller::should_save_history(){
    bool condition = true;
    if(Controller::get_enum_op() == Operations::INVALID){
        condition = false;
        return condition;
    }else if ((get_enum_op() == Operations::DIV) || (get_enum_op() == Operations::MOD)){
        if (number_2 == 0){
            condition = false;
        }
        return condition;
    }else{
        return condition;
    }
}

// Main application event loop handling menu navigation and execution pipeline
void Controller::manager(){
    do{
        print("\n===========Main Menu===========");
        print("\n          1.Calculate          ");
        print("\n           2.History           ");
        print("\n            3.Reset            ");
        print("\n            4.Exit             ");
        print("\nEnter your choice: ");
        std::cin >> Controller::choice;
        switch (choice)
        {
        case 1:
            Controller::get_user_expression();
            Controller::do_calculations();
            History::cast_numbers();
            if(Controller::should_save_history()){
                History::store_history();
            }
            break;
        case 2:
            History::show_history();
            break;
        case 3:
            History::delete_history();
            Calculate::reset_result();
            break;
        case 4:
            print("System Closing....");
            break;
        default:
            print("Are you blind and cant't see the main menu!");
            break;
        }
    }while(choice != 4);
}