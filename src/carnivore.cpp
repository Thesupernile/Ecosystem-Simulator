#include "headers/carnivore.hpp"

namespace Animals {
	class Carnivore : public Animal
	{
	private:

	public:
		Carnivore(int xCoord, int yCoord) : Animal(xCoord, yCoord) {
			_canEatPlant = false;
			_canEatAnimal = true;
		}
	};
}