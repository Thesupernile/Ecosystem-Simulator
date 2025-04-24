#include "headers/main.hpp"

namespace Ecosystem {
    static void instructions() {
        std::string userResponse;
        std::cout << "\n\n\n";
        std::cout << "Ecosystem Simulator:\n\n";
        std::cout << "The ecosystem simulator will start with a given number of plants, herbivores and carnivores\n";
        std::cout << "Each \"Day\" an animal must find the appropriate amount of food or it will lose health\n";
        std::cout << "If an animal remains unfed for a prolonged period, it will die\n";
        std::cout << "If an animal can stay fed for a prolonged period, it will be able to reproduce\n";
        std::cout << "The simulator will tell you each day how many of each animal type and how many plants there are\n";
        std::cout << "Press any key then enter to continue...\n";
        std::cin >> userResponse;
        std::cout << "\n\n\n";
    }
}

int main() {
    // Ecosystem Paramaters
    int mapWidth = 100;
    int mapHeight = 100;
    int numPlants = 200;
    double plantGrothRate = 0.8;
    int numHerbivores = 100;
    int numCarnivores = 10;
    bool runEcosystem = true;
    std::string userInput;

    // Ecosystem Setup By User
    Ecosystem::instructions();


    // Simulation
    std::vector<Animals::Animal> animalList;

    // Create each animal and populate the map (Each animal is placed randomly on the board)
    for (int i = 0; i < numHerbivores; i++){
        int x_coord = rand() % 100;
        int y_coord = rand() % 100;

        Animals::Herbivore animalToAdd = Animals::Herbivore(x_coord, y_coord);

        animalList.push_back(animalToAdd);
    }

    for (int i = 0; i < numHerbivores; i++){
        int x_coord = rand() % 100;
        int y_coord = rand() % 100;

        Animals::Herbivore animalToAdd = Animals::Herbivore(x_coord, y_coord);

        animalList.push_back(animalToAdd);
    }

    // Run simulation
    while (runEcosystem){
        for (int i = 0; i < animalList.size(); i++){
            animalList[i].dayProcess();
        }

        while (userInput != "Y" && userInput != "N"){
            std::cout << "Would you like to simulate another day? Y/N\n";
            if (Utilities::takeYNInput() == 'n'){
                std::cout << "Exiting...\n";
                runEcosystem = false;
            }
        }

    }

    return 0;
}