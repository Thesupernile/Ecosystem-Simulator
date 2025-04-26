#include "animal.hpp"

namespace Animals {
	class Animal {
		protected:
			const int ALLOWEDHUNGRYDAYS = 2;
			int _foodRequired = 1;
			int _sightRange = 5;
			int _wellFedDays = 0;
			bool _canEatPlant = false;
			bool _canEatAnimal = false;
			bool _ateLastDay = false;
			bool _isAlive = true;
			int _xCoord = 0;
			int _yCoord = 0;
			int _health = 0;
			int _speed = 5;

			void searchForPlantFood(std::vector<std::vector<int>> &plantMap, int (&foodCoordinates)[3], int depth, int x, int y) {

				if (plantMap[y][x] != 0 && (_sightRange - depth) < foodCoordinates[2]){
					// Check if there is food in the square
					foodCoordinates[0] = x;
					foodCoordinates[1] = y;
					foodCoordinates[2] = _sightRange - depth; /*This line also has the error*/
				}
				else if (depth > 0){
					// Increase distance
					// Check the squares around the square
					// Here there needs to be an extra part to prevent us looking at squares we've already checked
					if (x-1 >= 0 && y-1 >= 0){
						searchForPlantFood(plantMap, foodCoordinates, depth-1, x - 1, y - 1);
					}
					if (x+1 < static_cast<int>(plantMap[0].size()) && y-1 >= 0){
						searchForPlantFood(plantMap, foodCoordinates, depth-1, x + 1, y - 1);
					}
					if (x-1 >= 0 && y+1 < static_cast<int>(plantMap.size())){
						searchForPlantFood(plantMap, foodCoordinates, depth-1, x - 1, y + 1);
					}
					if(x+1 < static_cast<int>(plantMap[0].size()) && y+1 < static_cast<int>(plantMap.size())){
						searchForPlantFood(plantMap, foodCoordinates, depth-1, x + 1, y + 1);
					}
				}
			}

			void searchForAnimalFood(std::vector<Animal> &animalList, int (&foodCoordinates)[3], int depth, int x, int y){
				// Future feature: Carnivores can eat other carnivores if they are below half hunger
				for (auto &animal : animalList){
					if (animal.isHerbivore()){
						int xDistance;
						int yDistance;

						if (animal.getPositionX() < _xCoord){ xDistance = _xCoord - animal.getPositionX(); }
						else { xDistance = animal.getPositionX() - _xCoord; }

						if (animal.getPositionX() < _yCoord){ yDistance = _yCoord - animal.getPositionY(); }
						else { yDistance = animal.getPositionY() - _yCoord; }

						if ((xDistance + yDistance < foodCoordinates[2]) && (xDistance + yDistance <= _sightRange)){
							foodCoordinates[0] = animal.getPositionX();
							foodCoordinates[1] = animal.getPositionY();
							foodCoordinates[2] = xDistance + yDistance;
						}
					}
				}
			}

		public:
			Animal(int xCoord, int yCoord, bool canEatPlants, bool canEatAnimal) {
				_xCoord = xCoord;
				_yCoord = yCoord;
				_health = ALLOWEDHUNGRYDAYS;
				_canEatPlant = canEatPlants;
				_canEatAnimal = canEatAnimal;
			}

			/* Taken out since non functional
			~Animal() {
				delete &ALLOWEDHUNGRYDAYS;
				delete &_foodRequired;
				delete &_sightRange;
				delete &_wellFedDays;
				delete &_canEatPlant;
				delete &_canEatAnimal;
				delete &_ateLastDay;
				delete &_xCoord;
				delete &_yCoord;
				delete &_health;
				delete &_speed;
			}*/
			
