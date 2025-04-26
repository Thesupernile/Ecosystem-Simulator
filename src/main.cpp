#include "headers/main.hpp"

namespace Ecosystem {

    static void populateAnimals(std::vector<Animals::Animal> &animalList, int numHerbivores, int numCarnivores, int mapHeight, int mapWidth){
        for (int i = 0; i < numHerbivores; i++){
            int x_coord = rand() % mapWidth;
            int y_coord = rand() % mapHeight;
    
            animalList.emplace_back(Animals::Animal(x_coord, y_coord, true, false));
        }
    }

    static void populatePlants(std::vector<std::vector<int>> &plantMap, int numPlants, const int mapHeight, const int mapWidth) {
        for (int i = 0; i < numPlants; i++){
            int plantX = rand() % mapWidth;
            int plantY = rand() % mapHeight;

            plantMap[plantY][plantX] += 1;
        }
    }

    static void plantDayProcess(std::vector<std::vector<int>> &plantMap, int maxPlantsPerTile){
        for (int row = 0; row < static_cast<int>(plantMap.size()); row++){
            for (int col = 0; col < static_cast<int>(plantMap[row].size()); col++){
                // 80% chance of a plant duplicating
                int numPlants = plantMap[row][col];
                
                for (int i = 0; i < numPlants; i++){
                    if (rand() % 10 > 8){
                        bool newPlantMade = false;

                        while (!newPlantMade){
                            switch (rand() % 4){
                                case 0:
                                    if (col-1 >= 0){
                                        if (plantMap[row][col-1] < maxPlantsPerTile){
                                            plantMap[row][col-1] += 1;
                                        }
                                        newPlantMade = true;
                                    }
                                    break;
                                case 1:
                                    if (col+1 < static_cast<int>(plantMap[0].size())){
                                        if (plantMap[row][col+1] < maxPlantsPerTile){
                                            plantMap[row][col+1] += 1;
                                        }
                                        newPlantMade = true;
                                    }
                                    break;
                                case 2:
                                    if (row - 1 >= 0){
                                        if (plantMap[row-1][col] < maxPlantsPerTile){
                                            plantMap[row-1][col] += 1;
                                        }
                                        newPlantMade = true;
                                    }
                                    break;
                                default:
                                    if (row + 1 < static_cast<int>(plantMap.size())){
                                        if (plantMap[row+1][col] < maxPlantsPerTile){
                                            plantMap[row+1][col] += 1;
                                        }
                                        newPlantMade = true;
                                    }
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }

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

    static void reportEcoInformation(std::vector<Animals::Animal> &animalsList, std::vector<std::vector<int>> &plantMap){
        int numCarnivores = 0;
        int numHerbivores = 0;
        int numAliveAnimals = 0;
        int numPlants = 0;
        int numStarvingAnimals = 0;

        // Adds up all the plants
        for (size_t row = 0; row < plantMap.size(); row++){
            for (size_t col = 0; col < plantMap[row].size(); col++){
                numPlants += plantMap[row][col];
            }
        }

        // Adds up all the animals
        for (size_t i = 0; i < animalsList.size(); i++){
            if (animalsList[i].isAlive()){
                numAliveAnimals++;
            }
            if (animalsList[i].isHerbivore() && animalsList[i].isAlive()){
                numHerbivores++;
            }
            else if (animalsList[i].isCarnivore() && animalsList[i].isAlive()){
                numCarnivores++;
            }
            if (animalsList[i].getHealth() <= 1 && animalsList[i].isAlive()){
                numStarvingAnimals++;
            }
        }

        std::cout << "Ecosystem Information:\n\n";
        std::cout << "There are " << numPlants << " plants in the ecosystem.\n";
        std::cout << "There are " << numAliveAnimals << " animals in the ecosystem.\n";
        std::cout << "Of these, " << numHerbivores << " are herviores and " << numCarnivores << " are carnivores.\n";
        std::cout << numStarvingAnimals << " animals didn't find food today.\n";
    }

}

int main() {
    // Ecosystem Paramaters
    int mapWidth = 100;
    int mapHeight = 100;
    int numPlants = 4000;
    double plantGrothRate = 0.8;
    int numHerbivores = 100;
    int numCarnivores = 10;
    int wellFedDaysToReproduce = 2;
    int maxPlantsPerTile = 5;

    bool runEcosystem = true;
    std::string userInput = "";

    // Ecosystem Setup By User
    Ecosystem::instructions();

    // Simulation
    std::vector<Animals::Animal> animalList;
    std::vector<std::vector<int>> plantMap(mapHeight, std::vector<int>(mapWidth, 0));

    // Create each animal and populate the map (Each animal is placed randomly on the board)
    Ecosystem::populateAnimals(animalList, numHerbivores, numCarnivores, mapHeight, mapWidth);

    Ecosystem::populatePlants(plantMap, numPlants, mapHeight, mapWidth);

    // Run simulation
    while (runEcosystem){
        for (size_t i = 0; i < animalList.size(); i++){
            if (animalList[i].isAlive()){
                animalList[i].dayProcess(animalList, plantMap);
                // If an animal is dead, we can remove it from existance
                if (animalList[i].getHealth() == 0){
                    animalList[i].setIsAlive(false);
                }
                if (animalList[i].getFedDays() >= wellFedDaysToReproduce){
                    animalList.emplace_back(Animals::Animal(animalList[i].getPositionX(), animalList[i].getPositionY(), animalList[i].isHerbivore(), animalList[i].isCarnivore()));
                    animalList[i].setWellFedDays(0);
                }
            }
        }

        Ecosystem::plantDayProcess(plantMap, maxPlantsPerTile);
        Ecosystem::reportEcoInformation(animalList, plantMap);

        userInput = "";
        while (userInput != "y" && userInput != "n"){
            std::cout << "Would you like to simulate another day? Y/N\n";
            userInput = Utilities::takeYNInput();
            std::cout << userInput;
            if (userInput == "n"){
                std::cout << "Exiting...\n";
                runEcosystem = false;
            }
        }
    }

    return 0;
}