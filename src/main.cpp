#include "headers/main.hpp"

namespace Ecosystem {

    static void populateAnimals(std::vector<Animals::Animal> &animalList, int numHerbivores, int numCarnivores, int mapHeight, int mapWidth, int sightRange){
        for (int i = 0; i < numHerbivores; i++){
            int x_coord = rand() % mapWidth;
            int y_coord = rand() % mapHeight;
    
            animalList.emplace_back(Animals::Animal(x_coord, y_coord, true, false, sightRange));
        }
        for (int i = 0; i < numCarnivores; i++){
            int x_coord = rand() % mapWidth;
            int y_coord = rand() % mapHeight;
            
            animalList.emplace_back(Animals::Animal(x_coord, y_coord, false, true, sightRange));
        }
    }

    static void populatePlants(std::vector<std::vector<int>> &plantMap, int numPlants, const int mapHeight, const int mapWidth) {
        for (int i = 0; i < numPlants; i++){
            int plantX = rand() % mapWidth;
            int plantY = rand() % mapHeight;

            plantMap[plantY][plantX] += 1;
        }
    }

    static void plantDayProcess(std::vector<std::vector<int>> &plantMap, int maxPlantsPerTile, double plantGrowthChance){

        for (int row = 0; row < static_cast<int>(plantMap.size()); row++){
            for (int col = 0; col < static_cast<int>(plantMap[row].size()); col++){
                int numPlants = plantMap[row][col];
        
                for (int i = 0; i < numPlants; i++){
                    // Random chance of duplication
                    if ((double)((rand() % 1000) / 1000.0) < plantGrowthChance){
                        bool newPlantMade = false;
                        // Checks to see if there is ANY valid position to place a new plant (same conditions as in the switch statements)
                        if (!(col-1 >= 0 && plantMap[row][col-1] < maxPlantsPerTile) && !(col+1 < static_cast<int>(plantMap[0].size()) && (plantMap[row][col+1] < maxPlantsPerTile)) && !(row - 1 >= 0 && (plantMap[row-1][col] < maxPlantsPerTile)) && !(row + 1 < static_cast<int>(plantMap.size()) && (plantMap[row+1][col] < maxPlantsPerTile)) && !(plantMap[row][col] < maxPlantsPerTile)){
                            newPlantMade = true;
                        }
                        // If a plant can be made, makes the plant
                        while (!newPlantMade){
                            switch (rand() % 5){
                                case 0:
                                    if (col-1 >= 0 && plantMap[row][col-1] < maxPlantsPerTile){
                                        plantMap[row][col-1] += 1;
                                        newPlantMade = true;
                                    }
                                    break;
                                case 1:
                                    if (col+1 < static_cast<int>(plantMap[0].size()) && (plantMap[row][col+1] < maxPlantsPerTile)){
                                        plantMap[row][col+1] += 1;
                                        newPlantMade = true;
                                    }
                                    break;
                                case 2:
                                    if (row - 1 >= 0 && (plantMap[row-1][col] < maxPlantsPerTile)){
                                        plantMap[row-1][col] += 1;
                                        newPlantMade = true;
                                    }
                                    break;
                                case 3:
                                    if (row + 1 < static_cast<int>(plantMap.size()) && (plantMap[row+1][col] < maxPlantsPerTile)){
                                        plantMap[row+1][col] += 1;
                                        newPlantMade = true;
                                    }
                                    break;
                                default:
                                    if (plantMap[row][col] < maxPlantsPerTile){
                                        plantMap[row][col] += 1;
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
        std::cout << "The simulator will tell you each day how many of each animal type and how many plants there are as well as how many animals failed to find food the last day\n";
        std::cout << "Press any key then enter to continue...\n";
        std::cin >> userResponse;
        std::cout << "\n";
    }

    static void reportEcoInformation(std::vector<Animals::Animal> &animalsList, std::vector<std::vector<int>> &plantMap){
        int numCarnivores = 0;
        int numHerbivores = 0;
        int numAliveAnimals = 0;
        int numPlants = 0;
        int numAnimalsNotEaten = 0;

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
            if (!(animalsList[i].ateToday()) && animalsList[i].isAlive()){
                numAnimalsNotEaten++;
            }
        }

        std::cout << "Ecosystem Information:\n\n";
        std::cout << "There are " << numPlants << " plants in the ecosystem.\n";
        std::cout << "There are " << numAliveAnimals << " animals in the ecosystem.\n";
        std::cout << "Of these, " << numHerbivores << " are herviores and " << numCarnivores << " are carnivores.\n";
        std::cout << numAnimalsNotEaten << " animals didn't find food today.\n";
    }
}

int main() {
    // Ecosystem Paramaters
    int mapWidth = 100;
    int mapHeight = 100;
    int numPlants = 1000;
    double plantGrowthRate = 0.8;
    int numHerbivores = 200;
    int numCarnivores = 10;
    int wellFedDaysToReproduce = 2;
    int hungryDaysBeforeDeath = 2;
    int maxPlantsPerTile = 5;
    double preditorKillChance = 0.8;
    int sightRange = 5;

    bool runEcosystem = true;
    bool runProgram = true;
    std::string userInput = "";
    Ecosystem::instructions();

    while (runProgram) {
        // Ecosystem Setup By User
        std::cout << "Would you like to alter the ecosystem parameters? (y/n)\n";
        userInput = Utilities::takeYNInput();
        std::cout << "\n";
        if (userInput == "y"){
            bool setupComplete = false;

            do{
                std::cout << "\nEcosystem Setup Window: \n";
                std::cout << "\nMap:\n";
                std::cout << "1) Map Width: " << mapWidth << "\n";
                std::cout << "2) Map Height: " << mapHeight << "\n";

                std::cout << "\nPlants:\n";
                std::cout << "3) Initial Plants: " << numPlants << "\n";
                std::cout << "4) Plant Growth Rate: " << plantGrowthRate << "\n";
                std::cout << "5) Maximum number of plants per tile: " << maxPlantsPerTile << "\n";

                std::cout << "\nAnimals:\n";
                std::cout << "6) Intital Herbivores: " << numHerbivores << "\n";
                std::cout << "7) Initial Carnivores: " << numCarnivores << "\n";
                std::cout << "8) Number of consecutive fed days before an animal reproduces: " << wellFedDaysToReproduce << "\n";
                std::cout << "9) Number of consecutive days without food before an animal dies: " << hungryDaysBeforeDeath << "\n";
                std::cout << "10) Chance of a preditor killing it's prey: " << preditorKillChance << "\n";
                std::cout << "11) Distance animals can see: " << sightRange << "\n";

                std::cout << "\n12) Exit this menu" << "\n";

                std::cout << "\nEnter the number of the option you would like to choose: \n";
                int optionChosen = Utilities::takeIntInput();
                std::cout << "\n";

                // Creating variables for new inputted values (allows program to ask for confirmation before large values are inputted)
                // Only asks for values that substantially affect performance
                int newMapWidth;
                int newMapHeight;
                int newNumPlants;
                int newNumHerbivores;
                int newNumCarnivores;

                switch (optionChosen){
                    case 1:
                        std::cout << "Enter new value for map width: ";
                        newMapWidth = Utilities::takeIntInput();
                        std::cout << "\n";
                        if (newMapWidth >= 200){
                            std::cout << "WARNING! Large map size may take longer to process. Would you like to proceed anyway?\n";
                            userInput = Utilities::takeYNInput();
                            if (userInput == "y"){
                                mapWidth = newMapWidth;
                            }
                        }
                        else { mapWidth = newMapWidth; }
                        break;
                    case 2:
                        std::cout << "Enter new value for map height: ";
                        newMapHeight = Utilities::takeIntInput();
                        std::cout << "\n";
                        if (newMapHeight >= 200){
                            std::cout << "WARNING! Large map size may take longer to process. Would you like to proceed anyway?\n";
                            userInput = Utilities::takeYNInput();
                            if (userInput == "y"){
                                mapHeight = newMapHeight;
                            }
                        }
                        else { mapHeight = newMapHeight; }
                        break;
                    case 3:
                        std::cout << "Enter new value for initial plants: ";
                        newNumPlants = Utilities::takeIntInput();
                        std::cout << "\n";
                        if (newNumPlants >= 20000){
                            std::cout << "WARNING! Large numbers of plants may take a long time to process. Would you like to proceed anyway?\n";
                            userInput = Utilities::takeYNInput();
                            if (userInput == "y"){
                                numPlants = newNumPlants;
                            }
                        }
                        else { numPlants = newNumPlants; }
                        break;
                    case 4:
                        std::cout << "Enter new value for the plant growth rate: ";
                        plantGrowthRate = Utilities::takeDoubleInput();
                        std::cout << "\n";
                        break;
                    case 5:
                        std::cout << "Enter new value for the maximum number of plants per tile: ";
                        maxPlantsPerTile = Utilities::takeIntInput();
                        std::cout << "\n";
                        break;
                    case 6:
                        std::cout << "Enter new value for initial herbivores: ";
                        newNumHerbivores = Utilities::takeIntInput();
                        std::cout << "\n";
                        if (newNumHerbivores >= 20000){
                            std::cout << "WARNING! Large numbers of animals may take a long time to process. Would you like to proceed anyway?\n";
                            userInput = Utilities::takeYNInput();
                            if (userInput == "y"){
                                numHerbivores = newNumHerbivores;
                            }
                        }
                        else { numHerbivores = newNumHerbivores; }
                        break;
                    case 7:
                        std::cout << "Enter new value for initial carnivores: ";
                        newNumCarnivores = Utilities::takeIntInput();
                        std::cout << "\n";
                        if (newNumCarnivores >= 20000){
                            std::cout << "WARNING! Large numbers of animals may take a long time to process. Would you like to proceed anyway?\n";
                            userInput = Utilities::takeYNInput();
                            if (userInput == "y"){
                                numCarnivores = newNumCarnivores;
                            }
                        }
                        else { numCarnivores = newNumCarnivores; }
                        break;
                    case 8:
                        std::cout << "Enter new value for number of fed days required to reproduce: ";
                        wellFedDaysToReproduce = Utilities::takeIntInput();
                        std::cout << "\n";
                        break;
                    case 9:
                        std::cout << "Enter new value for number of days without food before death: ";
                        hungryDaysBeforeDeath = Utilities::takeIntInput();
                        std::cout << "\n";
                        break;
                    case 10:
                        std::cout << "Enter new value for preditor kill chance: ";
                        preditorKillChance = Utilities::takeDoubleInput();
                        std::cout << "\n";
                        break;
                    case 11:
                        std::cout << "Enter new value for animal sight range: ";
                        sightRange = Utilities::takeIntInput();
                        std::cout << "\n";
                        break;
                    case 12:
                        setupComplete = true;
                        std::cout << "\n";
                        break;
                    default:
                        std::cout << "Unknown Input\n\n";
                        break;
                }

            } while (setupComplete == false);

        }

        // Simulation
        std::vector<Animals::Animal> animalList;
        std::vector<std::vector<int>> plantMap(mapHeight, std::vector<int>(mapWidth, 0));

        // Create each animal and populate the map (Each animal is placed randomly on the board)
        Ecosystem::populateAnimals(animalList, numHerbivores, numCarnivores, mapHeight, mapWidth, sightRange);
        Ecosystem::populatePlants(plantMap, numPlants, mapHeight, mapWidth);

        // Run simulation
        int day = 1;
        while (runEcosystem){
            Ecosystem::plantDayProcess(plantMap, maxPlantsPerTile, plantGrowthRate);

            for (size_t i = 0; i < animalList.size(); i++){
                if (animalList[i].isAlive()){
                    animalList[i].dayProcess(animalList, plantMap, preditorKillChance);
                    // If an animal is dead, we can remove it from existance
                    if (animalList[i].getHungryDays() >= hungryDaysBeforeDeath){
                        animalList[i].setIsAlive(false);
                    }
                    if (animalList[i].getFedDays() >= wellFedDaysToReproduce){
                        animalList.emplace_back(Animals::Animal(animalList[i].getPositionX(), animalList[i].getPositionY(), animalList[i].isHerbivore(), animalList[i].isCarnivore(), sightRange));
                        animalList[i].setWellFedDays(0);
                    }
                }
            }

            std::cout << "Day " << day << " simulation completed\n\n";
            Ecosystem::reportEcoInformation(animalList, plantMap);

            userInput = "";
            std::cout << "Would you like to simulate another day? (y/n)\n";
            userInput = Utilities::takeYNInput();
            if (userInput == "n"){
                std::cout << "Exiting...\n";
                runEcosystem = false;
            }

            day++;
        }

        userInput = "";
        std::cout << "Would you like to run another simulation? (y/n) (entering n will exit the program)\n";
        userInput = Utilities::takeYNInput();
        if (userInput == "n"){
            std::cout << "Exiting...\n";
            runProgram = false;
        }
        else { runEcosystem = true; }
    }

    return 0;
}