			void dayProcess(std::vector<Animal> &animalList, std::vector<std::vector<int>> &plantMap){
				// The first two indexes in coordinates are the positon (x, y) and the third is the distance between this animal and the food
				int foodCoordinates[] = { -1, -1, _sightRange + 1 };
				int movementPoints = _speed;
				bool _ateLastDay = false;
				if (_canEatPlant){
					searchForPlantFood(plantMap, foodCoordinates, _sightRange, _xCoord, _yCoord);
				}
				else{
					searchForAnimalFood(animalList, foodCoordinates, _sightRange, _xCoord, _yCoord);
				}

				// Checks if the searchForFood found a food (negative coordinate is only returned if food is not found)
				while (foodCoordinates[0] == -1 && movementPoints > 0){
					// Randomly moves then checks for food again
					bool hasMoved = false;
					while (!hasMoved){
						switch (rand() % 4){
							case 0:
								if (_xCoord-1 >= 0){
									_xCoord -= 1;
									hasMoved = true;
								}
								break;
							case 1:
								if (_xCoord+1 < static_cast<int>(plantMap[0].size())){
									_xCoord += 1;
									hasMoved = true;
								}
								break;
							case 2:
								if (_yCoord - 1 >= 0){
									_yCoord -= 1;
									hasMoved = true;
								}
								break;
							default:
								if (_yCoord + 1 < static_cast<int>(plantMap.size())){
									_yCoord += 1;
									hasMoved = true;
								}
								break;
						}
					}
					movementPoints--;
					//std::cout << "Position updated:\nX: " << _xCoord << "\nY: " << _yCoord;

					if (_canEatPlant){
						searchForPlantFood(plantMap, foodCoordinates,  _sightRange, _xCoord, _yCoord);
					}
					else{
						searchForAnimalFood(animalList, foodCoordinates, _sightRange, _xCoord, _yCoord);
					}
				}
				// Use all remaining movement points to try to reach the food
				while ((foodCoordinates[0] != _xCoord || foodCoordinates[1] != _yCoord) && movementPoints > 0){
					// Moves first horizontally to the food, then up to it
					if (foodCoordinates[0] > _xCoord){
						_xCoord += 1;
					}
					else if (foodCoordinates[0] < _xCoord){
						_xCoord -= 1;
					}
					else if (foodCoordinates[1] > _yCoord){
						_yCoord += 1;
					}
					else if (foodCoordinates[1] < _yCoord){
						_yCoord -= 1;
					}
					movementPoints--;
				}

				if (foodCoordinates[0] == _xCoord && foodCoordinates[1] == _yCoord){
					if (_canEatPlant && plantMap[_yCoord][_xCoord] != 0){
						plantMap[_yCoord][_xCoord] -= 1;
						_ateLastDay = true;
						_wellFedDays += 1;
						_health = ALLOWEDHUNGRYDAYS;
					}
					else if (_canEatAnimal){
						for (size_t i = 0; i < animalList.size(); i++){
							if (animalList[i].getPositionX() == _xCoord && animalList[i].getPositionY() == _yCoord && animalList[i].isHerbivore()){
								_ateLastDay = true;
								_wellFedDays += 1;
								_health = ALLOWEDHUNGRYDAYS;
								animalList[i].setIsAlive(false);
							}
						}
					}
				}
				if (!(_ateLastDay)){
					_health--;
					_wellFedDays = 0;
				}

				// Delete the food coordinates array
				//delete[] &foodCoordinates;
			}

			// Methods for getting private members
			bool isHerbivore() { return _canEatPlant; }
			bool isCarnivore() { return _canEatAnimal; }
			bool isAlive() { return _isAlive; }
			bool AteToday() { return _ateLastDay; }
			int getHealth() { return _health; }
			int getFedDays() { return _wellFedDays; }


			int getPositionX() { return _xCoord; }
			int getPositionY() { return _yCoord; }

			// Methods for setting private members
			void setPositionX(int newPosX) { _xCoord = newPosX; }
			void setPositionY(int newPosY) { _yCoord = newPosY; }
			void setWellFedDays(int newDays) { _wellFedDays = newDays; }
			void setIsAlive(bool newIsAlive) { _isAlive = newIsAlive; }
	};
}