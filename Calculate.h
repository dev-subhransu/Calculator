// Header guard to prevent multiple inclusions of this file during compilation
#ifndef CALCULATE_H
#define CALCULATE_H

// ============================================================================
// Base Class: Calculate
// Handles core arithmetic operations and maintains the active calculation state.
// ============================================================================
class Calculate{

    private:
        double result = 0;          // Stores the ongoing/latest calculation result
    
    protected:
        double number_1 = 0;        // First operand (auto-filled from result in chained mode)
        double number_2 = 0;        // Second operand entered by the user
        std::string operation;      // Raw operator input entered by the user

    public:
        double Addition();          // Performs number_1 + number_2
        double Substraction();      // Performs number_1 - number_2
        double Multiplication();    // Performs number_1 * number_2
        double Division();          // Performs number_1 / number_2 (with zero-division guard)
        int Modulus();              // Performs integer modulus (with zero-modulus guard)
        double reset_result();      // Resets active result back to 0
        double get_result();        // Returns the current stored result
};


// ============================================================================
// Derived Class: History (inherits from Calculate)
// Manages dynamic pointer-based storage, formatting, and display of past entries.
// ============================================================================
class History: public Calculate{

    private:
        int count = 0;                          // Tracks total number of valid stored calculations

    private:
        std::string casted_number1;             // String-formatted representation of number_1
        std::string casted_number2;             // String-formatted representation of number_2
        std::string* Temp_history = nullptr;    // Temporary buffer pointer used during array resizing
        std::string* user_history = nullptr;    // Dynamic array pointer holding formatted history records

    public:
        void cast_numbers();        // Converts numeric operands into clean strings for logging
        void store_history();       // Dynamically allocates/resizes array and appends valid expression
        void show_history();        // Prints all recorded calculation entries to the console
        void delete_history();      // Frees allocated heap memory and resets history counter
        int get_count();            // Returns the current number of stored history entries
};


// ============================================================================
// Derived Class: Controller (inherits from History)
// Orchestrates the CLI menu loop, input validation, and execution pipeline.
// ============================================================================
class Controller:public History{
    public:
        // Strongly-typed enum representing supported arithmetic operators
        enum class Operations {ADD, SUB, MULTI, DIV, MOD, INVALID};
        void manager();             // Main application loop controlling menu options and execution flow
    private:
        int choice;                 // Stores user's menu selection
        void get_user_expression(); // Prompts and captures operands and operator from user
        Operations get_enum_op();   // Maps raw string operator to its corresponding Operations enum
        void do_calculations();     // Executes the matched arithmetic operation or handles invalid traps
        bool should_save_history(); // Validates whether the current operation is safe to record in history
};

#endif // CALCULATE_H