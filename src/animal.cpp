#include "animal.hpp"

namespace Animals {
	class Animal {
		protected:
			const int ALLOWEDHUNGRYDAYS = 2;
			const int WELLFEDDAYSTOREPRODUCE = 1;

			int _foodRequired = 1;
			int _sightRange = 5;
			int _hunger = 0;
			bool _wellFedDays = true;
			bool _canEatPlant = false;
			bool _canEatAnimal = false;
			bool _ateLastDay = false;
			int _xCoord = 0;
			int _yCoord = 0;
			int _health = 0;
			int _speed = 0;

			void searchForFood(int* coordinates) {

				//coordinates = {0, 0};
			}

		public:
			Animal(int xCoord, int yCoord) {
				_xCoord = xCoord;
				_yCoord = yCoord;
				_hunger = 0;
				_health = ALLOWEDHUNGRYDAYS;
			}
			
			void dayProcess(){
				int foodCoordinates[] = { -1, -1 };
				searchForFood(foodCoordinates);

				// Checks if the searchForFood found a food (negative coordinate is only returned if food is not found)
				while (foodCoordinates[0] == -1){
					
				}
				// Use all remaining movement points to try to reach the food

			}

			// Methods for getting private members
			bool isHerbivore() { return _canEatPlant; }
			bool isCarnivore() { return _canEatAnimal; }
			bool AteToday() { return _ateLastDay; }
			bool isStarving() { return _health == 1; }


			int getPositionX() { return _xCoord; }
			int getPositionY() { return _yCoord; }

			// Methods for setting private members
			void setPositionX(int newPosX) { _xCoord = newPosX; }
			void setPositionY(int newPosY) { _yCoord = newPosY; }
	};
}