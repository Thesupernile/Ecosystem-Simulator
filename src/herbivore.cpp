#include "herbivore.hpp"

namespace Animals {
	class Herbivore : public Animal
	{
		private:

		public:
			Herbivore(int xCoord, int yCoord) : Animal(xCoord, yCoord) {
				_canEatPlant = true;
				_canEatAnimal = false;
			}

			void dayProcess(){

			}
	};
}