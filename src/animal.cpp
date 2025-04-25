#include "animal.hpp"

namespace Animals {
	class Animal {
		protected:
			const int ALLOWEDHUNGRYDAYS = 2;
			const int WELLFEDDAYSTOREPRODUCE = 2;

			int _foodRequired = 1;
			int _sightRange = 5;
			int _wellFedDays = 1;
			bool _canEatPlant = false;
			bool _canEatAnimal = false;
			bool _ateLastDay = false;
			int _xCoord = 0;
			int _yCoord = 0;
			int _health = 0;
			int _speed = 5;

			void searchForPlantFood(std::vector<std::vector<int>> &plantMap, int (&foodCoordinates)[3], int depth, int x, int y) {

				if (plantMap[y][x] == 0 && (_sightRange - depth) < foodCoordinates[3]){
					// Check if there is food in the square
					foodCoordinates[0] = x;
					foodCoordinates[1] = y;
				}
				else{
					// Increase distance
					foodCoordinates[3] += 1;
					// Check the squares around the square
					searchForPlantFood(plantMap, foodCoordinates, depth-1, x - 1, y - 1);
					searchForPlantFood(plantMap, foodCoordinates, depth-1, x + 1, y - 1);
					searchForPlantFood(plantMap, foodCoordinates, depth-1, x - 1, y + 1);
					searchForPlantFood(plantMap, foodCoordinates, depth-1, x + 1, y + 1);
				}
			}

			void searchForAnimalFood(std::vector<Animal> &animalList, int (&foodCoordinates)[3], int depth, int x, int y){
				// Future feature: Carnivores can eat other carnivores if they are below half hunger
				for (auto animal : animalList){
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
			Animal(int xCoord, int yCoord) {
				_xCoord = xCoord;
				_yCoord = yCoord;
				_health = ALLOWEDHUNGRYDAYS;
			}
			
			void dayProcess(std::vector<Animal> &animalList, std::vector<std::vector<int>> &plantMap){
				// The first two indexes in coordinates are the positon (x, y) and the third is the distance between this animal and the food
				int foodCoordinates[] = { -1, -1, _sightRange + 1 };
				int movementPoints = _speed;
				if (_canEatPlant){
					searchForPlantFood(plantMap, foodCoordinates, _sightRange, _xCoord, _yCoord);
				}
				else{
					searchForAnimalFood(animalList, foodCoordinates, _sightRange, _xCoord, _yCoord);
				}

				// Checks if the searchForFood found a food (negative coordinate is only returned if food is not found)
				while (foodCoordinates[0] == -1 && movementPoints > 0){
					// Randomly moves then checks for food again
					switch (rand() % 4){
						case 0:
							_xCoord -= 1;
						case 1:
							_xCoord += 1;
						case 2:
							_yCoord -= 1;
						case 3:
							_yCoord += 1;
					}
					movementPoints--;

					if (_canEatAnimal){
						searchForPlantFood(plantMap, foodCoordinates,  _sightRange, _xCoord, _yCoord);
					}
					else{
						searchForAnimalFood(animalList, foodCoordinates, _sightRange, _xCoord, _yCoord);
					}
				}
				// Use all remaining movement points to try to reach the food
				while (foodCoordinates[0] != _xCoord && foodCoordinates[1] != _yCoord && movementPoints > 0){
					// Moves first horizontally to the food, then up to it
					if (foodCoordinates[0] > _xCoord){
						_xCoord -= 1;
					}
					else if (foodCoordinates[0] < _xCoord){
						_xCoord += 1;
					}
					else if (foodCoordinates[1] > _yCoord){
						_yCoord -= 1;
					}
					else if (foodCoordinates[1] > _yCoord){
						_yCoord += 1;
					}
					movementPoints--;
				}

				if (foodCoordinates[0] == _xCoord && foodCoordinates[1] == _yCoord){
					if (_canEatPlant && plantMap[_yCoord][_xCoord] != 0){
						plantMap[_yCoord][_xCoord] -= 1;
						_ateLastDay = true;
					}
					else if (_canEatAnimal){
						for (int i = 0; i < animalList.size(); i++){
							if (animalList[i].getPositionX() == _xCoord && animalList[i].getPositionY() == _yCoord && animalList[i].isHerbivore()){
								_ateLastDay = true;
								//animalList.erase(std::next(animalList.begin(), i));
							}
						}
					}
				}
				if (!(_ateLastDay)){
					_health--;
				}
			}

			// Methods for getting private members
			bool isHerbivore() { return _canEatPlant; }
			bool isCarnivore() { return _canEatAnimal; }
			bool AteToday() { return _ateLastDay; }
			int getHealth() { return _health; }


			int getPositionX() { return _xCoord; }
			int getPositionY() { return _yCoord; }

			// Methods for setting private members
			void setPositionX(int newPosX) { _xCoord = newPosX; }
			void setPositionY(int newPosY) { _yCoord = newPosY; }
	};
}