#ifndef CALCULATE_H
#define CALCULATE_H

class Calculate{

    private:
        double result = 0;
    
    protected:
        double number_1 = 0;
        double number_2 = 0;
        std::string operation;

    public:
        double Addition();
        double Substraction();
        double Multiplication();
        double Division();
        int Modulus();
        double reset_result();
        double get_result();
};



class History: public Calculate{

    private:
        int count = 0;

    private:
        std::string casted_number1;
        std::string casted_number2;
        std::string* Temp_history = nullptr;
        std::string* user_history = nullptr;

    public:
        void cast_numbers();
        void store_history();
        void show_history();
        void delete_history();
        int get_count();
};

class Controller:public History{
    public:
        enum class Operations {ADD, SUB, MULTI, DIV, MOD, INVALID};
        void manager();
    private:
        int choice;    
        void get_user_expression();
        Operations get_enum_op();
        void do_calculations();
        bool should_save_history();
};

#endif