#include "headers/utilities.hpp"

namespace Utilities {
    static std::string convertToLower(std::string inputString){
        for (size_t i = 0; i < inputString.length(); i++){
            char c = inputString[i];
            if (c >= 65 && c <= 90){
                c = c + 32;
            }
            inputString[i] = c;
        }
        return inputString;
    }

    static std::string takeYNInput(){
        bool ynInputed = false;
        std::string userInput;

        do {
            std::cin >> userInput;
            //userInput = convertToLower(userInput);
            if (userInput != "y" && userInput != "n"){
                std::cout << "Please enter either y or n\n";
            }
            else { ynInputed = true; }

        } while (ynInputed == false);

        return userInput;
    }

    static int takeIntInput() {
        bool intInputed = true;
        std::string userInput;
        
        do {
            std::cin >> userInput;
            intInputed = true;
            for (char c : userInput) {
                if (c < 48 || c > 58) {
                    intInputed = false;
                    std::cout << "Please enter a valid integer number (eg. 145)\n";
                }
            }
        } while (intInputed == false);

        return std::stoi(userInput);
    }

    static double takeDoubleInput() {
        bool doubleInputted = true;
        bool pointFound = false;
        std::string userInput;

        do {
            std::cin >> userInput;
            doubleInputted = true;

            for (char c : userInput) {
                if (c == '.'){
                    if (!pointFound) { pointFound = true; }
                    else { doubleInputted = false; }
                }
                if (c < 48 || c > 58) {
                    doubleInputted = false;
                    std::cout << "Please enter a valid decimal number (eg. 0.89 or 0.1)\n";
                }
            }
        } while (doubleInputted == false);

        return std::stod(userInput);
    }
}