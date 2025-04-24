#include "animal.hpp"

namespace Animals {
	class Animal {
		protected:
			const int ALLOWEDHUNGRYDAYS = 2;
			const int WELLFEDDAYSTOREPRODUCE = 1;

			int _foodRequired = 1;
			int _sightRange = 1;
			int _hunger = 0;
			bool _wellFedDays = true;
			bool _canEatPlant = false;
			bool _canEatAnimal = false;
			int _xCoord = 0;
			int _yCoord = 0;
			int _health = 0;
			int _speed = 0;

			int searchForFood() {
				int coordinates[] = { 0, 0 };

				return *coordinates;
			}

		public:
			Animal(int xCoord, int yCoord) {
				_xCoord = xCoord;
				_yCoord = yCoord;
				_hunger = 0;
				_health = ALLOWEDHUNGRYDAYS;
			}
			virtual void dayProcess() = 0;

			// Methods for getting private members
			int getPositionX() { return _xCoord; }
			int getPositionY() { return _yCoord; }
			// Methods for setting private members
			void setPositionX(int newPosX) { _xCoord = newPosX; }
			void setPositionY(int newPosY) { _yCoord = newPosY; }
	};
}