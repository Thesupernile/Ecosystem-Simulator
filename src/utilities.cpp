#include "headers/utilities.hpp"

namespace Utilities {
    static std::string convertToLower(std::string inputString){
        for (int i = 0; i < inputString.length(); i++){
            char c = inputString[i];
            if (c >= 65 && c <= 90){
                c = c + 32;
            }
            inputString[i] = c;
        }
        return inputString;
    }

    static char takeYNInput(){
        bool ynInputed = true;
        std::string userInput;

        do {
            std::cin >> userInput;
            userInput = convertToLower(userInput);
            if (userInput != "y" || userInput != "n"){
                std::cout << "Please enter either y or n\n";
            }
            else { ynInputed = true; }

        } while (ynInputed == false);

        return userInput[0];
    }

    static int takeIntInput() {
        bool intInputed = true;
        std::string userInput;

        do {
            std::cin >> userInput;
            for (char c : userInput) {
                if (c < 48 || c > 58) {
                    intInputed = false;
                    std::cout << "Please enter a valid integer number (eg. 145)\n";
                }
            }
        } while (intInputed == false);

        return std::stoi(userInput);
    }
}