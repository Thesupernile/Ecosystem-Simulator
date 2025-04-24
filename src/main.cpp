#include "headers/main.hpp"

namespace Ecosystem {
    static void instructions() {
        std::string userResponse;
        std::cout << "\n";
        std::cout << "Ecosystem Simulator:\n\n";
        std::cout << "The ecosystem simulator will start with a given number of plants, herbivores and carnivores\n";
        std::cout << "Each \"Day\" an animal must find the appropriate amount of food or it will lose health\n";
        std::cout << "If an animal remains unfed for a prolonged period, it will die\n";
        std::cout << "If an animal can stay fed for a prolonged period, it will be able to reproduce\n";
        std::cout << "The simulator will tell you each day how many of each animal type and how many plants there are\n";
        std::cout << "Press any key then enter to continue...\n";
        std::cin >> userResponse;
        std::cout << "\n";
    }

    static void reportEcoInformation(std::vector<Animals::Animal> animalsList){
        int numCarnivores = 0;
        int numHerbivores = 0;
        int numPlants = 0;
        int numStarvingAnimals = 0;

        for (int i = 0; i < animalsList.size(); i++){
            
        }

        std::cout << "Ecosystem Information:\n\n";
        std::cout << "There are " << numPlants << "plants in the ecosystem.\n";
        std::cout << "There are " << animalsList.size() << "animals in the ecosystem.\n";
        std::cout << "Of these, " << numHerbivores << " are herviores and " << numCarnivores << "are carnivores.\n";
        std::cout << numStarvingAnimals << " animals didn't find food today.\n";
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
        int x_coord = rand() % mapWidth;
        int y_coord = rand() % mapHeight;

        //animalList.emplace_back(Animals::Herbivore(x_coord, y_coord));
    }
    
    /*for (int i = 0; i < numCarnivores; i++){
        int x_coord = rand() % mapWidth;
        int y_coord = rand() % mapHeight;

        Animals::Herbivore animalToAdd = Animals::Herbivore(x_coord, y_coord);

        animalList.push_back(animalToAdd);
    }*/

    // Run simulation
    while (runEcosystem){
        for (int i = 0; i < animalList.size(); i++){
            animalList[i].dayProcess();
        }

        Ecosystem::reportEcoInformation(animalList);

        while (userInput != "y" && userInput != "n"){
            std::cout << "Would you like to simulate another day? Y/N\n";
            userInput = Utilities::takeYNInput();
            if (userInput == "n"){
                std::cout << "Exiting...\n";
                runEcosystem = false;
            }
        }
    }

    return 0;
}