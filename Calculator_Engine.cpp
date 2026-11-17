#include <iostream>
#include <string>
#include "Calculate.h"

#define print(x) std::cout << x

double Calculate::Addition(){
    result = number_1 + number_2;
    print("Answer: " << result << "\n");
    return result;
}

double Calculate::Substraction(){
    result = number_1 - number_2;
    print("Answer: " << result << "\n");
    return result;
}

double Calculate::Multiplication(){
    result = number_1 * number_2;
    print("Answer: " << result << "\n");
    return result;
}

double Calculate::Division(){
    if (number_2 == 0){
        print("Cannot divide by Zero" << "\n");
    }else{
        result = (number_1/number_2);
        print("Answer: " << result << "\n");
    }
    return result;
}

int Calculate::Modulus(){
     if (number_2 == 0){
        print("Cannot divide by Zero" << "\n");
    }else{
        result = static_cast<int>(number_1)%static_cast<int>(number_2);
        print("Answer: " << result << "\n");
        return result;
    }
}

double Calculate::reset_result(){
    result = 0;
    return result;
}

double Calculate::get_result(){
    result;
    return result;
}

void History::cast_numbers(){
    if (count == 0){
        casted_number1 = std::to_string(number_1);
        casted_number2 = std::to_string(number_2);
    }else{
        casted_number2 = std::to_string(number_2);
    }
}

void History::store_history(){
    if(count == 0){
        Temp_history = new std::string[count + 2];
        Temp_history[0] = casted_number1;
        Temp_history[1] = operation + casted_number2;
    }else{
        Temp_history = new std::string[count + 2];
        for (int i = 0; i <= count; i++ ){
            Temp_history[i] = user_history[i]; 
        }
        delete[] user_history;
        user_history = nullptr;
        Temp_history[count + 1] = operation + casted_number2;
    }
    user_history = new std::string[count + 2];
    for (int i = 0; i <= count + 1; i++){
        user_history[i] = Temp_history[i];
    }
    delete[] Temp_history;
    Temp_history = nullptr;
    count++;
}
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

void History::delete_history(){
    delete[] user_history;
    user_history = nullptr;
    count = 0;
}

int History::get_count(){
    count;
    return count;
}

void Controller::get_user_expression(){
    if(get_count() == 0){
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